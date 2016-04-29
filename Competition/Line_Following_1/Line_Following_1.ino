
//Outputs
//Left Motor pin 10-13
//Right Motor pin 9-12

//Inputs
//Gyroscope A0
//Hall Effect Sensor A1
//Left Outer IR Sensor A5
//Left Inner IR/Center Sensor A4
//Right Inner IR Sensor A3
//Right Outer IR Sensor A2


#include <Servo.h> // Include servo library


//Pseudo Code

//Setup 4 IR Sensors
//Set up Gyro Scope
//Set up Hall Effect Sensor

//Set up 2 servo motors
//Controlled by PWM



/*Robotics with the BOE Shield – ServosOppositeDirections
Generate a servo full speed counterclockwise signal with pin 13 and
full speed clockwise signal with pin 12.
*/

#include <Servo.h> // Include servo library

//Declare Servos
Servo servoLeft;
Servo servoRight; 

//Constants for threshold and pin numbers
int threshold = 900;
int leftIR = 4;
int rightIR = 2;
int leftMotor = 10;
int rightMotor = 9;

void setup() // Built in initialization block
{
servoLeft.attach(leftMotor); // Attach left signal to pin 13
servoRight.attach(rightMotor); // Attach right signal to pin 12
servoLeft.writeMicroseconds(1700); // 1.7 ms -> counterclockwise
servoRight.writeMicroseconds(1300); // 1.3 ms -> clockwise
Serial.begin(9600);
}


void loop() // Main loop auto-repeats
{
  //Serial.println(analogRead(leftIR));
  Serial.println(analogRead(leftIR));
  if (analogRead(leftIR)<threshold){
   servoLeft.writeMicroseconds(1500);;
 }
 else {servoLeft.writeMicroseconds(1700);}
 
//if left IR sees black, turn off left LED 
 if (analogRead(rightIR)<threshold){
   servoRight.writeMicroseconds(1500);
 }
 else{servoRight.writeMicroseconds(1300);}
}





//1. Circuit Race

//stay within two blacks
// - straight
// - slight turns
// - cross-overs/gaps
// - bang turns
// - hair pin turns



