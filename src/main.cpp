/*
* @Author: ramonmelo
* @Date:   2018-07-05
* @Last Modified by:   Ramon Melo
* @Last Modified time: 2018-07-21
*/

#define BLYNK_PRINT Serial
#define ONE_WIRE_BUS 14
#define VP_MIN_TEMP 20
#define VP_MAX_TEMP 21

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
// #include "VirtualControl/VirtualControl.h"

// OneWire Settings
// OneWire oneWire(ONE_WIRE_BUS);
// DallasTemperature sensors(&oneWire);

// Virtual Pins Operations
// VirtualControl virtualControl();

// Blynk App credentials
char auth[] = "d9e2d7366eb24c848885c7b672aaaf96";
char address[] = "blynk.canionlabs.io";

// WiFi credentials.
char ssid[] = "Venal Ninja Labs";
char pass[] = "Venal@2016";


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


// BLYNK_WRITE_DEFAULT() {
//   int pin = request.pin;
//   int value = param.asInt();

//   if (pin == VP_MIN_TEMP) {
//     VirtualControl.MinTemperature(value);
//   } else if (pin == VP_MAX_TEMP) {
//     VirtualControl.MaxTemperature(value);
//   }
// }

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, address, 8080);
  // VirtualControl.MinTemperature(10);
  // VirtualControl.MaxTemperature(30);
}

void loop() {
  Blynk.run();
  // virtualControl.reportDS18B20(ONE_WIRE_BUS);
  // virtualControl.reportDHT22();
  // virtualControl.reportDS18B20(ONE_WIRE_BUS);

  delay(1000 * 60 * 1); // (x * y * minutes)
}
