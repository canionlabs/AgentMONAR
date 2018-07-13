# pragma once


class RemoteControl
{
public:
  RemoteControl(int status);
  int getStatus;
  void setStatus;

private:
  int _status;

  void updateDisplay();
};