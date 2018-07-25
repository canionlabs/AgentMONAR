/*
* @Author: Ramon Melo
* @Date:   2018-07-24
* @Last Modified by:   Ramon Melo
* @Last Modified time: 2018-07-24
*/

#include "Sensor.h"

namespace monar {
  Sensor::Sensor(int port):
    port(port) {
  }

  void Sensor::publish(void (*push)(int, float)) {
    (*push)(this->port, this->data);
  }

  void Sensor::setData(float data) {
    this->data = data;
  }
}
