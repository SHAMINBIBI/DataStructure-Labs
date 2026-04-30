// (Include the same LCD module connections as Task 1)

void main() {
    int i;
    char msg[] = "Success";
    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);

    for(i=0; i<7; i++) {
        Lcd_Chr(1, i+1, msg[i]);       // Print single character [cite: 59, 114]
        Delay_ms(100);                 // 100ms delay 
    }
    
    while(1);
}