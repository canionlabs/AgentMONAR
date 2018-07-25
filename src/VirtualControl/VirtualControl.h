#pragma once

#include "Sensor/Sensor.h"

namespace monar {
  class VirtualControl : Sensor
  {
  public:
    VirtualControl(int port);

    // void publish() override;
    // void service() override;

    // int MinTemperature;
    // int MaxTemperature;
    // bool isVariance(float temperature);
    // void reportDS18B20(int ONE_WIRE_BUS);
    // void publishVirtual(float payload, int port);
    // void sendNotification(float temperature);
  };
}
