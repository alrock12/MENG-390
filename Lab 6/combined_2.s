
;-----------------------------SETUP-----------------------------
; Set Stack Pointer Register (16-bit: high and low) to end of SRAM 
; Stack is used to store and restore the program counter location when going to an interrupt or subroutine
.equ SPH , 0x3E
.equ SPL , 0x3D
.equ RAMEND , 0x08FF 

; I/O Registers
.equ PINB , 0x03
.equ DDRB , 0x04
.equ PORTB , 0x05
.equ DDRD , 0x0A
.equ PORTD , 0x0B
.equ SREG , 0x3F 

; I/O bits
.equ B5 , 5
.equ INT0 , 2

;16-Bit PWM Registers
.equ TCCR1A, 0x80
.equ TCCR1B, 0x81
.equ ICR1L, 0x86
.equ ICR1H, 0x87
.equ OCR1AL, 0x88
.equ OCR1AH, 0x89
.equ OCR1BL, 0x8A
.equ OCR1BH, 0x8B


;ADC Registers
.equ ADCL, 0x78
.equ ADCH, 0x79
.equ ADCSRA, 0x7A
.equ ADCSRB, 0x7B
.equ ADMUX, 0x7C
.equ DIDR0, 0x7E

.equ ADIF, 4


;External Interrupt Register Addresses
.equ EICRA , 0x69             ; Control Register A
.equ EIMSK , 0x1D             ; Mask Register
.equ EIFR , 0x1C              ; Flag Register

;External Interrupt Bits
.equ ISC11 , 3                ; Sense Control for INT1
.equ ISC10 , 2                ; Sense Control for INT1
.equ ISC01 , 1                ; Sense Control for INT0
.equ ISC00 , 0                ; Sense Control for INT0

.equ INT1MSK , 1              ; Mask for INT1
.equ INT0MSK , 0              ; Mask for INT0

.equ INTF1 , 1                ; Flag for INT1
.equ INTF0 , 0                ; Flag for INT0



;Wheel Constants
.equ HI, 0x01
.equ L_FOR, 0xA9
.equ L_REV, 0x45
.equ R_FOR, 0x45
.equ R_REV, 0xA9


;-----------------------------PROGRAM ADDRESSES-----------------------------
.org 0x0000                   ; RESET 0x0000 Program Address
	rjmp reset

.org 0x0054                   ; ADC Conversion Complete Interrupt 0x002A
    rjmp updatepwm


.org 0x0068                   ; First available address after assigned interrupt vectors 




;-----------------------------LABELLED ROUTINES-----------------------------
reset:
	cli                       ; Disable all interrupts while setting things up

	ldi r16 , hi8(RAMEND)     ; Set up stack pointer; high 8-bits to end of SRAM
	out SPH , r16
	ldi r16 , lo8(RAMEND)     ; Set up stack pointer; lo 8-bits to end of SRAM
	out SPL , r16

	rcall pwmsetup 
	rcall adcsetup

	sei                       ; Globally enable interrupts




main:
	rjmp main                 ; Currently empty loop



adcsetup:
	
	ldi r16, 0b01000000      ;selects analog input A0
	sts ADMUX, r16
	ldi r16, 0b11101111      ;enables, starts, sources, and prescales 128
	sts ADCSRA, r16  
	ldi r16, 0b00000000      ;free running mode
	sts ADCSRB, r16
	ldi r16, 0b00000001      ;disable digital input 0
	sts DIDR0, r16

	ret

pwmsetup:
    ldi r31, HI        
    ldi r30, L_FOR

    ldi r29, HI           ; set compare for duty cycle 
    ldi r28, R_FOR


    ldi r16,0b10100010      ;  FASM PWM Mode 15
    sts TCCR1A,r16
    ldi r16,0b00011011      ; Internal Clock no prescaling
    sts TCCR1B,r16

    ;for use with 16-bit clock
    ldi r17, 0x13            ; set top to 5000 for frequency of 50 Hz
    ldi r16, 0x88
    sts ICR1H, r17
    sts ICR1L, r16

    mov r17, r29
    mov r16, r28

    sts OCR1AH, r17
    sts OCR1AL, r16

    sbi DDRB, 1

    mov r17, r31
    mov r16, r30

    sts OCR1BH, r17
    sts OCR1BL, r16

    sbi DDRB, 2

    ret


updatepwm:
	in r16 , SREG              ; Store current Status Register values
	push r16                   ; Push to stack

	;Update PWM
    lds r31, ADCH        
    lds r30, ADCL

    lds r29, ADCH       ; set compare for duty cycle 
    lds r28, ADCL

    mov r17, r29
    mov r16, r28

    sts OCR1AH, r17
    sts OCR1AL, r16

    sbi DDRB, 1

    mov r17, r31
    mov r16, r30

    sts OCR1BH, r17
    sts OCR1BL, r16

    sbi DDRB, 2

    ldi r16, (0<<ADIF)
    sts ADCSRA, r16

	pop r16                    ; Recover Status Register values from the stack
	out SREG , r16             ; Restore the Status Register
	reti                       ; Exit the interrupt service routine
