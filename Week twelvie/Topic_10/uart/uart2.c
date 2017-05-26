
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdint.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>



#include "sprite.h"
#include "lcd.h"
#include "graphics.h"
#include "cpu_speed.h"


#define BUFF_LENGTH 20
// define some macros
#define BAUD 9600                                   // define baud rate
#define BAUDRATE ((F_CPU)/(BAUD*16UL)-1)    

//function declaration
void uart_transmit(unsigned char data);
unsigned char  uart_receive(void);
void init_hardware(void);
void uart_init(void);


// Basic command interpreter for controlling port pins
int main(void)
{


	// the buffer to store received characters
	unsigned char rcv;
	
	//set clock speed to 8MhZ
    set_clock_speed(CPU_8MHz);
    
    
    //initialise LCD and ports
	init_hardware();
	
	clear_screen();
	//display a message on the screen
	draw_string(5,5, "UART serial demo");
	show_screen();

	
		// main loop
	   while (1) {
			 
			 
			 //detect button pressed
			 if ((PINF>>PINF5)&1){
			        clear_screen();
  					draw_string(0,10, "Button 3 pressed");
  					draw_string(0,20, "Sending 'c' ");
  					uart_transmit('c'); 
  					show_screen();
  				}
				
			     //detect button pressed
			     if ((PINF>>PINF6)&1){
			        clear_screen();
  					draw_string(0,10, "Button 2 pressed");
  					draw_string(0,20, "Sending 'd' ");
  					uart_transmit('d'); 
  					show_screen();
  				}   
               
               //receive character
               rcv = uart_receive();
               
         
               // display received character
               draw_string(0,30, "rx:");
               draw_char(0,38, rcv);
               show_screen();
             
			    
           _delay_ms(10);       
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
    uart_init();
}


//initialise the uart
void uart_init(void)
{
	//UBRRH = (BAUDRATE>>8);                      // shift the register right by 8 bits
    UBRR1 = BAUDRATE;                           // set baud rate
    UCSR1B|= (1<<TXEN1)|(1<<RXEN1);                // enable receiver and transmitter
    UCSR1C|= (1<<UCSZ10)|(1<<UCSZ11);   // 8bit data format

}

void uart_transmit(unsigned char data){

while (!(( UCSR1A >> UDRE1) & 1));                // wait while register is free
    UDR1 = data;  
    

}

unsigned char  uart_receive(void){

	while(!(UCSR1A) & (1<<RXC1));                   // wait while data is being received
   	 return UDR1;

}

