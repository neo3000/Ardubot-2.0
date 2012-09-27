/*
  config.h - Library for configure the Ardubot.
  Created by M. KOCH, September 2012.
  Version 2, rev 1
  OPEN SOURCE
*/

#ifndef config_h
#define config_h

//PID Control
#define KP .19
#define KD 6

//Engine System
#define MOTOR1_NORMAL_SPEED 60
#define MOTOR2_NORMAL_SPEED 60
#define MOTOR1_MAXIMAL_SPEED 65
#define MOTOR2_MAXIMAL_SPEED 65

//Engine Navigation
#define FWD 0 //Vorwärts
#define REV 1 //Rückwärts

//Engine Connection and PWM
#define PwmPinMotorA 3
#define PwmPinMotorB 11
#define DirectionPinMotorA 12
#define DirectionPinMotorB 13

//IR Sensor
#define NUM_SENSORS 4 // Anpassen !! Anzahl an verwendeten Sensoren
#define TIMEOUT 1500
#define EMITTER_PIN 2

//Debug Mode
#define DEBUG_OUPUT_SPEED 500 // Debug Ausgabe Geschwindigkeit
#define PROGRAMCABLE 4
#define STATUS_LED A0

#endif

