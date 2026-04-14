LIST P=18F452 
#include<p18f452.inc> 
 
;Configuration bits 
CONFIG OSC = HS 
CONFIG WDT = OFF 
CONFIG LVP = OFF 
 
;Variables 
COUNT EQU 0X20       ;holds current digit (0-9) 
D1    EQU 0X21       ;inner delay loop counter 
D2    EQU 0X22       ;middle delay loop counter 
D3    EQU 0X23       ;outer delay loop counter 
 
    ORG 0X00 
 
START: 
    CLRF TRISB          ;Set PORTB as output 
    CLRF PORTB          ;Turn off display initially 
 
MAIN_LOOP: 
    ; Count up loop (0 to 9) 
    CLRF COUNT          ;Start COUNT at 0 
 
UP_LOOP: 
    MOVF COUNT, W       ;Move current count to W 
    CALL GET_7SEG       ;Get segment code for digit 
    MOVWF PORTB         ;Send to seven-segment display 
    CALL DELAY          ;Hold so digit is visible 
    INCF COUNT, F       ;COUNT = COUNT + 1 
    MOVLW D'10' 
    CPFSEQ COUNT        ;Skip if COUNT == 10 
    BRA UP_LOOP         ;Not 10 yet, show next digit 
    ; Count down loop (9 to 0) 
    MOVLW D'9' 
    MOVWF COUNT         ;Start down from 9 
 
DOWN_LOOP: 
    MOVF COUNT, W 
    CALL GET_7SEG 
    MOVWF PORTB 
    CALL DELAY 
    MOVF COUNT, F       ;Check if COUNT is currently 0 
    BZ   MAIN_LOOP      ;If yes, we just showed 0, restart 
    DECF COUNT, F       ;Else decrement and continue 
    BRA DOWN_LOOP 
 
; Delay Subroutine 
DELAY: 
    MOVLW d'10' 
    MOVWF D3 
D_L0: 
    MOVLW D'255' 
    MOVWF D1 
D_L1: 
    MOVLW D'255' 
    MOVWF D2 
D_L2: 
    DECFSZ D2, F 
    BRA D_L2 
    DECFSZ D1, F 
    BRA D_L1 
    DECFSZ D3, F 
    BRA D_L0 
    RETURN 
; Seven Segment Lookup (if-else chain using CPFSEQ) 
GET_7SEG: 
    MOVLW D'0' 
    CPFSEQ COUNT 
    BRA CHECK_1 
    RETLW 0X3F          ;0 
 
CHECK_1: 
    MOVLW D'1' 
    CPFSEQ COUNT 
    BRA CHECK_2 
    RETLW 0X06          ;1 
 
CHECK_2: 
    MOVLW D'2' 
    CPFSEQ COUNT 
    BRA CHECK_3 
    RETLW 0X5B          ;2 
 
CHECK_3: 
    MOVLW D'3' 
    CPFSEQ COUNT 
    BRA CHECK_4 
    RETLW 0X4F          ;3 
 
CHECK_4: 
    MOVLW D'4' 
    CPFSEQ COUNT 
    BRA CHECK_5 
    RETLW 0X66          ;4 
 
CHECK_5: 
    MOVLW D'5' 
    CPFSEQ COUNT 
    BRA CHECK_6 
    RETLW 0X6D          ;5 
 
CHECK_6: 
    MOVLW D'6' 
    CPFSEQ COUNT 
    BRA CHECK_7 
    RETLW 0X7D          ;6 
 
CHECK_7: 
    MOVLW D'7' 
    CPFSEQ COUNT 
    BRA CHECK_8 
    RETLW 0X07          ;7 
 
CHECK_8: 
    MOVLW D'8' 
    CPFSEQ COUNT 
    BRA CHECK_9 
    RETLW 0X7F          ;8 
 
CHECK_9: 
    RETLW 0X6F          ;9 
 
END