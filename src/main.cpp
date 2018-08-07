/*
* @Author: ramonmelo
* @Date:   2018-07-05
* @Last Modified by:   Ramon Melo
* @Last Modified time: 2018-08-06
*/

///
/// DHT22 -> D5
///

#define DEVICE_NAME "Monar"
#define BLYNK_PRINT Serial
#define UPDATE_RATE 15 // seconds
#define ONE_WIRE_BUS D5

#include "Arduino.h"
#include <BlynkSimpleEsp8266.h>

#include "Sensor/Sensor.h"
#include "Sensor/SensorDallas.h"
#include "Sensor/SensorInputVoltage.h"

#include <vector>

// Configuration

ADC_MODE(ADC_VCC);

/// Object declaration

OneWire oneWire(ONE_WIRE_BUS);
WidgetTerminal terminal(V0);
BlynkTimer timer;

std::vector<monar::Sensor*> sensors;

char auth[] = "0f251ae887d344ceb98348bf385a4a79";
char address[] = "blynk.canionlabs.io";

/// Main Scope

void connect() {
  WiFi.mode(WIFI_STA);

  int cnt = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (cnt++ >= 10) {
      WiFi.beginSmartConfig();
      while (1) {
        delay(1000);
        if (WiFi.smartConfigDone()) {
          Serial.println();
          Serial.println("SmartConfig: Success");
          break;
        }
        Serial.print("|");
      }
    }
  }

  Serial.println("WiFi Connected.");
  WiFi.printDiag(Serial);
  Serial.printf("IP Address: %s\n", WiFi.localIP().toString().c_str());
  Serial.printf("Gateway IP: %s\n", WiFi.gatewayIP().toString().c_str());
  Serial.printf("Hostname: %s\n",   WiFi.hostname().c_str());
  Serial.printf("RSSI: %d dBm\n",   WiFi.RSSI());
}

void push(int port, float value) {
  Blynk.virtualWrite(port, value);
}

void sendSensor()
{
  for (unsigned int i = 0; i < sensors.size(); ++i)
  {
    sensors.at(i)->publish(push);
  }

  terminal.print(F("."));
  terminal.flush();
}

void setup() {
  Serial.begin(9600);

  sensors.push_back(new monar::SensorDallas(&oneWire));
  sensors.push_back(new monar::SensorInputVoltage());

  connect();

  Blynk.config(auth, address, 8080);
  timer.setInterval(1000L * UPDATE_RATE, sendSensor);

  Serial.println("done!");
}

void loop() {
  Blynk.run();
  timer.run();
}

// Blynk Callbacks
BLYNK_CONNECTED() {
  terminal.clear();
  terminal.println(F("Blynk v" BLYNK_VERSION ": Device started"));
  terminal.println(DEVICE_NAME);
  terminal.println(F("-------------"));
  terminal.println(F("Free Scketch Space"));
  terminal.println(ESP.getFreeSketchSpace());
  terminal.flush();
}
