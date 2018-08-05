/*
* @Author: ramonmelo
* @Date:   2018-07-05
* @Last Modified by:   Ramon Melo
* @Last Modified time: 2018-08-03
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
#include "Sensor/SensorDallas.h"

#include <ESP8266httpUpdate.h>

OneWire oneWire(ONE_WIRE_BUS);
WidgetTerminal terminal(V0);

ADC_MODE(ADC_VCC);

BlynkTimer timer;
monar::SensorDallas dallas(&oneWire);

// Blynk App credentials
char auth[] = "79ff8641717a48adbe72780710e8f945";
char address[] = "blynk.canionlabs.io";

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
  Serial.println("Free:");
  Serial.println(ESP.getFreeSketchSpace());
}

void push(int port, float value) {
  Blynk.virtualWrite(port, value);
}

void sendSensor()
{
  dallas.publish(push);

  terminal.print(F("."));
  terminal.flush();

  float v = ((float) ESP.getVcc() / 1024.0f) * 1.12;
  Blynk.virtualWrite(V5, v);
}

void setup() {
  Serial.begin(9600);

  connect();

  Blynk.config(auth, address, 8080);
  timer.setInterval(1000L * UPDATE_RATE, sendSensor);

   // Clear the terminal content
  terminal.clear();
  terminal.println(F("Blynk v" BLYNK_VERSION ": Device started"));
  terminal.println(DEVICE_NAME);
  terminal.println(F("-------------"));

  terminal.println(F("Free Scketch Space"));
  terminal.println(ESP.getFreeSketchSpace());

  terminal.flush();

  // ESPhttpUpdate.update("192.168.88.240", 5000, "/firmware");
}

void loop() {
  Blynk.run();
  timer.run();
}
