/*
* @Author: ramonmelo
* @Date:   2018-07-05
* @Last Modified by:   Ramon Melo
* @Last Modified time: 2018-08-08
*/

#define BLYNK_PRINT Serial // Comment out when deploy
#define BLYNK_NO_BUILTIN
#define BLYNK_NO_FLOAT

#define DEVICE_NAME "Monar"

#define UPDATE_RATE 60 // seconds
#define ONE_WIRE_BUS D5

#include "Arduino.h"
#include <BlynkSimpleEsp8266.h>
#include <TimeLib.h>
#include <WidgetRTC.h>

#include <Sensor/SensorDallas.h>
#include <Sensor/SensorInputVoltage.h>

#include <vector>

// Configuration

ADC_MODE(ADC_VCC);

/// Object declaration

OneWire oneWire(ONE_WIRE_BUS);
WidgetTerminal terminal(MONAR_OUTPUT_LOG);
BlynkTimer timer;
WidgetRTC rtc;

std::vector<monar::Sensor*> sensors;

char auth[] = "cb395bc6d9a742df9baeb14b3b41db1e";
char address[] = "blynk.canionlabs.io";

/// Main Scope

void connect() {
  WiFi.mode(WIFI_STA);

  int cnt = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    BLYNK_LOG(".");
    if (cnt++ >= 10) {
      WiFi.beginSmartConfig();
      while (1) {
        delay(1000);
        if (WiFi.smartConfigDone()) {
          BLYNK_LOG("\nSmartConfig: Success");
          break;
        }
        BLYNK_LOG("|");
      }
    }
  }

  BLYNK_LOG("WiFi Connected.");
  WiFi.printDiag(Serial);
  BLYNK_LOG("IP Address: %s\n", WiFi.localIP().toString().c_str());
  BLYNK_LOG("Gateway IP: %s\n", WiFi.gatewayIP().toString().c_str());
  BLYNK_LOG("Hostname: %s\n",   WiFi.hostname().c_str());
  BLYNK_LOG("RSSI: %d dBm\n",   WiFi.RSSI());
}

void push(int port, float value) {
  Blynk.virtualWrite(port, (int) value);
}

void alert(int port, String text) {
  Blynk.notify(String("{DEVICE_NAME}: ") + text);

  String currentTime = String("[") + String(hour()) + ":" + minute() + ":" + second() + "] ";

  terminal.println(currentTime + text);
  terminal.flush();
}

void service()
{
  for (unsigned int i = 0; i < sensors.size(); ++i) {
    sensors.at(i)->send(push);
    sensors.at(i)->notify(alert);
  }
}

void setup() {
  Serial.begin(9600);

  sensors.push_back(new monar::SensorDallas(&oneWire));
  sensors.push_back(new monar::SensorInputVoltage());

  connect();

  Blynk.config(auth, address, 8080);
  timer.setInterval(1000L * UPDATE_RATE, service);

  BLYNK_LOG("done!");
}

void loop() {
  Blynk.run();
  timer.run();
}

//
// Blynk Callbacks
//

BLYNK_CONNECTED() {
  // terminal.clear();
  // terminal.println(F("Blynk v" BLYNK_VERSION ": Device started"));
  // terminal.println(DEVICE_NAME);
  // terminal.println(F("-------------"));
  // terminal.println(F("Free Scketch Space"));
  // terminal.println(ESP.getFreeSketchSpace());
  // terminal.flush();

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
