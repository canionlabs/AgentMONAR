/*
* @Author: Ramon Melo
* @Date:   2018-08-06
* @Last Modified by:   Ramon Melo
* @Last Modified time: 2018-08-07
*/

#include "SensorInputVoltage.h"

namespace monar {

  SensorInputVoltage::SensorInputVoltage() :
    Sensor(MONAR_OUTPUT_VOLTAGE) {
  }

  void SensorInputVoltage::service() {
    float v = ((float) ESP.getVcc() / 1024.0f) * 1.12;
    setData(v);
  }
}
