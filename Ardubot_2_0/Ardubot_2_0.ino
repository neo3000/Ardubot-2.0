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
int MaximumPoint = (NUM_SENSORS - 1) * 1000;
int SetPoint = MaximumPoint / 2;
int Output;
int Position;
//--------------------------------------------------------------------------------------------
//  Sensors [i]  |  0  |  1  |  2  |  3  |  4  | 5  |
//  Pins [i+5]   |  5  |  6  |  7  |  8  |  9  | 10 |
//--------------------------------------------------------------------------------------------
unsigned char SensorArray[NUM_SENSORS];


//Initiation
void setup()
{
  
 switch  (NUM_SENSORS) {
  case 2:
   SensorArray[0] = 7;SensorArray[1] = 8;
  break; 
  case 4:
   SensorArray[0] = 6;SensorArray[1] = 7;SensorArray[2] = 8;SensorArray[3] = 9;
  break;
  case 6:
   SensorArray[0] = 5;SensorArray[1] = 6;SensorArray[2] = 7;SensorArray[3] = 8;SensorArray[4] = 9;SensorArray[5] = 10;
  break;
 }
  
  Serial.begin(9600); // Serial init
  
  pinMode(PROGRAMCABLE, INPUT);  //Programmer Cable Pin
  
  pinMode(PwmPinMotorA, OUTPUT);
  pinMode(PwmPinMotorB, OUTPUT);
  pinMode(DirectionPinMotorA, OUTPUT);
  pinMode(DirectionPinMotorB, OUTPUT);
  
  pinMode(EMITTER_PIN, OUTPUT);
  pinMode(STATUS_LED, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  
  digitalWrite(1, HIGH);
  
  delay(300);
  manual_calibration(); //Sensor calibration
  delay(500);
  
  set_motors(0,0, FWD);
}

QTRSensorsRC qtrrc(SensorArray, NUM_SENSORS, TIMEOUT, EMITTER_PIN);
//Mainframe
void loop()
{
  unsigned int Sensors[NUM_SENSORS];
  Position = qtrrc.readLine(Sensors);
  Error = Position - SetPoint;

  Output = KP * Error + KD * (Error - LastError);
  LastError = Error;
  
  if(digitalRead(PROGRAMCABLE) == HIGH){
    set_motors(0,0, FWD);
    delay(200);
    digitalWrite(STATUS_LED, HIGH);
    delay(200);
    digitalWrite(STATUS_LED, LOW);
  } 
  
  if(DEBUG == 1){
    debug_mode();
  }else{
    if(Position == 0 || Position == MaximumPoint){
    set_motors(0, 0, FWD);
    }else{
    int Motor1NewSpeed = MOTOR1_NORMAL_SPEED + Output;
    int Motor2NewSpeed = MOTOR2_NORMAL_SPEED - Output;
    set_motors(Motor1NewSpeed, Motor2NewSpeed, FWD);
    }
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
  digitalWrite(STATUS_LED, HIGH);
  for (int i = 0; i < 250; i++)
  {
    qtrrc.calibrate(QTR_EMITTERS_ON);
    delay(10);
  }
  digitalWrite(STATUS_LED, LOW);
}

void debug_mode(){
    Serial.print("Min: ");
    for (int i = 0; i < NUM_SENSORS; i++)
    {
      Serial.print(qtrrc.calibratedMinimumOn[i]);
      Serial.print(' ');
    }
    Serial.println();
    
    Serial.print("Max: ");
    for (int i = 0; i < NUM_SENSORS; i++)
    {
      Serial.print(qtrrc.calibratedMaximumOn[i]);
      Serial.print(' ');
    }
    Serial.print('\n');    
    
    Serial.print("Output: ");
    Serial.print(Output);
    Serial.print('\n');    
    Serial.print("Position: ");
   Serial.print(Position);
    Serial.print('\n');
    Serial.print("----------------------------------");
    Serial.print('\n');
    delay(DEBUG_OUPUT_SPEED);
}
