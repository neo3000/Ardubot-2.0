/*
  Ardubot_2_0.ino - Mainframe Firmware for Ardubot-2.0
  Created by M. KOCH, September 2012.
  Version 2.0, rev 0
*/

#include "QTRSensors.h"
#include "engine.h"
#include "config.h"

QTRSensorsRC qtrrc((unsigned char[]) {5, 6, 7, 8, 9, 10}, NUM_OF_SENSORS, TIMEOUT, EMITTER_PIN);

unsigned int sensorValues[NUM_OF_SENSORS];

void setup()
{
  pinMode(STATE_LED, OUTPUT);
  engineSetup();
  
  for (int i = 0; i < CALIBRATION_SPEED; i++)  // the calibration will take a few seconds
  {
    qtrrc.calibrate(QTR_EMITTERS_ON);
    delay(20);
  }
  
  delay(1000);

  set_motors(0,0);
}

int lastError = 0;
int last_proportional = 0;
int integral = 0;


void loop()
{
  unsigned int sensors[5];
  int position = qtrrc.readLine(sensors);
  int error = position - 2000;

  int motorSpeed = KP * error + KD * (error - lastError);
  lastError = error;

  int leftMotorSpeed = M1_DEFAULT_SPEED + motorSpeed;
  int rightMotorSpeed = M2_DEFAULT_SPEED - motorSpeed;

  // set motor speeds using the two motor speed variables above
  set_motors(leftMotorSpeed, rightMotorSpeed);
}

void set_motors(int motor1speed, int motor2speed)
{
  if (motor1speed > M1_MAX_SPEED ) motor1speed = M1_MAX_SPEED; // limit top speed
  if (motor2speed > M2_MAX_SPEED ) motor2speed = M2_MAX_SPEED; // limit top speed
  if (motor1speed < 0) motor1speed = 0; // keep motor above 0
  if (motor2speed < 0) motor2speed = 0; // keep motor speed above 0
  motor_speed_dir(motor1speed, FORWARD);     // set motor speed
  motor_speed_dir(motor2speed, FORWARD);     // set motor speed
}

void led_blink(int Led, int Time, int Numbers){
    digitalWrite(Led, HIGH);
    for(int i = 0; i < Numbers; i++){
      if (digitalRead(Led) == LOW){
        digitalWrite(Led, HIGH);
        }else{
        digitalWrite(Led, LOW);}
      delay(Time);
    }
    digitalWrite(Led, LOW);
  }
