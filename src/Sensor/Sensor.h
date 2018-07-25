#pragma once

#define MONAR_SENSOR_DALLAS 7

namespace monar {

  class Sensor {
  public:
    Sensor(int port);

    void publish(void (*push)(int, float));
    void setData(float data);

    virtual void service() = 0;
  private:
    int port;
    float data;
  };
}
