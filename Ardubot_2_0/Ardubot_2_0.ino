#include <QTRSensors.h>
#include <AFMotor.h>

AF_DCMotor motor1(1, MOTOR12_8KHZ ); // PIN 11 - create motor #1 pwm
AF_DCMotor motor2(2, MOTOR12_8KHZ ); // PIN 3 - create motor #2 pwm

// Change the values below to suit your robot's motors, weight, wheel type, etc.
#define KP .2
#define KD 5
#define M1_DEFAULT_SPEED 50
#define M2_DEFAULT_SPEED 50
#define M1_MAX_SPEED 70
#define M2_MAX_SPEED 70
#define MIDDLE_SENSOR 3
#define NUM_SENSORS  5      // number of sensors used
#define TIMEOUT       2500  // waits for 2500 us for sensor outputs to go low
#define EMITTER_PIN   2     // emitter is controlled by digital pin 2
#define DEBUG 0 // set to 1 if serial debug output needed

QTRSensorsRC qtrrc((unsigned char[]) {  18,17,16,15,14} ,NUM_SENSORS, TIMEOUT, EMITTER_PIN);

unsigned int sensorValues[NUM_SENSORS];

void setup()
{
  delay(1000);
  manual_calibration(); 
  set_motors(0,0);
}

int lastError = 0;
int  last_proportional = 0;
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
  motor1.setSpeed(motor1speed);     // set motor speed
  motor2.setSpeed(motor2speed);     // set motor speed
  motor1.run(FORWARD);  
  motor2.run(FORWARD);
}


void manual_calibration() {

  int i;
  for (i = 0; i < 250; i++)  // the calibration will take a few seconds
  {
    qtrrc.calibrate(QTR_EMITTERS_ON);
    delay(20);
  }

  if (DEBUG) { // if true, generate sensor dats via serial output
    Serial.begin(9600);
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
  }
}
