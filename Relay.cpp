#include "Relay.h"
#include "Arduino.h"

Relay::Relay(int signal_pin, bool normally_open) {
  pinMode(signal_pin, OUTPUT);

  norm_open = normally_open;
  pin_signal = signal_pin;

  //set to off
  if(norm_open) {
    digitalWrite(pin_signal, LOW);  
  } else {
    digitalWrite(pin_signal, HIGH);  
  }
}

void Relay::on() {
  if(norm_open) {
    digitalWrite(pin_signal, HIGH);  
  } else {
    digitalWrite(pin_signal, LOW);  
  }
}

void Relay::off() {
  if(norm_open) {
    digitalWrite(pin_signal, LOW);  
  } else {
    digitalWrite(pin_signal, HIGH);  
  }
}
