/*
* @Author: ramonmelo
* @Date:   2018-07-05
* @Last Modified by:   Ramon Melo
* @Last Modified time: 2018-08-20
*/

#define APP_DEBUG
#define BLYNK_PRINT Serial // Comment out when deploy
#define BLYNK_NO_BUILTIN
#define BLYNK_NO_FLOAT
#define USE_CUSTOM_BOARD

#define UPDATE_RATE 60 // seconds
#define ONE_WIRE_BUS D5
#define VOLTAGE_SENSOR D0

#define SECOND 1000
#define MINUTE SECOND * 60

#include "Arduino.h"
#include <BlynkSimpleEsp8266.h>
#include <TimeLib.h>
#include <WidgetRTC.h>

#include <Sensor/SensorDallas.h>
#include <Sensor/SensorInputVoltage.h>
#include <Sensor/SensorWallVoltage.h>

#include <vector>
#include "config.h"

// Configuration

ADC_MODE(ADC_VCC);

/// Object declaration

OneWire oneWire(ONE_WIRE_BUS);
WidgetTerminal terminal(MONAR_OUTPUT_LOG);
BlynkTimer timer;
WidgetRTC rtc;

std::vector<monar::Sensor*> sensors;

bool connected = false;
bool status = false;
unsigned long last_up = 0;
bool long_blink = false;
bool pulse = false;

/// Main Scope

void init_blinker() {
  pinMode(D4, OUTPUT);
  last_up = millis();
}

void blinker() {
  if (!connected) {
    if ( millis() > last_up ) {
      status = !status;

      last_up = millis() + (long_blink ? 500 : 100);
    }

    digitalWrite(D4, status);
  } else {
    digitalWrite(D4, HIGH);
  }
}

void connect() {
  WiFi.mode(WIFI_STA);

  bool success = false;

  BLYNK_LOG("\nConnecting...");

  long start_time = millis();
  while (WiFi.status() != WL_CONNECTED) {
    delay(10);

    if ( ((millis() - start_time) > MINUTE) && !success ) {

      WiFi.beginSmartConfig();
      BLYNK_LOG("\nBegin SmartConfig...");

      while (1) {
        delay(10);

        if (WiFi.smartConfigDone()) {
          BLYNK_LOG("\nSmartConfig: Success");

          success = true;
          break;
        }

        if ((millis() - start_time) > (MINUTE * 2)) {
            ESP.restart();
        }

        blinker();
      }
    }

    blinker();
  }

  long_blink = true;

  BLYNK_LOG("WiFi Connected.");
  WiFi.printDiag(Serial);
  BLYNK_LOG("IP Address: %s\n", WiFi.localIP().toString().c_str());
  BLYNK_LOG("Gateway IP: %s\n", WiFi.gatewayIP().toString().c_str());
  BLYNK_LOG("Hostname: %s\n",   WiFi.hostname().c_str());
  BLYNK_LOG("RSSI: %d dBm\n",   WiFi.RSSI());
}

void build_time(char *buffer) {
  sprintf(buffer, "%02d:%02d:%02d", hour(), minute(), second());
}

void push(int port, float value) {
  Blynk.virtualWrite(port, (int) value);
}

void blynk_log(String text) {
  char currentTime[9] = "";
  build_time(currentTime);
  terminal.println(String("[") + currentTime + String("] ") + text);
  terminal.flush();
}

void alert(int port, String text, bool notify) {
  if (notify) {
    Blynk.notify(String("{DEVICE_NAME}: ") + text);
  }

  blynk_log(text);
}

void service()
{
  for (unsigned int i = 0; i < sensors.size(); ++i) {
    sensors.at(i)->send(push);
    sensors.at(i)->notify(alert);
  }
}

void setup() {
  delay(500);
  Serial.begin(9600);

  init_blinker();
  connect();

  sensors.push_back(new monar::SensorDallas(&oneWire));
  sensors.push_back(new monar::SensorInputVoltage());
  sensors.push_back(new monar::SensorWallVoltage(VOLTAGE_SENSOR));

  Blynk.config(APP_ID, BLYNK_SERVER, 8080);
  timer.setInterval(1000L * UPDATE_RATE, service);

  BLYNK_LOG("done!");
}

void loop() {
  Blynk.run();
  timer.run();

  connected = Blynk.connected();
  blinker();
}

//
// Blynk Callbacks
//

BLYNK_CONNECTED() {
  Blynk.syncAll();
  rtc.begin();
}

BLYNK_WRITE_DEFAULT()
{
  int pin = request.pin;
  int value = param.asInt();

  for (unsigned int i = 0; i < sensors.size(); ++i) {
    sensors.at(i)->receive(pin, value);
  }
}
