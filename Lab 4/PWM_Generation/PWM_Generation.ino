//Adafruit Sample Code for Gyro

#include <Wire.h> 
#include <Adafruit_L3GD20.h>

// No need to specify pins for I2C
Adafruit_L3GD20 gyro;


int x_pin = 3;
int x_dps = 0;
int x_pwm = 0;
int y_pin = 9;
int y_dps = 0;
int y_pwm = 0;
int z_pin = 10;
int z_dps = 0;
int z_pwm = 0;

void setup() 
{
  Serial.begin(9600);
  
  // Try to initialise and warn if we couldn't detect the chip
  if (!gyro.begin(gyro.L3DS20_RANGE_500DPS))          //range can be 250,500, or 2000 degrees per second
  {
    Serial.println("Oops ... unable to initialize the L3GD20. Check your wiring!");
    while (1);
  }
}

void loop() 
{
  gyro.read();
  //records a data point of [x,y,z] in degrees-per-second
  Serial.print("X: "); Serial.print(gyro.data.x);   Serial.print(" ");
  Serial.print("Y: "); Serial.print(gyro.data.y);   Serial.print(" ");
  Serial.print("Z: "); Serial.println(gyro.data.z); Serial.print(" ");
  delay(100);
  x_dps = abs(gyro.data.x);//only read magnitude;
  x_pwm = x_dps*255/575; 
  analogWrite(x_pin, x_pwm);
  y_dps = abs(gyro.data.y);//only read magnitude;
  y_pwm = y_dps*255/575; 
  analogWrite(y_pin, y_pwm);
  z_dps = abs(gyro.data.z);//only read magnitude;
  z_pwm = z_dps*255/575; 
  analogWrite(z_pin, z_pwm);
  
}
