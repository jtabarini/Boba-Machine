/*
 * Can only be used for input
 * A0 - boiling_pot_stop
 * A1 - boiling_pot_reset
 * A2 - dispense_boba_switch
 * A3 - sugar_water_pot_stop
 * A4 - sugar_water_pot_reset
 * A5 - 
 * 
 * PORTS 0 and 1 i think can't be used during operation because of
 *  serial communication over the usb
 *  
 * Digital Write/Read pins
 * 2 - water_to_boba_boiler_pump
 * 4 - heating_element1
 * 7 - heating_element2
 * 8 - BROKEN
 * 12 - boiling_motor_turn_in2
 * 13 - boba_dispense_relay
 * 
 * PWM pins
 * 3 - boiling_motor_turn_enable
 * 5 - boba_and_sugar_water_motor_in1
 * 6 - boba_and_sugar_water_motor_in2
 * 10 - boba_and_sugar_water_motor_en
 * 11 - sugar_water_pump
 */

 /*
  * 4 relays
  * 2 H-bridges
  * 5 LimitSwitches
  */

#include "Relay.h"
#include "DC_Motor_Driver.h"
#include "Stepper_Motor_Driver.h"
#include "LimitSwitch.h"

#define MOTOR_SPEED 200
#define AMOUNT_OF_WATER_TO_BOBA 12000 //six seconds of water being pumped
#define AMOUNT_OF_TIME_TO_BOIL_WATER 1000*10 //4 minutes to boil water
#define BOBA_COOK_TIME_WITH_HEAT 1000*10 //6 minutes to cook boba with heat
#define BOBA_COOK_TIME_WITHOUT_HEAT 1000*10 //4 minutes to cook boba without heat
#define AMOUNT_OF_TIME_TO_PUMP_SUGAR_WATER 3000 //15 seconds of sugar water pumped
#define BOBA_AND_SUGAR_WAIT_TIME 1000*10 //2.5 minutes to soak boba in sugar water

Relay water_to_boba_boiler_pump(2, true);
//Relay heating_element1(4, true);
//Relay heating_element2(7, true);
Relay sugar_water_pump(11, true);
Relay boba_dispense_relay(13, true);

DC_Motor_Driver boiling_motor_turn(4,12,3);
DC_Motor_Driver boba_and_sugar_water_motor(5, 6, 10);

LimitSwitch boiling_pot_stop(A0);
LimitSwitch boiling_pot_reset(A1);
LimitSwitch dispense_boba_switch(A2);
LimitSwitch sugar_water_pot_stop(A3);
LimitSwitch sugar_water_pot_reset(A4);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()) {
    String token = Serial.readStringUntil('\n');
    if (token.equals("Make_Boba")) {
      make_boba();

      Serial.println("Boba_Made");
    }

    if (token.equals("part1")) {
      Serial.println("Start1");
      
      part1();

      Serial.println("Done1");
    }

    if (token.equals("part2")) {
      Serial.println("Start2");
      part2();
      Serial.println("Done2");
    }

    if (token.equals("part3")) {
      Serial.println("Start");
      
      part3();

      Serial.println("Done");
    }

    if (token.equals("part4")) {
      Serial.println("Start");
      
      part4();

      Serial.println("Done");
    }

    if (token.equals("part5")) {
      Serial.println("Start");
      
      part5();

      Serial.println("Done");
    }

    if (token.equals("part6")) {
      Serial.println("Start");
      
      part6();
      
      Serial.println("Done");  
    }

    if (token.equals("part7")) {
      Serial.println("Start");
      
      part7();

      Serial.println("Done");
    }
  }
}

void part1() {
  water_to_boba_boiler_pump.on();
  delay(AMOUNT_OF_WATER_TO_BOBA);
  water_to_boba_boiler_pump.off();
}

void part2() {
  for(int i = 0; i < 2; i++) {
    boba_dispense_relay.on();
    delay(1000);
    while(dispense_boba_switch.is_pressed() == false) {
    }
    boba_dispense_relay.off();
  }
}

void part3() {
  delay(BOBA_COOK_TIME_WITH_HEAT);
  //heating_element1.off();
  delay(BOBA_COOK_TIME_WITHOUT_HEAT);
}

void part4() {
  boiling_motor_turn.drive_clockwise(MOTOR_SPEED);
  while(boiling_pot_stop.is_pressed() == false) {
  
  }
  boiling_motor_turn.drive_counter_clockwise(MOTOR_SPEED);
  while(boiling_pot_reset.is_pressed() == false) {
  
  }
  boiling_motor_turn.brake_motor();
}

void part5() {
  sugar_water_pump.on();
  delay(AMOUNT_OF_TIME_TO_PUMP_SUGAR_WATER);
  sugar_water_pump.off();
}

void part6() {
  delay(BOBA_AND_SUGAR_WAIT_TIME);
}

void part7() {
  boba_and_sugar_water_motor.drive_clockwise(MOTOR_SPEED);
  while(sugar_water_pot_stop.is_pressed() == false) {
    
  }
  boba_and_sugar_water_motor.drive_counter_clockwise(MOTOR_SPEED);
  while(sugar_water_pot_reset.is_pressed() == false) {
    
  }
  boba_and_sugar_water_motor.brake_motor();
}

void make_boba() {
  part1();
  part2();
  part3();
  part4();
  part5();
  part6();
  part7();
}

