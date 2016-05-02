//Outputs
//Left Motor pin 10-13, OCR1B
//Right Motor pin 9-12, OCR1A

//Inputs
//IR Outer Left A0
//IR Inner Left A1
//IR Inner Right A2
//IR Outer Right A3


//Interrupt Code based on assembly values

//EDIT ME
//values to change and tune
unsigned int startForward = 50;
int Kp = 3;
int Ki = 1;
int Kd = 7;
unsigned int setpoint = 0;


//PWM constants
unsigned int top = 5000;
unsigned int freq = 50;
float dutyMid  = 0.07;
int pwmValue = 0;

//Driving Constants
int rightMotr OCR1A;
int leftMotor OCR1B;
unsigned int leftSpeed;
unsigned int rightSpeed;

int rpmOutput = 50;

//ADC Constants
unsigned int prevLeftOuter = 0;
unsigned int prevLeftInner = 0;
unsigned int prevRightInner = 0;
unsigned int prevRightOuter = 0;
unsigned int LeftOuterValue = 0;
unsigned int RightOuterValue = 0;
unsigned int LeftInnerValue = 0;
unsigned int RightInnerValue = 0;

//PID Constants
int error = 0;
int dError = 0;
int sumErr = 0;
int lastError = 0;
int output =0;

//IR Constants
int threshold = 900;
int outerweight = 2;

void setup(){
  cli(); //stop all interrupts
  pwm_setup();
  sei();
  Serial.begin(9600); 
}

void loop(){
  LeftOuterValue = analogRead(A0);
  LeftInnerValue = analogRead(A1);
  RightInnerValue = analogRead(A2);
  RightOuterValue = analogRead(A3);
  Serial.println(LeftOuterValue);
  
  if (RightOuterValue < threshold){
    leftSpeed = calc_left(-25);
    rightSpeed = calc_right(0);
    delay(50);    
  }
  if (LeftOuterValue < threshold){
    leftSpeed = calc_left(0);
    rightSpeed = calc_right(-25);
    delay(50);    
  }
  
  else{
    leftSpeed = calc_left(startForward);
    rightSpeed = calc_right(startForward);
  }
    OCR1A = rightSpeed; 
    bitSet(DDRB, 1);
    OCR1B = leftSpeed;
    bitSet(DDRB, 2);
 
}



void pwm_setup(){
  //initialize 16-bit timer, Timer 1
  //OCR1A = pin 9
  //OCR1B = pin 10
  
   TCCR1A = 0;
   TCCR1B = 0;
   TCNT1  = 0;

   TCCR1A |= (1 << COM1A1); //setup non-inverting mode for OCR1A
   TCCR1A |= (1 << COM1B1); //setup non-inverting mode for OCR1B
   TCCR1A |= (1 << WGM11);
   TCCR1B |= (1 << WGM13)|(1<< WGM12); //fast PWM mode
   TCCR1B |= (1 << CS10)|(1 << CS11); //internal clock, /64 prescaling
  
    ICR1 = top ; //set top value for frequency of 50 Hz
 

    //start driving forward
    OCR1A = calc_right(startForward);
    bitSet(DDRB, 1);
    OCR1B = calc_left(startForward);
    bitSet(DDRB, 2);
}
//
//int pid_control(unsigned int Position){
// // Serial.println(position);
//  error = Position - setpoint;
// // Serial.println(error);
//  sumErr += error;
//  //Serial.println(sumErr);
//  dError = error - lastError;
// // Serial.println(dError);
//  lastError = error;
//  
//  output = (Kp*error + Ki*sumErr + Kd*dError)/32;
//  output = constrain(output, -50, 50);
//  return output;
// // Serial.println(output);
//}

int calc_left(double rpm){
  double x = (rpm/50)*10+75;
  unsigned int pwmValue = top * x/1000;
  return pwmValue;
}

int calc_right(double rpm){
  double x = (rpm/50)*-10+75;
  unsigned int pwmValue = top * x/1000;
  return pwmValue;
}



