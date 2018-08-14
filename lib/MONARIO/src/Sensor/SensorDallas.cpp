/*
* @Author: Ramon Melo
* @Date:   2018-07-24
* @Last Modified by:   Ramon Melo
* @Last Modified time: 2018-08-13
*/

#include "SensorDallas.h"

// function to print a device address
void printAddress(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

namespace monar {

  SensorDallas::SensorDallas(OneWire* ow) : manager(ow) {

    // pin mapping
    pin_map[0] = MONAR_OUTPUT_TEMPERATURE_1;
    pin_map[1] = MONAR_OUTPUT_TEMPERATURE_2;
    pin_map[2] = MONAR_OUTPUT_TEMPERATURE_3;
    pin_map[3] = MONAR_OUTPUT_TEMPERATURE_4;
    pin_map[4] = MONAR_OUTPUT_TEMPERATURE_5;
    pin_map[5] = MONAR_OUTPUT_TEMPERATURE_6;
    pin_map[6] = MONAR_OUTPUT_TEMPERATURE_7;
    pin_map[7] = MONAR_OUTPUT_TEMPERATURE_8;
    // END pin mapping

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

    for (int i = 0; i < sensor_count; ++i)
    {
      float t = manager.getTempC(sensors[i]);

      setData(pin_map[i], t);
    }
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

  void SensorDallas::notify(void(*alert)(int, String)) {
    // if (this->data < temp_min) {
    //   (*alert)(MONAR_OUTPUT_LOG, String("Alerta de BAIXA Temperatura"));
    // }
    // if (this->data > temp_max) {
    //   (*alert)(MONAR_OUTPUT_LOG, String("Alerta de ALTA Temperatura"));
    // }
  }
}
