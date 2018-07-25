/*
* @Author: ramonmelo
* @Date:   2018-07-05
* @Last Modified by:   Ramon Melo
* @Last Modified time: 2018-07-24
*/

///
/// DHT22 -> D5
///

#define BLYNK_PRINT Serial
#define UPDATE_RATE 2 // seconds
#define ONE_WIRE_BUS D5

#include "Arduino.h"
#include <BlynkSimpleEsp8266.h>

#include "Sensor/SensorDallas.h"

OneWire oneWire(ONE_WIRE_BUS);

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

//   float v = ((float) ESP.getVcc() / 1024.0f) * 1.12;
//   Blynk.virtualWrite(V7, v);
}

void setup() {
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass, address, 8080);
  timer.setInterval(1000L * UPDATE_RATE, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();

  dallas.service();
}
