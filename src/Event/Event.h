#pragma once

// #ifndef Event_H
// #define Event_H

#include "Arduino.h"


class Event {
public:
  Event(int value, unsigned long timestamp); // constructor
  unsigned long getTimestamp();
  unsigned long getValue();
  unsigned long getPayload();

private:
  unsigned long _timestamp;
  unsigned long _payload;
  int _value;

  unsigned long _generatePayload();
};