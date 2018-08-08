#pragma once

#include <monar_defines.h>
#include "Arduino.h"

namespace monar {

  class Sensor {
  public:
    Sensor(int port);

    float send(void (*push)(int, float));
    void setData(float data);

    virtual void receive(int pin, int value);
    virtual void service() = 0;
    virtual void notify(void(*alert)(String));

  protected:
    float data;
    int port;
  };
}
