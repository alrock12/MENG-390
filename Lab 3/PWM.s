.equ DDRD, 0x0A
.equ TCCR0A, 0x24
.equ TCCR0B, 0x25
.equ OCR0A, 0x27

.org 0x0000
rjmp init

.org 0x0032 ; First memory address after the interrupt vector table
            ; Some random code to keep the CPU busy.


init:
    ldi r16,0b10000011
    out TCCR0A,r16
    ldi r16,0b00000101
    out TCCR0B,r16
    ldi r16,127
    out OCR0A,r16
    sbi DDRD,6
    rjmp start
