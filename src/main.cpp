/*
* @Author: ramonmelo
* @Date:   2018-07-05
* @Last Modified by:   Ramon Melo
* @Last Modified time: 2018-07-23
*/

///
/// DHT22 -> D5
///

#define BLYNK_PRINT Serial
#define ONE_WIRE_BUS D5

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
// #include "VirtualControl/VirtualControl.h"

#include <OneWire.h>
#include <DallasTemperature.h>

ADC_MODE(ADC_VCC);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress thermometer;

BlynkTimer timer;

// Auth Token in the Blynk App.
char auth[] = "79ff8641717a48adbe72780710e8f945";
char address[] = "blynk.canionlabs.io";

// Blynk App credentials
char auth[] = "d9e2d7366eb24c848885c7b672aaaf96";
char address[] = "blynk.canionlabs.io";

// WiFi credentials.
char ssid[] = "Automata";
char pass[] = "data.hal.johnny";

void sendSensor()
{
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  // Serial.println("DONE");

  float tempC = sensors.getTempC(thermometer);

  Serial.println(tempC);

  Blynk.virtualWrite(V5, tempC);

  float v = ((float) ESP.getVcc() / 1024.0f) * 1.12;
  Blynk.virtualWrite(V7, v);
}

void setup() {
  Serial.begin(9600);

  Serial.print("Locating devices...");
  sensors.begin();
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");

  // report parasite power requirements
  Serial.print("Parasite power is: ");
  if (sensors.isParasitePowerMode()) {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }

  if (!sensors.getAddress(thermometer, 0)) {
    Serial.println("Unable to find address for Device 0");
  }

  sensors.setResolution(thermometer, 9);

  Blynk.begin(auth, ssid, pass, address, 8080);
  timer.setInterval(1000L * 30, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();
}
