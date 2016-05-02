//Outputs
//Left Motor pin 10-13, OCR1B
//Right Motor pin 9-12, OCR1A

//Inputs
//Hall Effect Sensor A4
//Gyroscope A5

//Interrupt Code based on assembly values

//EDIT ME
//values to change and tune
unsigned int startForward = 12;
int Kp = 3;
int Ki = 1;
int Kd = 7;


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
unsigned int setpointLow = 527;
unsigned int setpointHigh = 531;

int error = 0;
int dError = 0;
int sumErr = 0;
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
  // int x = calc_left(50);
  // OCR1B = x;
   //Serial.print(OCR1B);
   //bitSet(DDRB, 2);
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

void adc_setup(){
  //initialize ADC for interrupt upon conversion

  ADMUX = B00000100; 
  ADCSRA = B11101010;
  ADCSRB = B00000000;

//  ADCSRA |= (1 << ADATE); //enabble auto trigger
//  ADCSRA |= (1 << ADIE); //enable interrupts when measurement complete
//  ADCSRA |= (1 << ADEN); //enable ADC
//  ADCSRA |= (1 << ADSC); //start ADC measurements
//  ADCSRA |= (1 << ADPS1); //prescaler of 4 for 160 kHz rate of conversion
//  ADMUX  |= (1 << MUX2); //read channel A4 

}


ISR(ADC_vect) {//when new ADC value ready

  //load data
   prevData = newData;
   newData = ADCL | (ADCH << 8);
    
   readFlag = 1;
    
   ADCSRA |= (1 << ADIF);

}

int pid_control(unsigned int hallValue){
  Serial.println(hallValue);
  error = hallValue - setpointHigh;
  Serial.println(error);
  sumErr = error + lastError;
  Serial.println(sumErr);
  dError = error - lastError;
  Serial.println(dError);
  lastError = error;
  
  output = (Kp*error + Ki*sumErr + Kd*dError)/10;
  output += startForward;
  output = constrain(output, -50, 50);
  return output;
 // Serial.println(output);
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



