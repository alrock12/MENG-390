/*Robotics with the BOE Shield – ServosOppositeDirections
Generate a servo full speed counterclockwise signal with pin 13 and
full speed clockwise signal with pin 12.
*/

#include <Servo.h> // Include servo library

//Declare Servos
Servo servoLeft;
Servo servoRight; 

//Constants for IR threshold and pin numbers
int threshold = 900;
int leftIR = 1;
int rightIR = 0;

void setup() // Built in initialization block
{
servoLeft.attach(13); // Attach left signal to pin 13
servoRight.attach(12); // Attach right signal to pin 12
servoLeft.writeMicroseconds(1700); // 1.7 ms -> counterclockwise
servoRight.writeMicroseconds(1300); // 1.3 ms -> clockwise
Serial.begin(9600);
}


void loop() // Main loop auto-repeats
{
  //Serial.println(analogRead(leftIR));
  //Serial.println(analogRead(rightIR));
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
