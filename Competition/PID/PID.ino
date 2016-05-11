//Outputs
//Left Motor pin 10-13, OCR1B
//Right Motor pin 9-12, OCR1A

//Inputs
//Hall Effect Sensor A4
//Gyroscope 

//values to change and tune
unsigned int startForward = 25;
float Kp = 8;
float Ki = 0;
float Kd = 0;
unsigned int setpointLow = 510;
unsigned int setpointHigh = 525;

//PWM constants
unsigned int top = 5000;
unsigned int freq = 50;
float dutyMid  = 0.07;
int pwmValue = 0;

//Driving Constants
int rightMotr OCR1A;
int leftMotor OCR1B;
unsigned int left_speed;
unsigned int right_speed;

int rpmOutput = 50;

//ADC Constants
unsigned int prevData = 0;
unsigned int prevDataL = 0;
unsigned int newData = 0;
unsigned int newDataL = 0;
int readFlag = 0;

//PID Constants
int error = 0;
int dError = 0;
double sumErr = 0;
int lastError = 0;
int output =0;

void setup(){
  cli(); //stop all interrupts
  ADCH = 0;
  ADCL = 0;
  pwm_setup();
  adc_setup();  
  sei();
  Serial.begin(9600); 
}

void loop(){
  if (readFlag == 1){
    rpmOutput = pid_control(newData);
    Serial.print("output:");
    Serial.println(rpmOutput);
    OCR1A = calc_right(rpmOutput);
    Serial.print("ocr1a");
    Serial.println(OCR1A);    
    bitSet(DDRB, 1);
    OCR1B = calc_left(rpmOutput);
    bitSet(DDRB, 2);
    readFlag = 0;
  }
}

void pwm_setup(){
  
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

void adc_setup(){
  //initialize ADC for interrupt upon conversion

  ADMUX = B00000100; 
  ADCSRA = B11101010;
  ADCSRB = B00000000;

}


ISR(ADC_vect) {//when new ADC value ready

  //load data
   prevData = newData;
   newData = ADCL | (ADCH << 8);
    
   readFlag = 1;
    
   ADCSRA |= (1 << ADIF);

}

int pid_control(unsigned int hallValue){
  Serial.print("Hall");
  Serial.println(hallValue);
  if(hallValue < setpointLow || hallValue > setpointHigh){
  error = min((hallValue-setpointHigh),(hallValue - setpointLow));
  Serial.println(error);
  sumErr += error ;
  Serial.println(sumErr);
  dError = error - lastError;
  Serial.println(dError);
  lastError = error;
  
  output = (Kp*error + Ki*sumErr + Kd*dError)/10;
 if(output >0){ output += startForward;}
  output = constrain(output, -50, 50);
  return output;}
  else{return 0;}
}



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

