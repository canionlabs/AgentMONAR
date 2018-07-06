/*
* @Author: ramonmelo
* @Date:   2018-07-05
* @Last Modified by:   ramonmelo
* @Last Modified time: 2018-07-05
*/

#define BLYNK_PRINT Serial

#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "bb4604f08a224670805ef10c9e13438e";

char ssid[] = "Venal Ninja Labs";
char pass[] = "Venal@2016";

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}
