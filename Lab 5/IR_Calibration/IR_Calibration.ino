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
int newIRreading = 0;
int lastIRreading = 0;
int time = 0;
int lastTime = 0;
int period = 0;

void setup() // Built in initialization block
{
servoLeft.attach(13); // Attach left signal to pin 13
servoRight.attach(12); // Attach right signal to pin 12
servoLeft.writeMicroseconds(Serial.read()); // 1.7 ms -> counterclockwise
servoRight.writeMicroseconds(1500); // 1.3 ms -> clockwise
Serial.begin(9600);
}


void loop() // Main loop auto-repeats
{
 newIRreading = analogRead(leftIR);
 //Serial.println(newIRreading);
 time = millis();
 if (lastIRreading < 900 && newIRreading > 900){
   period = time - lastTime;
   Serial.println(period);
   lastTime = time;
 }
 lastIRreading = newIRreading;  
}
