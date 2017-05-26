
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdint.h>
#include <util/delay.h>
#include <stdio.h>

#include "usb_serial.h"

#include "sprite.h"
#include "lcd.h"
#include "graphics.h"
#include "cpu_speed.h"


#define BUFF_LENGTH 32

//function declaration
void send_string(const char *s);
void recv_string(char *buf, uint8_t size);
void init_hardware(void);


// Basic command interpreter for controlling port pins
int main(void)
{
	// the buffer to store received characters
	char rx_buf[BUFF_LENGTH];
   

	//set clock speed to 8MhZ
    set_clock_speed(CPU_8MHz);
    
    
    //initialise LCD and ports
	init_hardware();
	
	clear_screen();
	//display a message on the screen
	draw_string(5,5, "USB serial demo");
	show_screen();


    // Wait until the USB port is configured and ready to go
  while(!usb_configured() || !usb_serial_get_control());
 	  _delay_ms(1000);


   //keep looping until the character 'q' is received
	while (rx_buf[0]!='q') {
        


		// and then listen for commands and process them
	   while (1) {

            if (usb_serial_available())
            {
			   recv_string(rx_buf, BUFF_LENGTH); //read serial port
			   //send a characters to the other side
               send_string(PSTR("received \n"));
			}
			else
			{
			  break;
			}	 
          	 
             clear_screen();
          	 char buff2[BUFF_LENGTH];
    		 sprintf(buff2, "Received: %s", rx_buf);   
             draw_string(5,30, buff2);
             show_screen();
        
            //check first character of the buffer and perform an action
            if(rx_buf[0]=='a'){ //turn LED0 ON
                PORTB &= 0xF0;
                PORTB |=(1<<PINB2);
                }
            if(rx_buf[0]=='d'){ //turn LED1 ON
            	PORTB &= 0xF0;
            	PORTB |= (1<<PINB3);
            	}
            if(rx_buf[0]=='s') //turn both LEDs OFF
            	PORTB &= 0xF0;
                         
		}
		
		     
		
	}	 
	return 0;
}


//initialise ports and LCD screen
void init_hardware()
{
	DDRB |= (1<<PINB2)|(1<<PINB3);	//LED0 and LED1 as outputs
	DDRF &= ~((1<<PINF5)|(1<<PINF6));	//Switch0 and Switch1 as input
	PORTB = 0xF0; 	// Turn everything off to start with
	lcd_init( LCD_DEFAULT_CONTRAST );
	clear_screen();
	show_screen();
	
	// Initialise the USB serial
    usb_init();
}


// Send a string to the USB serial port.  The string must be in
// flash memory, using PSTR
//
void send_string(const char *s)
{
	char c;
	while (1) {
		c = pgm_read_byte(s++);
		if (!c) break;
		usb_serial_putchar(c);
	}
}

// Receive a string from the USB serial port.  The string is stored
// in the buffer and this function will not exceed the buffer size.
// A carriage return or newline completes the string, and is not
// stored into the buffer.
// The return value is the number of characters received, or 255 if
// the virtual serial connection was closed while waiting.
//
void recv_string(char *buf, uint8_t buf_size)
{
	int16_t r;
	uint8_t count = 0;

	while (count < buf_size) {
		r = usb_serial_getchar();
		if (r != -1) {
			if (r == '\r' || r == '\n')  break;
				*buf++ = r;
				count++;
			
		} else {
			if (!usb_configured() ||
			  !(usb_serial_get_control() & USB_SERIAL_DTR)) {
				// user no longer connected
				break;
			}
			// just a normal timeout, keep waiting
		}
	}
	*buf++ = '\0';
	//return count;
}


