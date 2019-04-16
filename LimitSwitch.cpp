#include "Arduino.h"
#include "LimitSwitch.h"

LimitSwitch::LimitSwitch(int port_pin) {
  pinMode(port_pin, INPUT);
  
  pin_port = port_pin;  
}

bool LimitSwitch::is_pressed() {
  return digitalRead(pin_port);
}
