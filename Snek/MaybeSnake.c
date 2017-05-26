#include <util/delay.h>
#include <avr/io.h>
#include <util/delay.h>
#include "cpu_speed.h"
#include "graphics.h"
#include "lcd.h"
#include "sprite.h"
#include <stdbool.h>
#include <stdlib.h>
#define DELAY (20)
#define MAX_SNAKE_LENGTH (20) //max snake can grow constant
//bool isRunning = true;

int currentSnakeLength = 2; //when snake eats increment by 1
int currentPosition_X = LCD_X/2;

int playerScore;
int playerLives;
char pScore;

bool starting = true;

unsigned char snakeSprite[] = {
    //Each bit determins where a sprite will be drawn
    0b11100000,
    0b11100000,
    0b11100000
};
Sprite snake[MAX_SNAKE_LENGTH];

void welcomeTimer(void){
    
    draw_string(LCD_X/7, LCD_Y/2, "Jainesh Kumar");
    draw_string(LCD_X/7, LCD_Y/2*1.5, "n9686789");
    show_screen();
    _delay_ms(2000);
    starting = false;
    clear_screen();
    
}

// void playerStatus(){
//   draw_string(1, 1, pScore);
// }

void drawSnake(){
    
    
    
    
    // unsigned char backSquareSprite[] = {
    //   0b11100000,
    //   0b11100000,
    //   0b11100000
    // };
    //Declaring the sprite
    for (int i = 0; i < currentSnakeLength; i++) {
        init_sprite(&snake[i], currentPosition_X+i*3, LCD_Y/2, 3, 3, snakeSprite);
        draw_sprite(&snake[i]);
    }
    
    // init_sprite(&square, LCD_X/2, LCD_Y/2, 3, 3, squareSprite);
    // draw_sprite(&square);
    
    //init_sprite(&square, LCD_X/2-1, LCD_Y/2-4, 3, 3, backSquareSprite);
    //draw_sprite(&square);
}

void moveSnake(){
    int nextPosition_X = currentPosition_X+1;
    //clear_screen(); //Might needs
    
    //while(1){
    for (int i = 0; i < currentSnakeLength; i++) {
        init_sprite(&snake[i], nextPosition_X+i*3, LCD_Y/2, 3, 3, snakeSprite);
        draw_sprite(&snake[i]);
    }
    //}
    currentPosition_X = nextPosition_X;
}
// void moveSquare(){
//   if(PINF & (1 << 5) ){  //Right Button
//   // Send output to PORTB.
//      PORTB = (1 << 3);      //Right LED
//   }
// }

int main(){
    playerScore = 0;
    playerLives = 5;
    pScore = playerScore;
    
    //bool isRunning = true;
    
    set_clock_speed(CPU_8MHz);
    lcd_init(LCD_LOW_CONTRAST);
    clear_screen();
    //show_screen();
    //BACKLIGHT
    DDRC |= 1 << PIN7;
    PORTC |= 1 << PIN7;
    
    
    while(1) {
        clear_screen();
        if(starting == true){
            welcomeTimer();
            //starting = false;
            //_delay_ms(2000);
            //clear_screen();
        }
        else if(starting == false){
            while(1){
                //draw_string(LCD_X/7, LCD_Y/2, "Jainesh Kumar"); // IT IS REACHING HERE
                //clear_screen();
                show_screen();
                clear_screen();
                drawSnake();
                moveSnake();
                
            }
            //playerStatus();
            //moveSquare();
            
        }
    }
    show_screen();
    // cleanup_screen();
    return 0;
}