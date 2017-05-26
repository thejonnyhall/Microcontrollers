#include <avr/io.h>
#include <stdbool.h>
#include <stdio.h>
#include <util/delay.h>
#include "lcd.h"
#include "graphics.h"
#include "sprite.h"
#include "cpu_speed.h"
#include <string.h>
#include <avr/interrupt.h>


#define SNEK_START_LENGTH 2

int score = 0;

/* this takes care of DDR for SWs and LED and LCD*/
void screenSetup(void);
void setup_timer(void);

volatile int i;


// Le Main program entry point
int main(){
    i = 0;
    screenSetup();
    setup_timer();


    while(1){
        for (int i=0; i<SNEK_START_LENGTH + score; i++) {
        draw_sprite(*snake[i]);
        }

        show_screen();
        _delay_ms(200);
        clear_screen();
    }
    return 0;
}


void screenSetup(){
    set_clock_speed(CPU_8MHz);
    DDRB |= 1 << PIN2 | 1 << PIN3 ;
    DDRF &= ~( 1 << PIN5);
    DDRC  |= 1 << PIN7;
    PORTC |= 1 << PIN7;
    lcd_init(LCD_DEFAULT_CONTRAST);
    clear_screen();
    draw_string(5,5,"Pls give me a 7");
    show_screen();
}



void process_btn(){
    if (PINF >> PIN5 & 0b1){
        debounce(PIN5);
        PORTB ^= 1 << PIN2 | 1 << PIN3;
    }
}

void debounce(int p){
    _delay_ms(100);
    while(PINF >> p & 0b1);
    _delay_ms(100);
}

void setup_timer(){
    TCCR0B &= ~(1 << WGM02);
    TCCR0B |= 1 << CS00 | 1 << CS02;
    TCCR0B &= ~(1 << CS01);
    
    // handling interrupts
    TIMSK0 |= 1 << TOIE0; // TIME OVERFLOW INTERRUPT ENABLE TOIE0

    sei();
    
}


ISR(TIMER0_OVF_vect){
    i++;
    clear_screen();
    char cnt[80];
    sprintf(cnt, "%d", i);
    draw_string(20,10,cnt);
    show_screen();
}






