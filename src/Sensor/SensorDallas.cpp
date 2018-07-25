/*
* @Author: Ramon Melo
* @Date:   2018-07-24
* @Last Modified by:   Ramon Melo
* @Last Modified time: 2018-07-24
*/

#include "SensorDallas.h"

using namespace monar;

SensorDallas::SensorDallas(OneWire* ow) :
  Sensor(MONAR_SENSOR_DALLAS),
  sensors(ow) {

  Serial.print("Locating devices...");
  sensors.begin();
  Serial.print("Found ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" devices.");

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
}

SensorDallas::~SensorDallas() {
}

void SensorDallas::service() {
  sensors.requestTemperatures();
  float tempC = sensors.getTempC(thermometer);

  setData(tempC);
}
