/*
  SMART DUSTBIN
  THIS IS A CODE FOR MAKING A SMART DUSTBIN WHICH OPENS AND CLOSES AUTOMATICALLY.
  IF DISTANCE IS LESS THAN 50 CM THEN LID OF DUSTBIN IS OPENED FOR 3.5 SECONDS AND THEN CLOSED
*/

#include <Servo.h>  //INCLUDES SERVO LIBRARY

Servo servo;
int trig = 5;
int echo = 6;
int servoPin = 9;
long duration, distance, average;
long aver[3];

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  servo.write(0); //CLOSES CAP ON STARTING
  delay(100);
  servo.detach();
}

void measure() {
  digitalWrite(trig, LOW);
  delayMicroseconds(5);
  digitalWrite(trig, HIGH);
  delayMicroseconds(15);
  digitalWrite(trig, LOW);
  pinMode(echo, INPUT);
  duration = pulseIn(echo, HIGH);
  distance = (duration / 2) / 29.1; //CALCULATES DISTANCE
}

void loop() {
  Serial.println(distance);     //CAN BE DISABLED
  for (int i = 0; i <= 2; i++) { //CALCULATES AVERAGE DISTANCE
    measure();
    aver[i] = distance;
    delay(10);
  }
  distance = (aver[0] + aver[1] + aver[2]) / 3;

  if ( distance <= 50 ) { //CHANGE AS PER AS NEED
    servo.attach(servoPin);
    delay(1);
    servo.write(0);
    delay(3500); //CHANGE AS PER AS NEED
    servo.write(180);
    delay(1500); //CHANGE AS PER AS NEED
    servo.detach();
  }
}