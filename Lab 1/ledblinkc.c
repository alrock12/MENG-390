#include <avr/io.h>                //import AVR provided libary

int main()                       
{
	unsigned int i = 0;            //initiate counter i as a variable 
	DDRB = 0x20;                   //assign DDRB pin5 to high, output
	  
	while(1)                       //continuously run loop
	{
		for (i=0;i<50000;i++)      //delay program with counter 0-50000
		{PORTB = 0x20;}            //set PORTB pin 5 high, LED on
		for (i=0;i<50000;i++)      //delay
		{PORTB = 0x00;}            //set PORTB pin 5 low, LED off
	}

	return 0;                      //exit
}

