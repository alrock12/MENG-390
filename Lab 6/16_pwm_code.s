; Use 16-bit Timer for PWM generation
; 16-bit output pins are OC1A/OC1B (Port B 1/2)
; corresponding to Arduino digital pin 9 (Right)/10(Left)
; TOP set to 2^16 for freq 244 Hz
; Duty Cycles manually set 


; 0x4CCC = 30% (Right Forward)
; 0x6666 = 40% (Left Forward)


;Register Addresses
.equ DDRB, 0x04
.equ TCCR1A, 0x80
.equ TCCR1B, 0x81
.equ ICR1L, 0x86
.equ ICR1H, 0x87
.equ OCR1AL, 0x88
.equ OCR1AH, 0x89
.equ OCR1BL, 0x8A
.equ OCR1BH, 0x8B

;Integers
.equ R_L, 28
.equ R_H, 29
.equ L_VALUEL, 30
.equ L_VALUEH, 31


.org 0x0000
rjmp init

.org 0x0032 ; First memory address after the interrupt vector table

start:
    ldi r16,254

main:
    nop
    dec r16 
    rjmp main

init:
    ldi L_VALUEH, 0x01        
    ldi L_VALUEL, 0x45   

    ldi r29, 0x01           ; set compare for duty cycle 
    ldi r28, 0xA9 



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

    mov r17, L_VALUEH
    mov r16, L_VALUEL

    sts OCR1BH, r17
    sts OCR1BL, r16

    sbi DDRB, 2

    rjmp main
