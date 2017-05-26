/*  CAB202 Tutorial 9
*	Question 4 - Solution
*
*	B.Talbot, May 2016
*	Queensland University of Technology
*/
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "lcd.h"
#include "graphics.h"
#include "cpu_speed.h"
#include "sprite.h"

/*
* Useful defines you can use in your system time calculations
*/
#define FREQUENCY 8000000.0
#define PRESCALER 1024.0

/*
* Definitions for the states of the buttons
*/
#define NUM_BUTTONS 6
#define BTN_DPAD_LEFT 0
#define BTN_DPAD_RIGHT 1
#define BTN_DPAD_UP 2
#define BTN_DPAD_DOWN 3
#define BTN_LEFT 4
#define BTN_RIGHT 5

#define BTN_STATE_UP 0
#define BTN_STATE_DOWN 1

/*
* Variables used in recording the state of the buttons. Note the use of volatile
* keyword. For arrays this keyword isn't necessary (consider why...), but we leave
* it there to show how to use volatile Sprite variables with the "cab202_teensy"
* library
*/
volatile Sprite btn_sprites[NUM_BUTTONS];
volatile unsigned char btn_hists[NUM_BUTTONS];
volatile unsigned char btn_states[NUM_BUTTONS];

volatile unsigned int press_count = 0;

/*
* Bitmaps for visualising the button states
*/
unsigned char bm_pressed[] = {
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111,
    0b11111111
};
unsigned char bm_unpressed[] = {
    0b11111111,
    0b10000001,
    0b10000001,
    0b10000001,
    0b10000001,
    0b10000001,
    0b10000001,
    0b11111111
};

/*
* Function declarations
*/
void init_hardware(void);

double get_system_time(unsigned int timer_count);

/*
* Main - initialise the hardware, and run the code that increments the face's
* current position and draws it.
*/
int main() {
    set_clock_speed(CPU_8MHz);

    // Create and initialise the sprites
    // NOTE: our volatile Sprite pointers are explicitly cast back to a Sprite
    // pointer to remove the "volatile" qualifier. This is because our functions
    // in the library do not explicitly support volatile arguments!
    init_sprite((Sprite*) &btn_sprites[BTN_DPAD_LEFT], 0, 32, 8, 8, bm_unpressed);
    init_sprite((Sprite*) &btn_sprites[BTN_DPAD_RIGHT], 16, 32, 8, 8, bm_unpressed);
    init_sprite((Sprite*) &btn_sprites[BTN_DPAD_UP], 8, 24, 8, 8, bm_unpressed);
    init_sprite((Sprite*) &btn_sprites[BTN_DPAD_DOWN], 8, 40, 8, 8, bm_unpressed);
    init_sprite((Sprite*) &btn_sprites[BTN_LEFT], 60, 32, 8, 8, bm_unpressed);
    init_sprite((Sprite*) &btn_sprites[BTN_RIGHT], 76, 32, 8, 8, bm_unpressed);

    // Setup the hardware
    init_hardware();

    // Run the main loop
    char buff[80];
    while (1) {
        // Decide what bitmap we should have
        for (unsigned char i = 0; i< NUM_BUTTONS; i++) {
            btn_sprites[i].bitmap = (btn_states[i] == BTN_STATE_DOWN) ? bm_pressed : bm_unpressed;
        }

        // Draw the screen
        clear_screen();
        for (unsigned char i = 0; i < NUM_BUTTONS; i++) {
            // NOTE: the same casting technique is used as mentioned above.
            draw_sprite((Sprite*) &btn_sprites[i]);
        }
        sprintf(buff, "%5.4f", get_system_time(TCNT1));
        draw_string(54, 0, buff);
        sprintf(buff, "%4d", press_count);
        draw_string(0, 0, buff);
        show_screen();

        // Have a rest
        _delay_ms(50);
    }

    // We'll never get here...
    return 0;
}

/*
* Function implementations
*/
void init_hardware(void) {
    // Initialising the LCD screen
    lcd_init(LCD_DEFAULT_CONTRAST);

    // Initalising the buttons as inputs
    DDRF &= ~((1 << PF5) | (1 << PF6));
    
    // Initialising the LEDs as outputs
    DDRB |= ((1 << PB2) | (1 << PB3));

    // Configure all necessary timers in "normal mode", enable all necessary
    // interupts, and configure prescalers as desired
    TCCR1B &= ~((1<<WGM02)); // This one is the timer
    TCCR0B &= ~((1<<WGM02));
    
    // Set the prescaler for TIMER1 so that the clock overflows every ~8.3 seconds
    TCCR1B |= ((1<<CS12) | (1<<CS10));
    TCCR1B &= ~((1<<CS11));
    
    //Configure TIMER0
    TCCR0B |= ((1<<CS02) | (1<<CS00));
    TCCR0B &= ~((1<<CS01));
    TIMSK0 = (1<<TOIE0);
    
    sei();
}

double get_system_time(unsigned int timer_count) {
    // Based on the current count, frequency, and prescaler - return the current
    // count time in seconds
    double scaler = 128 / 1000000.0;
    return (timer_count * scaler);
}


/*
* Interrupt service routines
*/
ISR(TIMER0_OVF_vect){
    size_t i = 0;
    for( i = 0; i < sizeof(btn_hists) / sizeof(btn_hists[0]); i++) {
        btn_hists[i] = btn_hists[i] << 1;
    }
    
    if((PINF >> 6) & 1){ // Left Button
        btn_hists[BTN_LEFT] |= 0x01;
    }
    
    if((PINF >> 5) & 0b1 ){ // Right Button
        btn_hists[BTN_RIGHT] |= 0x01;
    }
    
    if((PIND >> 1) & 0b1) { // Joystick Up
        btn_hists[BTN_DPAD_UP] |= 0x01;
    }
    
    if((PINB >> 1) & 0b1) { // Joystick Left
        btn_hists[BTN_DPAD_LEFT] |= 0x01;
    }
    
    if((PIND >> 0) & 0b1) { // Joystick Right
        btn_hists[BTN_DPAD_RIGHT] |= 0x01;
    }
    
    if((PINB >> 7) & 0b1) { // Joystick Down
        btn_hists[BTN_DPAD_DOWN] |= 0x01;
    }
    
    size_t x = 0;
    for( x = 0; x < sizeof(btn_hists) / sizeof(btn_hists[0]); x++) {
        if (btn_hists[x] == 0b00000000 && btn_states[x] == BTN_STATE_DOWN) { // All Off
            btn_states[x] = BTN_STATE_UP;
            press_count += 1;
        } else if (btn_hists[x] == 0b11111111 && btn_states[x] == BTN_STATE_UP) { // All High
            btn_states[x] = BTN_STATE_DOWN;
        }
    }
}
