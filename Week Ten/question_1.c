#include <avr/io.h>
#include <util/delay.h>
#include "graphics.h"
#include "sprite.h"
#include "cpu_speed.h"

int main(void){

// Set the CPU speed to 8MHz (you must also be compiling at 8MHz)
    set_clock_speed(CPU_8MHz);
    
    //initialise the LCD screen
    lcd_init(LCD_DEFAULT_CONTRAST);
    
    //clear any characters that were written on the screen
    clear_screen();
    
    //draw vertical line on right edge of screen
    draw_line(83,0,83,83);
    
    // draw name and student number
     draw_string(20,10,"Jonny Hall");
     draw_string(25,20,"n9697985");
    
    //draw 8x8 square sprite in top left corner
    Sprite squareSprite;
    
    unsigned char bitmapSquare [] = {
        0b11111111,
        0b10000001,
        0b10000001,
        0b10000001,
        0b10000001,
        0b10000001,
        0b10000001,
        0b11111111
    };
    
    init_sprite(&squareSprite, 0, 0, 8, 8, bitmapSquare);
    
    draw_sprite(&squareSprite);
    
    //write the string on the lcd
    show_screen();

    return 0;
}