#pragma once

#include "Sensor.h"
#include <DallasTemperature.h>

namespace monar {

  class SensorDallas : public Sensor
  {
  public:
    SensorDallas(OneWire* ow);

    void service() override;
  private:
    DallasTemperature manager;
    DeviceAddress *sensors;
    int sensor_count;
  };
}
