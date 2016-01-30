.equ PORTB, 0x05
.equ DDRB, 0x04
.equ TURNON, 0xFF
.equ TURNOFF, 0x00

main:
	ldi r16, 0xFF           ; Setup pin 5 port B to writable
	out DDRB, r16           ;
	ldi r16, TURNOFF        ; Replace with TURNOFF
	out PORTB, r16          ;
	rjmp main               ;   

