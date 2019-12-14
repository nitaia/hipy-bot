#include <Servo.h>

Servo myservo;

//varibal setup:
int sensor[7] = {0};
const int want = 90;
int real = 0;
int turnTo = 0;
int sum = 0;
int avr = 0;
int sensorB = 0;
const int velocity = 100;

void setup()
{
  // setup
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  myservo.attach(12);
  Serial.begin(9600);  
}

void loop()
{
  //sensor chack
  
  sensor[0] = analogRead(0);
  sensor[1] = analogRead(1);
  sensor[2] = analogRead(2);
  sensor[3] = analogRead(3);
  sensor[4] = analogRead(4);
  sensor[5] = analogRead(5);
  sensor[6] = analogRead(6);

  //sensor average
  sensorB = 0;
  sum = 0;
  for(int i = 0; i < 7; i++)
  {
    if(BorW(sensor[i]) == 1)
    {
      sum += i;
      sensorB++;
    }
  }
  avr = sum / sensorB;
  
  //set reality
  real = avr * (90 / 3);

  //set turnTo
  turnTo = want - real;
  if(turnTo < 0)
  {
    turnTo *= -1;
  }

  //Turn
  Turn(turnTo);

  //Move forward
  Move(velocity);
}

//-----------------------------------------------------------------------------------------------------------------------------------------------

int BorW(int a)
{
  // 0 is white, 1 is black
  return a >= 90 ? 0 : 1;
}

void Turn(float steps)
{
  myservo.write(steps);
}

void Move(int a)
{
  //move the robot;
  analogWrite(8, 0);
  analogWrite(9, a);
}
