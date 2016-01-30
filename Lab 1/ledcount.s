.equ PORTB, 0x05
.equ DDRB, 0x04
.equ PINB, 0x03

.equ TURNON, 0xFF
.equ TURNOFF, 0x00

.equ COUNT1, 0xFF
.equ COUNT2, 0xFF
.equ COUNT3, 0xFF

init:
	ldi r16, 0xFF           ; Setup pin 5 port B to writable
	out DDRB, r16           ;
	ldi r16, TURNOFF        ; Replace with TURNOFF
	out PORTB, r16          ;
	ldi r17, 0x00
	ldi r18, 0xFF

main:
	ldi r29, COUNT1
	eor r16, r18
	out PORTB, r16

loop: 
	dec r29
	ldi r30, COUNT2
	cpse r29, r17
	rjmp innerloop
	brne loop
	rjmp main

innerloop:
	dec r30
	ldi r31, COUNT3
	cpse r30, r17
	rjmp innermostloop
	brne innerloop
	rjmp loop

innermostloop:
	dec r31
	brne innermostloop
	rjmp innerloop




