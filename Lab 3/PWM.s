;Define relative addresses of registers
.equ DDRD , 0x0A      ;Date Direction Register of PORTD
.equ TCCR0A , 0x24    ;Time Counter Control Register 0A
.equ TCCR0B , 0x25    ;Time Counter Control Register 0B
.equ OCR0A , 0x27     ;Output Compare Register  0A

.org 0x0000
	rjmp init
.org 0x0032        ;First memory address after the interrupt vector table

start:
	ldi r16 , 254  ;Some random code to keep the CPU busy.

main :
	nop                     ;consumes on clock cycle
	dec r16                 ;decrement register r16
	rjmp main               ;stay in loop

init :
	ldi r16 , 0b01000011    ;PWM settings 
	out TCCR0A , r16        
	ldi r16 , 0b00001001    ;PWM settings
	out TCCR0B , r16
	ldi r16 , 0           ; output compare value
	out OCR0A , r16         ;
	sbi DDRD , 6            ;set Data Direction Register, pin 6 of Port D 
	rjmp start              ;return from subroutine
