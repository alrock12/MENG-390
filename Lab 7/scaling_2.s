


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
.equ PORTC, 0x08
.equ DDRC, 0x07

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

;Wheel Constants based on 50 Hz
.equ HI, 0x01
.equ L_FOR, 0xA9
.equ L_REV, 0x45
.equ R_FOR, 0x45
.equ R_REV, 0xA9

;Math Constants
.equ HIGH, 0b110101001 ;425
.equ LOW,  0b101000101 ;325


;-----------------------------PROGRAM ADDRESSES-----------------------------
.org 0x0000                   ; RESET 0x0000 Program Address
    rjmp reset

.org 0x0054                   ; ADC Conversion Complete Interrupt 0x002A
    rjmp adcinterrupt

.org 0x0068                   ; First available address after assigned interrupt vectors 



;-----------------------------LABELLED ROUTINES-----------------------------
reset:
    cli                       ; Disable all interrupts while setting things up

    ldi r16 , hi8(RAMEND)     ; Set up stack pointer; high 8-bits to end of SRAM
    out SPH , r16
    ldi r16 , lo8(RAMEND)     ; Set up stack pointer; lo 8-bits to end of SRAM
    out SPL , r16

    rcall troubleshootsetup
    rcall pwmsetup 
    rcall adcsetup

    sei                       ; Globally enable interrupts


main:
    rjmp main                 ; Currently empty loop


troubleshootsetup:

    ldi r16 , 0xFF            ; enable port B outputs
    out DDRB , r16            ; Set PORTB5 as output
    cbi PORTB , B5            ; Clear bit value, LED OFF

    ldi r16, 0x00             ; set port C as inputs
    out DDRC, r16

    ret                        ; Exit subroutine and go to return address



pwmsetup:

    ;16-bit PWM Timer 1
    ldi r16,0b10100010      ; FAST PWM Mode 15
    sts TCCR1A,r16
    ldi r16,0b00011011      ; Internal Clock, prescaling 64
    sts TCCR1B,r16

    ;for use with 16-bit clock
    ldi r17, 0x13            ; set top to 5000 for frequency of 50 Hz
    ldi r16, 0x88
    sts ICR1H, r17
    sts ICR1L, r16


    ;Output Right
    ldi r17, HI
    ldi r16, R_FOR

    sts OCR1AH, r17
    sts OCR1AL, r16

    sbi DDRB, 1


    ;Output Left
    ldi r17, HI
    ldi r16, L_FOR

    sts OCR1BH, r17
    sts OCR1BL, r16

    sbi DDRB, 2

    ret



adcsetup:
    
    ldi r16, 0b01100000      ;selects AREF, Left Adjust, analog input A0
    sts ADMUX, r16
    ldi r16, 0b11101010      ;enables, starts, sources, and prescales 4
    sts ADCSRA, r16  
    ldi r16, 0b00000000      ;free running mode
    sts ADCSRB, r16

    ret



adcinterrupt:
    in r16 , SREG              ; Store current Status Register values
    push r16                   ; Push to stack

    sbi PINB , B5              ; Toggle the LED

    ;load Analog value 
    lds r25, ADCH 
    ldi r16, 0b11111010        ;clear flag
    sts ADCSRA, r16  

    ;divide by 2.5
    ldi r26, 102
    mul r25, r26
    inc r1

    ;copy for manipulation
    mov r28, r1              
    mov r30, r1

    
    ;-----------------------------------------------------


    ;Right Wheel
    ;Reverse on high

    ldi r20, hi8(HIGH) ; 425 upper 8 bits  
    ldi r21, lo8(HIGH) ; 425 lower 8 bits
    ldi r22, 0x00       ; upper 8 of (x/10) 
    mov r23, r28       ; lower 8 of (x/10)
    sub r21,r23      ;lower 8 bit answer
    sbc r20,r22      ;upper 8 bit answer

    sts OCR1AH, r20
    sts OCR1AL, r21

    sbi DDRB, 1


    ;Left Wheel
    ;Forward on high

    ;add 325
    ldi r20, hi8(LOW) ; 325 upper 8 bits  
    ldi r21, lo8(LOW) ; 325 lower 8 bits
    ldi r22, 0x00       ; upper 8 of (x/10) 
    mov r23, r25       ; lower 8 of (x/10)
    add r21,r23      ;lower 8 bit answer
    adc r20,r22      ;upper 8 bit answer

    sts OCR1BH, r20
    sts OCR1BL, r21

    sbi DDRB, 2



    pop r16                    ; Recover Status Register values from the stack
    out SREG , r16             ; Restore the Status Register
    reti                       ; Exit the interrupt service routine
