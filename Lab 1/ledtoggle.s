.equ PORTB, 0x05
.equ DDRB, 0x04
.equ PINB, 0x03

.equ TURNON, 0x20
.equ TURNOFF, 0x00

main:
	ldi r16, 0x20           ; Setup pin 5 port B to writable
	out DDRB, r16           ;
	ldi r16, TURNOFF        ; Replace with TURNOFF
	out PORTB, r16          ;
	sbi PINB, 5             ; Toggle by triggering PINB5



 