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

//Declare Servos
Servo servoLeft;
Servo servoRight; 

//Constants for threshold and pin numbers
int threshold = 900;
int leftIR = 2;
int rightIR = 3;
int leftMotor = 10;
int rightMotor = 9;

void setup() // Built in initialization block
{
servoLeft.attach(leftMotor); // Attach left signal to pin 13
servoRight.attach(rightMotor); // Attach right signal to pin 12
servoLeft.writeMicroseconds(1700); //Start motors by running them forward
servoRight.writeMicroseconds(1300); 
Serial.begin(9600);
}


void loop() // Main loop auto-repeats
{
  //Serial.println(analogRead(leftIR)); //For debugging and calibration
  //Serial.println(analogRead(leftIR)); //Commented out when not in use
  if (analogRead(leftIR)<threshold){    // When the left IR sees black/triggered
   
   servoLeft.writeMicroseconds(1500);  //Left Motor stays still
   servoRight.writeMicroseconds(1400); //Right Motor corrects
   delay(50);                          //Pause for correction
 }
 else {servoLeft.writeMicroseconds(1700);} //Else keep true
 

 if (analogRead(rightIR)<threshold){   //When the right IR sees black/triggered
  
   servoRight.writeMicroseconds(1500); //Right motor stays still
   servoLeft.writeMicroseconds(1600);  // Left motor corrects
   delay(50);                          //Pause for correction
 }
 else{servoRight.writeMicroseconds(1300);} //Else keep true
}

