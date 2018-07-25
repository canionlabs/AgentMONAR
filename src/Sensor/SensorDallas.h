#pragma once

#include "Sensor.h"
#include <DallasTemperature.h>

namespace monar {

  class SensorDallas : public Sensor
  {
  public:
    SensorDallas(OneWire* ow);
    ~SensorDallas();

    void service() override;
  private:
    DallasTemperature sensors;
    DeviceAddress thermometer;
  };
}
