/*
* @Author: caiovictormartinscarvalho
* @Date:   2018-07-09 16:59:17
* @Last Modified by:   caiovictormartinscarvalho
* @Last Modified time: 2018-07-10 16:25:50
*/

#include "Event.h"
// #include <NTPtimeESP.h>


// NTPtime NTPch("ch.pool.ntp.org");
// strDateTime dateTime;


Event::Event(String payload) {
  _timestamp = _setTimestamp();
  _payload = payload;
};

String Event::getPayload() {
	return _payload;
};

unsigned long Event::getTimestamp() {
	return _timestamp;
};

unsigned long Event::_setTimestamp() {
  // dateTime = NTPch.getNTPtime(1.0, 1);
  // return dateTime.epochTime;
  return 12;
};

