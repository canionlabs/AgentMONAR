#pragma once

#define CANION_SENSOR_VOLTAGE  5
#define CANION_SENSOR_CURRENT  6
#define CANION_SENSOR_DALLAS 7

#include "Arduino.h"

namespace monar {

  class Sensor {
  public:
    Sensor(int port);

    float publish(void (*push)(int, float));
    void setData(float data);

    virtual void service() = 0;
  private:
    int port;
    float data;
  };
}
