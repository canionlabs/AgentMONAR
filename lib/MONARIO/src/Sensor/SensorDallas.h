#pragma once

#include "Sensor.h"
#include <DallasTemperature.h>
#include <map>

namespace monar {

  class SensorDallas : public Sensor
  {
  public:
    SensorDallas(OneWire* ow);

    void service() override;
    void receive(int pin, int value) override;
    void notify(void(*alert)(int, String)) override;

  private:
    DallasTemperature manager;
    DeviceAddress *sensors;
    int sensor_count;

    int temp_min;
    int temp_max;

    std::map<int, int> pin_map;
  };
}
