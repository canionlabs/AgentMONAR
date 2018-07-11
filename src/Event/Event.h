#pragma once

// #ifndef Event_H
// #define Event_H

#include "Arduino.h"


class Event {
public:
  Event(String payload); // constructor
  unsigned long getTimestamp();
  String getPayload();

private:
  unsigned long _timestamp;
  String _payload;

  unsigned long _setTimestamp();
};