/*
* @Author: caiovictormartinscarvalho
* @Date:   2018-07-13 10:26:22
* @Last Modified by:   Ramon Melo
* @Last Modified time: 2018-07-21
*/

#include "VirtualControl.h"
#include "Sensor/Sensor.h"
#include <BlynkSimpleEsp8266.h>x
#include <sstream>

const int PROB_LIMIT = 3;
int PROB_VIRTUAL_PORTS[PROB_LIMIT] = {1, 2, 3};
int ENVIROMENT_PORT = 4;

void VirtualControl::reportDS18B20(int ONE_WIRE_BUS) {
  Sensor sensor(ONE_WIRE_BUS);
  int DS18Count = sensor.getCount();

  for(int i=0; i<=DS18Count; i++){
    float temperature = sensor.getTemperature(i);
    if (i <= PROB_LIMIT) {
      publishVirtual(temperature, PROB_VIRTUAL_PORTS[i]);
    }
  }
}

void VirtualControl::publishVirtual(float payload, int port) {
  if (isVariance(payload)) {
    sendNotification(payload);
  }
  Blynk.virtualWrite(port, payload);
}

bool VirtualControl::isVariance(float temperature) {
  if (temperature >= MaxTemperature || temperature <= MinTemperature) {
    return true;
  } else {
    return false;
  }
}

void VirtualControl::sendNotification(float temperature) {
  std::ostringstream notifyMessage;
  notifyMessage << "Alerta de Temperatura, " << notifyMessage << " ˚C registrados no local {DEVICE_NAME}";
  Blynk.notify(notifyMessage.str());
}


// void VirtualControl::sendNotification(port) {

// }

// RemoteControl::Event(int status = -1) {
//   _status = status;

//   if (status == -1) {
//     updateDisplay(status);
//   }
// }

// int RemoteControl::getStatus() {
//   return _status;
// }

// void RemoteControl::setStatus(int status) {
//   _status = status
// }

// void RemoteControl::updateDisplay(int pin) {
//   if (pin >= 0 || pin <= amountTypes) {
//     setStatus(pin);
//     Blynk.virtualWrite(V10, "Produção:");
//     Blynk.virtualWrite(V11, pinTypes[pin]);
//   } else if (pin == -1) {
//     Blynk.virtualWrite(V10, "Selecione o");
//     Blynk.virtualWrite(V11, "tipo de produção");
//   }

//   updateButtons();
// }

// void RemoteControl::updateButtons() {
//   for (int i=0; i <= amountTypes ; i++) {
//     if (i != _status) {
//       Blynk.virtualWrite(i, 0);
//     }
//   }
// }
