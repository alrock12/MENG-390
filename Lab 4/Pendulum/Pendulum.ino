//Adafruit Sample Code for Gyro

#include <Wire.h> 
#include <Adafruit_L3GD20.h>

// No need to specify pins for I2C
Adafruit_L3GD20 gyro;


int z_pin = 10;
int z_dps = 0;
long int z_pwm = 0;

void setup() 
{
  Serial.begin(9600);
  
  // Try to initialise and warn if we couldn't detect the chip
  if (!gyro.begin(gyro.L3DS20_RANGE_2000DPS))          //range can be 250,500, or 2000 degrees per second
  {
    Serial.println("Oops ... unable to initialize the L3GD20. Check your wiring!");
    while (1);
  }
}

void loop() 
{
  gyro.read();
  //records a data point of [x,y,z] in degrees-per-second
  //Serial.print("Z: "); Serial.println(gyro.data.z); Serial.print(" ");
  delay(10);
  z_dps = gyro.data.z;//only read magnitude;
  z_pwm = (z_dps+512)/4; 
  //Serial.print("z_pwm:  "); 
  Serial.println(z_pwm);Serial.print(" ");
  analogWrite(z_pin, z_pwm);
  
}
