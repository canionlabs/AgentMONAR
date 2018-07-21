#pragma once

class VirtualControl
{
public:
  VirtualControl();

  int MinTemperature;
  int MaxTemperature;

  bool isVariance(float temperature);
  void reportDS18B20(int ONE_WIRE_BUS);
  void publishVirtual(float payload, int port);
  void sendNotification(float temperature);
};
