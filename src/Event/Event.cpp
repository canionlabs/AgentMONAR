/*
* @Author: ramonmelo
* @Date:   2018-07-09 16:59:17
* @Last Modified by:   caiovictormartinscarvalho
* @Last Modified time: 2018-07-12 11:32:15
*/

#include "Event.h"


Event::Event(int value, unsigned long timestamp) {
  _timestamp = timestamp;
  _value = value;
  _payload = _generatePayload();
};

unsigned long Event::getPayload() {
	return _payload;
};

unsigned long Event::getValue() {
	return _value;
}

unsigned long Event::getTimestamp() {
	return _timestamp;
};

unsigned long Event::_generatePayload() {
  unsigned long out = _timestamp << sizeof(unsigned short) * 8;
  return out | _value;
}
