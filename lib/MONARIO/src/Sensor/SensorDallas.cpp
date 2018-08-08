/*
* @Author: Ramon Melo
* @Date:   2018-07-24
* @Last Modified by:   Ramon Melo
* @Last Modified time: 2018-08-07
*/

#include "SensorDallas.h"

namespace monar {

  SensorDallas::SensorDallas(OneWire* ow) :
    Sensor(MONAR_OUTPUT_TEMPERATURE),
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
      tempC += manager.getTempC(sensors[i]);
    }

    tempC /= sensor_count;

    setData(tempC);
  }

  void SensorDallas::receive(int pin, int value) {

    switch(pin) {
      case MONAR_INPUT_TEMPERATURE_MIN:
        temp_min = value;

        Serial.println("update min");
        break;
      case MONAR_INPUT_TEMPERATURE_MAX:
        temp_max = value;

        Serial.println("update max");
        break;
    }
  }

  void SensorDallas::notify(void(*alert)(String)) {
    if (this->data < temp_min) {
      (*alert)(String("Alerta de BAIXA Temperatura"));
    }

    if (this->data > temp_max) {
      (*alert)(String("Alerta de ALTA Temperatura"));
    }
  }
}
