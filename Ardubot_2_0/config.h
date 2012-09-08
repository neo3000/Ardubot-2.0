/*
  config.h - Library for configure the Ardubot.
  Created by M. KOCH, September 2012.
  Version 1, rev 0
*/

#ifndef config_h
#define config_h

//QTR Sensors
#define NUM_OF_SENSORS 6
#define MIDDLE_POS (((NUM_OF_SENSORS*1000) - 1000) / 2)
#define MIDDLE_SENSOR 3
#define EMITTER_PIN 1
#define TIMEOUT 2500
#define CALIBRATION_SPEED 250

//PID Control
#define KP 0.2
#define KD 5

//LEDs
#define STATE_LED 2

//Engine
#define FORWARD_MAX 70
#define REVERSE_MAX 20
#define M1_MAX_SPEED 70
#define M2_MAX_SPEED 70
#define M1_DEFAULT_SPEED 40
#define M2_DEFAULT_SPEED 40

#endif

