/*
 *    
 */
#include<Servo.h>
#include<PID_v1.h>
#include "SR04.h"


const int servoPin = 9; 
//// tuning PID here
float Kp = 0.3; // Proportional Gain
float Ki = 0.1; // Integral Gain
float Kd =  0.5; // Derivative Gain
double Setpoint, Input, Output, ServoOutput;


PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT); //Initialize PID object, which is in the class PID.
Servo myServo; //Initialize Servo.
float readPosition();

void setup(){
  Serial.begin(9600); //Begin Serial
  myServo.attach(servoPin); //Attach Servo
  Input = readPosition(); //Calls function readPosition() and sets the balls
  // position as the input to the PID algorithm
  myPID.SetMode(AUTOMATIC); //Set PID object myPID to AUTOMATIC
  myPID.SetOutputLimits(-60,60); //Set Output limits 
}

void loop(){
  Setpoint = 15; /////can be adjusted between 5cm & 25m
  Input = readPosition();
  myPID.Compute(); //computes Output in range of -80 to 80 degrees
  ServoOutput=40+Output; // 40 degrees is the horizontal, can change depending on the current angle of the motor
  myServo.write(ServoOutput); //Writes value of Output to servo
}

float readPosition() {
  
  delay(40); //should not be set too low or echos will run into eachother.
  
  const int pingPin = 7; //Trig Pin 
  const int pingPin2 = 6; //Echo Pin 
  long duration, cm;
  unsigned long now = millis();
  
  pinMode(pingPin, OUTPUT);   
  digitalWrite(pingPin, LOW);  
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);  
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin2, HIGH);
  cm = duration/(29*2);
  if(cm > 30) // 30 cm is the maximum position for the ball // make 35
  {
    cm=25;
  } // make 30
  Serial.println(cm);
  return cm; //Returns distance value.
}
