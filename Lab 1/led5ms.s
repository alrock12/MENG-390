.equ PORTB, 0x05
.equ DDRB, 0x04
.equ PINB, 0x03

.equ TURNON, 0xFF
.equ TURNOFF, 0x00

.equ COUNT1, 0x4E
.equ COUNT2, 0xFF

init:
	ldi r16, 0xFF           ; value for pin 5 writable
	out DDRB, r16           ; set up PORTB5 to writable
	ldi r16, TURNOFF        ; value for pin 5 high output
	out PORTB, r16          ; output PORTB5 high
	ldi r17, 0x00           ; zero value for counter comparisons
	ldi r18, 0xFF           ; pin 5 high for toggle xor

main:
	ldi r29, COUNT1         ; set counter one
	eor r16, r18            ; xor to toggle value
	out PORTB, r16          ; output toggle PORTB5 

loop: 
	dec r29                 ; decrement counter 1
	ldi r30, COUNT2         ; set counter 2
	cpse r29, r17           ; skip next line if values equal, compare counter1 to 0
	rjmp innerloop          ; go to innerloop if counter 1 is not 0
	brne loop               ; start at loop if counter 1 != 0
	rjmp main               ; go to main loop if counter 1 == 0

innerloop:
	dec r30                   ; 1 
	nop                       ; 1
	brne innerloop            ; 2 end 1        
	rjmp loop                 ; 2




