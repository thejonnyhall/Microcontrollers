#include <avr/io.h>
#include <avr/pgmspace.h>
#include "usb_serial.h"
#include "cpu_speed.h"
#include "graphics.h"
#include "lcd.h"

void setup(void);
int receive_date(void);

int main(){
   setup();
   while(!usb_configured() || !usb_serial_get_control()){
       clear_screen();
       draw_string(0,10,"Not Ready");
       show_screen();
   }
   clear_screen();
   draw_string(0,10,"Ready");
   show_screen();
   while(1){
       if (receive_date()){
           char *s = PSTR("COPY THAT \n");
           char c;
           while(1){
               c = pgm_read_byte(s++);
               if (!c) break;
               usb_serial_putchar(c);
           }

       }
   }
   return 0;
}

void setup(){
    set_clock_speed(CPU_8MHz);
    DDRB  |= 1 << PIN2;
    DDRC  |= 1 << PIN7;
    PORTC |= 1 << PIN7;
    lcd_init(LCD_DEFAULT_CONTRAST);
    usb_init();
}

int receive_date(){
    if(usb_serial_available()){
        int16_t c = usb_serial_getchar();
        if (c == 'a'){
            PORTB |= 1 << PIN2;
        }else if(c == 'x'){
            PORTB &= ~(1 << PIN2);
        }
        return 1;
    }
    return 0;
}
