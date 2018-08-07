/*
* @Author: Ramon Melo
* @Date:   2018-07-24
* @Last Modified by:   Ramon Melo
* @Last Modified time: 2018-08-07
*/

#include "SensorDallas.h"

using namespace monar;

SensorDallas::SensorDallas(OneWire* ow) :
  Sensor(CANION_SENSOR_DALLAS),
  manager(ow) {

  Serial.print("Locating devices...");
  manager.begin();
  sensor_count = manager.getDeviceCount();

  Serial.print("Found ");
  Serial.print(sensor_count, DEC);
  Serial.println(" devices.");

  Serial.print("Parasite power is: ");
  if (manager.isParasitePowerMode()) {
    Serial.println("ON");
  } else {
    Serial.println("OFF");
  }

  sensors = new DeviceAddress[sensor_count];

  for (int i = 0; i < sensor_count; ++i)
  {
    if (manager.getAddress(sensors[i], i)) {
      Serial.println("Found Device");
      manager.setResolution(sensors[i], 9);
    } else {
      Serial.println("Unable to find address for Device");
    }
  }
}

void SensorDallas::service() {
  manager.requestTemperatures();

  float tempC = 0;
  for (int i = 0; i < sensor_count; ++i)
  {
    float t = manager.getTempC(sensors[i]);

    Serial.println(t);

    tempC += t;
  }

  tempC /= sensor_count;

  setData(tempC);
}
