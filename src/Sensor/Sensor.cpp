/*
* @Author: Ramon Melo
* @Date:   2018-07-24
* @Last Modified by:   Ramon Melo
* @Last Modified time: 2018-08-06
*/

#include "Sensor.h"

namespace monar {
  Sensor::Sensor(int port):
    port(port) {
  }

  float Sensor::publish(void (*push)(int, float)) {
    this->service();
    (*push)(this->port, this->data);

    return this->data;
  }

  void Sensor::setData(float data) {
    this->data = data;
  }
}
