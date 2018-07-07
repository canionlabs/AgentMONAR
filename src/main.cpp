/*
* @Author: ramonmelo
* @Date:   2018-07-05
* @Last Modified by:   caiovictormc
* @Last Modified time: 2018-07-07 11:10:29
*/

#define BLYNK_PRINT Serial

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


// Auth Token in the Blynk App.
char auth[] = "";

// WiFi credentials.
char ssid[] = "";
char pass[] = "";

// Pins reserved for types
const int amountTypes = 4;
String pinTypes[amountTypes] = {"Arg 0", "Arg 1", "Arg 2", "Arg 3"};
int bufferType = -1;


void initialVirtualStatus() {
  Blynk.virtualWrite(V10, "Selecione o");
  Blynk.virtualWrite(V11, "tipo de produção");
  for (int i=0; i <= amountTypes ; i++) {
    Blynk.virtualWrite(i, 0);
  }
}


void updateVirtualStatus(int pin) {
  if (pin >= 0 || pin <= amountTypes) {
    bufferType = pin;
    Blynk.virtualWrite(V10, "Produção:");
    Blynk.virtualWrite(V11, pinTypes[pin]);
  }
  for (int i=0; i <= amountTypes ; i++) {
    if (i != pin) {
      Blynk.virtualWrite(i, 0);
    }
  }
}


BLYNK_CONNECTED() {
  if (bufferType != -1) {
    updateVirtualStatus(bufferType);
  } else {
    initialVirtualStatus();
  }

}


BLYNK_WRITE_DEFAULT() {
  int pin = request.pin;
  updateVirtualStatus(pin);
}


void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}


void loop() {
  Blynk.run();
}
