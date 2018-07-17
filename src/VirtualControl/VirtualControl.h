# pragma once


class VirtualControl
{
public:
  VirtualControl();
  void reportDS18B20(ONE_WIRE_BUS);
  bool isVariance(float temperature);
  void sendEvent();
  void sendNotification();
};