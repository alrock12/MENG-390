//Adafruit Sample Code for Gyro

#include <Wire.h> 
#include <Adafruit_L3GD20.h>

// No need to specify pins for I2C
Adafruit_L3GD20 gyro;

void setup() 
{
  Serial.begin(9600);
  
  // Try to initialise and warn if we couldn't detect the chip
  if (!gyro.begin(gyro.L3DS20_RANGE_250DPS))          //range can be 250,500, or 2000 degrees per second
  {
    Serial.println("Oops ... unable to initialize the L3GD20. Check your wiring!");
    while (1);
  }
}

void loop() 
{
  gyro.read();
  //records a data point of [x,y,z] in degrees-per-second
  Serial.print("X: "); Serial.print((int)gyro.data.x);   Serial.print(" ");
  Serial.print("Y: "); Serial.print((int)gyro.data.y);   Serial.print(" ");
  Serial.print("Z: "); Serial.println((int)gyro.data.z); Serial.print(" ");
  delay(100);
}





