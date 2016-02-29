


;locations of registers associated with LED
.equ PORTB, 0x05
.equ DDRB, 0x04

;constants to toggle the value of Pin 5 0b00x00000
.equ TURNON, 0x20
.equ TURNOFF, 0x00

main:
	ldi r16, 0x20           ; setup pin 5 port B to writable
	out DDRB, r16           ;
	ldi r16, TURNON         ; set r16 as value to output to PORTB
	out PORTB, r16          ;
	rjmp main               ; return to label main

