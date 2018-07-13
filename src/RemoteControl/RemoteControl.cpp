/*
* @Author: caiovictormartinscarvalho
* @Date:   2018-07-13 10:26:22
* @Last Modified by:   caiovictormartinscarvalho
* @Last Modified time: 2018-07-13 12:13:39
*/

#include "Settings.h"

RemoteControl::Event(int status = -1) {
  _status = status;

  if (status == -1) {
    updateDisplay(status);
  }
}

int RemoteControl::getStatus() {
  return _status;
}

void RemoteControl::setStatus(int status) {
  _status = status
}

void RemoteControl::updateDisplay(int pin) {
  if (pin >= 0 || pin <= amountTypes) {
    setStatus(pin);
    Blynk.virtualWrite(V10, "Produção:");
    Blynk.virtualWrite(V11, pinTypes[pin]);
  } else if (pin == -1) {
    Blynk.virtualWrite(V10, "Selecione o");
    Blynk.virtualWrite(V11, "tipo de produção");
  }

  updateButtons();
}

void RemoteControl::updateButtons() {
  for (int i=0; i <= amountTypes ; i++) {
    if (i != _status) {
      Blynk.virtualWrite(i, 0);
    }
  }
}