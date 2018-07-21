/*
* @Author: ramonmelo
* @Date:   2018-07-05
* @Last Modified by:   Ramon Melo
* @Last Modified time: 2018-07-18
*/

///
/// DHT22 -> D5
/// DS18b20 -> DS18b20
///

#define BLYNK_PRINT Serial
#define ONE_WIRE_BUS 5
#define DHTTYPE DHT22
#define DHTPIN 14

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#include <OneWire.h>
#include <DallasTemperature.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

ADC_MODE(ADC_VCC);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress thermometer;

DHT_Unified dht(DHTPIN, DHTTYPE);

BlynkTimer timer;

// Auth Token in the Blynk App.
char auth[] = "dbd404c9c3b14b5c9c94eec2ba045082";
// char auth[] = "";

// WiFi credentials.
char ssid[] = "Automata";
char pass[] = "data.hal.johnny";
// char ssid[] = "";
// char pass[] = "";

// Pins reserved for types
// const int amountTypes = 4;
// String pinTypes[amountTypes] = {"Arg 0", "Arg 1", "Arg 2", "Arg 3"};
// int bufferType = -1;

// void initialVirtualStatus() {
//   Blynk.virtualWrite(V10, "Selecione o");
//   Blynk.virtualWrite(V11, "tipo de produção");
//   for (int i=0; i <= amountTypes ; i++) {
//     Blynk.virtualWrite(i, 0);
//   }
// }

// void updateVirtualStatus(int pin) {
//   if (pin >= 0 || pin <= amountTypes) {
//     bufferType = pin;
//     Blynk.virtualWrite(V10, "Produção:");
//     Blynk.virtualWrite(V11, pinTypes[pin]);
//   }
//   for (int i=0; i <= amountTypes ; i++) {
//     if (i != pin) {
//       Blynk.virtualWrite(i, 0);
//     }
//   }
// }

// BLYNK_CONNECTED() {
//   if (bufferType != -1) {
//     updateVirtualStatus(bufferType);
//   } else {
//     initialVirtualStatus();
//   }
// }

// BLYNK_WRITE_DEFAULT() {
//   int pin = request.pin;
//   updateVirtualStatus(pin);
// }

// void printAddress(DeviceAddress deviceAddress)
// {
//   for (uint8_t i = 0; i < 8; i++)
//   {
//     if (deviceAddress[i] < 16) Serial.print("0");
//     Serial.print(deviceAddress[i], HEX);
//   }
// }

// void printTemperature(DeviceAddress deviceAddress)
// {
//   float tempC = sensors.getTempC(deviceAddress);
//   Serial.print("Temp C: ");
//   Serial.print(tempC);
// }

void sendSensor()
{
  sensors_event_t event;

  dht.temperature().getEvent(&event);

  if (!isnan(event.temperature)) {
    Blynk.virtualWrite(V5, event.temperature);
  } else {
    Serial.println("Error reading temperature!");
  }

  dht.humidity().getEvent(&event);

  if (!isnan(event.relative_humidity)) {
    Blynk.virtualWrite(V6, event.relative_humidity);
  } else {
    Serial.println("Error reading humidity!");
  }

  float v = ((float) ESP.getVcc() / 1024.0f) * 1.12;
  Blynk.virtualWrite(V7, v);
}

void setup() {
  Serial.begin(9600);
  dht.begin();

  // Serial.print("Locating devices...");
  // sensors.begin();
  // Serial.print("Found ");
  // Serial.print(sensors.getDeviceCount(), DEC);
  // Serial.println(" devices.");

  // // report parasite power requirements
  // Serial.print("Parasite power is: ");
  // if (sensors.isParasitePowerMode()) {
  //   Serial.println("ON");
  // } else {
  //   Serial.println("OFF");
  // }

  // if (!sensors.getAddress(thermometer, 0)) {
  //   Serial.println("Unable to find address for Device 0");
  // }

  // Serial.print("Device 0 Address: ");
  // printAddress(thermometer);
  // Serial.println();

  // sensors.setResolution(thermometer, 9);

  Blynk.begin(auth, ssid, pass);
  // Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  timer.setInterval(1000L * 60, sendSensor);
}

void loop() {
  Blynk.run();
  timer.run();

  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  // Serial.print("Requesting temperatures...");
  // sensors.requestTemperatures(); // Send the command to get temperatures
  // Serial.println("DONE");

  // It responds almost immediately. Let's print out the data
  // printTemperature(thermometer); // Use a simple function to print out the data
}
