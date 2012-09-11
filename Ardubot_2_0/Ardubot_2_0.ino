/*
  Ardubot_2_0.ino - Mainframe Firmware for Ardubot.
  Created by M. KOCH, September 2012.
  Version 2, rev 1
  Arduino rev3, IDE 1.0.1
  OPEN SOURCE
*/

#include "QTRSensors.h"
#include "config.h"

int Error = 0;
int LastError = 0;
int MotorSpeed = 0;
int Output = 0;

//--------------------------------------------------------------------------------------------
QTRSensorsRC qtrrc((unsigned char[]) {5,6,7,8,9,10} ,NUM_SENSORS, TIMEOUT, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];

void setup()
{
  Serial.begin(9600);
  delay(1000);
  manual_calibration(); 
  set_motors(0,0, FWD);
}

void loop()
{
  unsigned int Sensors[5];
  int position = qtrrc.readLine(Sensors);
  Error = position - 2000;

  Output = KP * Error + KD * (Error - LastError);
  LastError = Error;
  
  if(DEBUG == 1){
    debug_mode();
    Serial.println('\n');
    Serial.print(qtrrc.readLine(Sensors));
    Serial.println('\n');
  }else{
    int Motor1NewSpeed = MOTOR1_NORMAL_SPEED + Output;
    int Motor2NewSpeed = MOTOR2_NORMAL_SPEED - Output;
    set_motors(Motor1NewSpeed, Motor2NewSpeed, FWD);
  }
}

void set_motors(int Motor1Speed, int Motor2Speed, int MotorDirection)
{
  if (Motor1Speed > MOTOR1_MAXIMAL_SPEED ){Motor1Speed = MOTOR1_MAXIMAL_SPEED;}
  if (Motor2Speed > MOTOR2_MAXIMAL_SPEED ){Motor2Speed = MOTOR2_MAXIMAL_SPEED;}
  if (Motor1Speed < 0){Motor1Speed = 0;}
  if (Motor2Speed < 0){Motor2Speed = 0;}
  analogWrite(PwmPinMotorA, Motor1Speed);
  analogWrite(PwmPinMotorB, Motor2Speed);
  
  if(MotorDirection == FWD){
  digitalWrite(DirectionPinMotorA, HIGH);
  digitalWrite(DirectionPinMotorB, HIGH);
  }
  if(MotorDirection == REV){
  digitalWrite(DirectionPinMotorA, LOW);
  digitalWrite(DirectionPinMotorB, LOW);
  }  
}

void manual_calibration() {
  for (int i = 0; i < 250; i++)
  {
    qtrrc.calibrate(QTR_EMITTERS_ON);
    delay(5);
  }
}

void debug_mode(){
    for (int i = 0; i < NUM_SENSORS; i++)
    {
      Serial.print(qtrrc.calibratedMinimumOn[i]);
      Serial.print(' ');
    }
    Serial.println();

    for (int i = 0; i < NUM_SENSORS; i++)
    {
      Serial.print(qtrrc.calibratedMaximumOn[i]);
      Serial.print(' ');
    }
    Serial.println();
    Serial.println();
    delay(DEBUG_OUPUT_SPEED);
}
