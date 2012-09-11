/*
  config.h - Library for configure the Ardubot.
  Created by M. KOCH, September 2012.
  Version 2, rev 1
  OPEN SOURCE
*/

#ifndef config_h
#define config_h

//PID Control
#define KP 0.2
#define KD 5

//Engine System
#define MOTOR1_NORMAL_SPEED 50
#define MOTOR2_NORMAL_SPEED 50
#define MOTOR1_MAXIMAL_SPEED 70
#define MOTOR2_MAXIMAL_SPEED 70

//Engine Navigation
#define FWD 0
#define REV 1

//Engine Connection and PWM
#define PwmPinMotorA 3
#define PwmPinMotorB 11
#define DirectionPinMotorA 12
#define DirectionPinMotorB 13

//IR Sensor
#define NUM_SENSORS 5
#define TIMEOUT 1000
#define EMITTER_PIN 2

//Debug Mode
#define DEBUG 1
#define DEBUG_OUPUT_SPEED 500
#endif

