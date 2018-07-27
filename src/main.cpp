/*
* @Author: ramonmelo
* @Date:   2018-07-05
* @Last Modified by:   Ramon Melo
* @Last Modified time: 2018-07-26
*/

///
/// DHT22 -> D5
///

#define DEVICE_NAME "Monar"
#define BLYNK_PRINT Serial
#define UPDATE_RATE 2 // seconds
#define ONE_WIRE_BUS D5

#include "Arduino.h"
#include <BlynkSimpleEsp8266.h>

#include "Sensor/SensorDallas.h"

OneWire oneWire(ONE_WIRE_BUS);
WidgetTerminal terminal(V0);

ADC_MODE(ADC_VCC);

BlynkTimer timer;
monar::SensorDallas dallas(&oneWire);

// Blynk App credentials
char auth[] = "79ff8641717a48adbe72780710e8f945";
char address[] = "blynk.canionlabs.io";

// WiFi credentials.
char ssid[] = "Venal Ninja Labs";
char pass[] = "Venal@2016";

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

  Blynk.begin(auth, ssid, pass, address, 8080);
  timer.setInterval(1000L * UPDATE_RATE, sendSensor);

   // Clear the terminal content
  terminal.clear();
  terminal.println(F("Blynk v" BLYNK_VERSION ": Device started"));
  terminal.println(DEVICE_NAME);
  terminal.println(F("-------------"));
  terminal.flush();
}

void loop() {
  Blynk.run();
  timer.run();
}
