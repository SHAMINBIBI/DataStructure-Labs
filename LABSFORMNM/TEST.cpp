LIST P=18F452
    #include <p18f452.inc>

    CONFIG OSC = HS      // initial configurations
    CONFIG WDT = OFF 
    CONFIG LVP = OFF 

    ORG 0x00 

START:
    CLRF PORTB         //clearing port B for a garbage free Output
    MOVLW 0x00
    MOVWF TRISB 

MAIN_LOOP:
    MOVLW B'01010101'   //for blinking the ODD LEDs
    MOVWF PORTB
    CALL DELAY          //adding delay to make the blinking visible
    CLRF PORTB
    CALL DELAY
    
    MOVLW B'10101010'   //for blinking the EVEN LEDs
    MOVWF PORTB
    CALL DELAY
    CLRF PORTB
    CALL DELAY         //adding delay to make the blinking visible
    
    MOVLW B'11111111'  //for blinking ALL the LEDs
    MOVWF PORTB
    CALL DELAY         //adding delay to make the blinking visible
    CLRF PORTB
    CALL DELAY
    
    GOTO MAIN_LOOP     //looping the main program

DELAY:                 //delay subroutine to create a delay of approximately 1 second
    MOVLW D'255'
    MOVWF 0x20
D1: MOVLW D'255'
    MOVWF 0x21
D2: DECFSZ 0x21, F
    BRA D2
    DECFSZ 0x20, F
    BRA D1
    RETURN

    END