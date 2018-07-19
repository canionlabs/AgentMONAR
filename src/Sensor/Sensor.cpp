/*
* @Author: ramonmelo
* @Date:   2018-07-09 16:59:17
* @Last Modified by:   caiovictormartinscarvalho
* @Last Modified time: 2018-07-19 18:53:09
*/

#include "Sensor.h"
#include <OneWire.h>
#include <DallasTemperature.h>

Sensor::Sensor(int port) {
  PORT = port;
  if (PORT == 14) {
  	OneWire oneWire(ONE_WIRE_BUS);
    DallasTemperature sensor(&oneWire);
  }
};

bool Sensor::isDS18B20() {
  if (PORT == 14) {
    return true;
  }
  return false;
}

int Sensor::getCount() {
  if (isDS18B20() == true) {
    return sensor.getDS18Count();
  }
  return 1;
}

float Sensor::getTemperature(int index) {
  if (isDS18B20() == true) {
    sensors.requestTemperatures();
    return sensor.getTempCByIndex(index);
  }
}

// unsigned long Sensor::getValue() {
// 	return _value;
// }

// unsigned long Sensor::getTimestamp() {
// 	return _timestamp;
// };

// unsigned long Sensor::_generatePayload() {
//   unsigned long out = _timestamp << sizeof(unsigned short) * 8;
//   return out | _value;
// }
