.equ PORTB, 0x05
.equ DDRB,  0x04
.equ PINB,  0x03

.equ TURNON,  0x20
.equ TURNOFF, 0x00

.equ COUNT1, 0x4E           ; outer loop: 78
.equ COUNT2, 0xFF           : inner loop: 255

;SETUP VALUES
init:
	ldi r16, 0x20           ; 
	out DDRB, r16           ; set up PORTB5 to writable
	ldi r16, TURNON         ; 
	out PORTB, r16          ; output PORTB5 high
	ldi r17, 0x00           ; zero value for counter comparisons
	ldi r18, 0x20           ; pin 5 high for toggle ex-or

;TOGGLE LED AND RESET COUNTER
main:
	ldi r29, COUNT1         ; set counter one
	eor r16, r18            ; ex-or to toggle value, store in r16
	out PORTB, r16          ; output toggle value to PORTB5 

;LOOPS FOR COUNTERS
loop: 
	dec r29                 ; decrement counter by 1
	ldi r30, COUNT2         ; set counter 2
	cpse r29, r17           ; skip next line if (counter 1)== 0
	rjmp innerloop          ; go to innerloop if counter 1 is not 0
	brne loop               ; start at loop if (counter 1)!= 0
	rjmp main               ; go to main loop if (counter 1)== 0

innerloop:
	dec r30                 ; decrement counter by 1 
	nop                     ; no operation, one clock cycle
	brne innerloop          ; start at innerloop if (counter 2)!= 0       
	rjmp loop               ; go to loop if (counter 1)== 0




