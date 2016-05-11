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

//Set up 2 servo motors
//Controlled by PWM

#include <Servo.h> // Include servo library

//Declare Servos
Servo servoLeft;
Servo servoRight; 

//Constants for threshold and pin numbers
int threshold = 900; //Calibrated threshold value for above/below viewing black
int leftIR = 1;
int rightIR = 2;
int leftMotor = 10;
int rightMotor = 9;

void setup() // Built in initialization block
{
servoLeft.attach(leftMotor); // Attach left signal to pin 13
servoRight.attach(rightMotor); // Attach right signal to pin 12
servoLeft.writeMicroseconds(1700); // Start the robot with a command to go forward
servoRight.writeMicroseconds(1300); 
Serial.begin(9600);
}


void loop() // Main loop auto-repeats
{
  Serial.println(analogRead(leftIR));  //For debugging and calibration
  Serial.println(analogRead(rightIR)); //For debugging and calibration
  if (analogRead(leftIR)<threshold){ //When the left IR is triggered/hits black
   servoRight.writeMicroseconds(1575); // Wheel spins backward
   servoLeft.writeMicroseconds(1550); //Wheel spins forward 
   delay(50); // Short delay to allow for the correction to take place
 }
 else {servoLeft.writeMicroseconds(1700);} // Normal forward command
 
//if left IR sees black, turn off left LED 
 if (analogRead(rightIR)<threshold){ //When the right IR is triggered/hits black
  
   servoRight.writeMicroseconds(1450); //Wheel spins forward
   servoLeft.writeMicroseconds(1425);  //Wheel spins backward
   delay(50); // Short delay to allow for the correction to take place
 }
 else{servoRight.writeMicroseconds(1300);} //Normal forward command
}

