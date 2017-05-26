/*/ All the Header Files /*/
#include <stdlib.h>
#include <math.h>

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#include "ascii_font.h"
#include "cpu_speed.h"
#include "lcd.h"
#include "graphics.h"
#include "sprite.h"
#include <stdbool.h>

#define MAXIMUM_SNAKE_LENGTH (20) // Max length the snake can grow to



unsigned char snekSprite[] = {
    0b11100000,
    0b11100000,
    0b11100000
};

unsigned char foodSprite[] = {
    0b01000000,
    0b10100000,
    0b01000000
};

Sprite snake[MAXIMUM_SNAKE_LENGTH];

Sprite food;


/* Global Variables */
int lives = 5;
int score = 0;
int snakePosY;
int snakePosX;
char life[80];
char scor[80];
int direction = 5;
int snakeLength = 2;


bool buttonPressed = false;
bool wallsOn = false;


/* Function Declarations */

// Setup
void initHardware(void);
void lifeBanner(void);
void scoreBanner(void);
void drawGame(void);
void pinOutputs(void);
void lifeChequer(void);
void gameOverBruh(void);
void wallsBoi(void);
void wally(void);
uint16_t adc_read(uint8_t ch);
void potStuff(void);

// Snake
void snakeGame(void);
void initSnake(void);
void moveSnake(void);
void snakeDirection(void);
void foodSnakeCollision(void);
uint16_t adcResult;

//Food
void moveFood(void);

/* Helper Function Declarations */
void drawCentred(unsigned char y, char* string);

// Program Entry Point
int main(void){
    // Initialize the hardware
    initHardware();
    initSnake();
    // Draw name and student number nice and neatly
    drawCentred(12, "Jonny Hall");
    drawCentred(22, "n9697985");

    show_screen();
    
    // Let there be light
    PORTC |= 1<<7;
    
    srand(50);

    _delay_ms(2000);
    clear_screen();
    
    // Run le game
    while(1){
        //potentiometer memes
        adcResult = adc_read(0);

        // walls memes
        wally();
        
        if(direction != 5){
            moveSnake();
        }
        // draws te gem
        drawGame();
        

        
        pinOutputs();
        
        wallsBoi();
        
        lifeChequer();
        
        lifeBanner();
        scoreBanner();
        
        show_screen();
        
        potStuff();
        
        clear_screen();
    }
    return 0;
}

void moveSnake(){
    int tailX = snake[snakeLength - 1].x;
    int tailY = snake[snakeLength - 1].y;
    
    for (int i = snakeLength - 1; i > 0; i--) {
        snake[i].x = snake[i - 1].x;
        snake[i].y = snake[i - 1].y;
    }
    
    if (direction == 0){ // up up up up up up up up up
        snakePosY = snake[0].y - 3;
        if (snakePosY < 0) {
            snakePosY = 45;
        }
        if (snakePosY < 8 && snake[0].x < 35) {
                snakePosY = 45;
            }
            snakePosY = snakePosY % 48;
            snake[0].y = snakePosY;
        
        if (wallsOn == true){
            if (snake[0].x < 30 && snake[0].y == 18) {
                lives--;
                direction = 5;
                snakeLength = 2;
                initSnake();
            }
            if (snake[0].x == 60 && snake[0].y < 14) {
                lives--;
                direction = 5;
                snakeLength = 2;
                initSnake();
            }
            if (snake[0].x == 45  && snake[0].y > 30) {
                lives--;
                direction = 5;
                snakeLength = 2;
                initSnake();
            }
        }
    }
    if(direction == 1){ // left left left left left left left left
        snakePosX = snake[0].x - 3;
        if (snakePosX < 0) {
            snakePosX = 81;
        }
        if (snakePosX < 35 && snake[0].y < 8) {
            snakePosX = 81;
        }
        snakePosX = snakePosX % 84;
        snake[0].x = snakePosX;
        if (wallsOn == true){
            if (snake[0].x == 45 && snake[0].y >= 30) {
                lives--;
                direction = 5;
                snakeLength = 2;
                initSnake();
            }
            if (snake[0].x == 60 && snake[0].y < 14) {
                lives--;
                direction = 5;
                snakeLength = 2;
                initSnake();
            }
            if (snake[0].x < 30 && snake[0].y == 21) {
                lives--;
                direction = 5;
                snakeLength = 2;
                initSnake();
            }
        }
    }
    if (direction == 2){ // down
        snakePosY = snake[0].y + 3;
        snakePosY = snakePosY % 48;
        if (snakePosY < 8 && snake[0].x < 35) {
            snakePosY = 8;
        }
        snakePosY = snakePosY % 48;
        snake[0].y = snakePosY;
        if (wallsOn == true){
            if (snake[0].x < 30 && snake[0].y == 18) {
                lives--;
                direction = 5;
                snakeLength = 2;
                initSnake();
            }
            if (snake[0].x == 60 && snake[0].y < 14) {
                lives--;
                direction = 5;
                snakeLength = 2;
                initSnake();
            }
            if (snake[0].x == 45  && snake[0].y > 29) {
                lives--;
                direction = 5;
                snakeLength = 2;
                initSnake();
            }
        }

    }

    if (direction == 3){ // right
        snakePosX = snake[0].x + 3;
        snakePosX = snakePosX % 84;
        if (snakePosX < 35 && snake[0].y < 8) {
            snakePosX = 35;
        }
        snakePosX = snakePosX % 84;
        snake[0].x = snakePosX;
        if (wallsOn == true){
            //draw_line(60, 0 , 60, 15); // top wall
            //draw_line(45, 48, 45, 30); // bottom wall
            //draw_line(0, 20, 30, 20); // left wall
            if (snake[0].x < 30 && snake[0].y == 21) {
                lives--;
                direction = 5;
                snakeLength = 2;
                initSnake();
            }
            if (snake[0].x == 60 && snake[0].y < 14) {
                lives--;
                direction = 5;
                snakeLength = 2;
                initSnake();
            }
            if (snake[0].x == 45  && snake[0].y > 29) {
                lives--;
                direction = 5;
                snakeLength = 2;
                initSnake();
            }
        }

    }
    
    // food eat
    if (snake[0].x == food.x && snake[0].y == food.y) {
        if(wallsOn == true){
            score = score + 2;
        } else {
            score++;
        }
        snakeLength++;
        // eliminates end tail position glitch thingo that drew in the middle of the screen.
        snake[snakeLength - 1].x = tailX;
        snake[snakeLength - 1].y = tailY;
        moveFood();
    }
    
    // snek dead
    for (int i = 1; i < snakeLength; i++) {
        if (snake[i].x == snake[0].x && snake[i].y == snake[0].y) {
            lives--;
            direction = 5;
            snakeLength = 2;
            initSnake();
            
            return;
        }
    }
}

void pinOutputs(void){
    
    if((PIND >> 1) & 0b1) { //Joystick Up
        direction = 0;
    }
    
    if((PIND >> 0) & 0b1){ //Joystick Right
        direction = 3;
    }
    
    if((PINB >> 7) & 0b1){ //Joystick Down
        direction = 2;
    }
    
    if((PINB >> 1) & 0b1){  //Joystick Left
        direction = 1;
    }
}

void initHardware(void) {
    // Set the clock-speed.
    set_clock_speed(CPU_8MHz);
    
    
    // Initialize the LCD screen.
    lcd_init(LCD_DEFAULT_CONTRAST);
    
    // Initialising SW1 as input.
    DDRB &= ~((1 << PB1) | (1 << PB7));
    DDRD &= ~((1 << PD0) | (1 << PD1));
    
    // Initialising SW2 and SW3 as inputs.
    DDRF &= ~((1 << PF5) | (1 << PF6));
    
    // Initialising LED0 and LED1 as outputs.
    DDRB |= ((1 << PB2) | (1 << PB3));
    
    // Initialising ADC with a pre-scaler of 128.
    ADMUX = (1<<REFS0);
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
    
    // Setup TIMER0 and add it to the interrupt register.
    TCCR0B |= ((1 << CS02) | (1 << CS00));
    TIMSK0 = (1<<TOIE0);
    
    
    // AREF = AVcc
    ADMUX = (1<<REFS0);
    
    // ADC Enable and pre-scaler of 128
    // 8000000/128 = 62500
    ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
    
    // Initialise the food
    init_sprite(&food, 60, 18, 3, 3, foodSprite);
    
    // Enable interrupts globally.
    //sei();
}

// Read the ADC value
uint16_t adc_read(uint8_t ch){
    // select the corresponding channel 0~7
    // ANDing with '7' will always keep the value
    // of 'ch' between 0 and 7
    ch &= 0b00000111;  // AND operation with 7
    ADMUX = (ADMUX & 0xF8)|ch;     // clears the bottom 3 bits before ORing
    
    // start single conversion
    // write '1' to ADSC
    ADCSRA |= (1<<ADSC);
    
    // wait for conversion to complete
    // ADSC becomes '0' again
    // till then, run loop continuously
    while(ADCSRA & (1<<ADSC));
    
    return (ADC);
}


void drawGame(void){
    for(unsigned char i = 0; i < snakeLength; i++){
        draw_sprite(&snake[i]);
    }
    draw_sprite(&food);
}

void initSnake(void){
    for (int i = 0; i < MAXIMUM_SNAKE_LENGTH; i++) {
        init_sprite(&snake[i], 36 + (i * 3), 21, 3, 3, snekSprite);
    }
}

void moveFood(void){
    int randX = rand() % 84;
    int randY = rand() % 39 + 9;
    
    randX/=3;
    randX*=3;
    
    randY/=3;
    randY*=3;
    
    food.x = randX;
    food.y = randY;
}


void lifeBanner(void){
    sprintf(life, "(%d)", lives);
    draw_string(15, 0, life);
    show_screen();
}

void scoreBanner(void){
    sprintf(scor, "%.2d", score);
    draw_string(0, 0, scor);
    show_screen();
}

void lifeChequer(void){
    if (lives == 0) {
        gameOverBruh();
    }
}

void gameOverBruh(void){
    clear_screen();
    drawCentred(12, "Game Over!");
    drawCentred(22, "Hope you had fun!");
    drawCentred(32, "HighScore = 67");
    show_screen();
}

void wallsBoi(void){
    if((PINF >> 5) & 0b1){ // Right Button
        wallsOn = true;
    }
    if((PINF >> 6) & 1){ // Left Button
        wallsOn = false;
    }
}
void wally(void){
    if(wallsOn == true){
        draw_line(61, 0 , 61, 15);
        draw_line(46, 48, 46, 30);
        draw_line(0, 21, 30, 21);
    }
}

void potStuff(void){
    if (adcResult < 100){
        _delay_ms(350);
    } else if (adcResult >= 100 && adcResult < 250){
        _delay_ms(275);
    } else if (adcResult >= 250 && adcResult < 400){
        _delay_ms(200);
    } else if (adcResult >= 400 && adcResult < 600){
        _delay_ms(150);
    } else if (adcResult >= 600 && adcResult < 800){
        _delay_ms(100);
    } else if (adcResult >= 800 && adcResult < 1000){
        _delay_ms(50);
    } else if (adcResult >= 1000){
        _delay_ms(0);
}
}


/* Helper Function */

void drawCentred(unsigned char y, char* string) {
    // Draw a string centred in the LCD when you don't know the string length
    unsigned char l = 0, i = 0;
    while (string[i] != '\0') {
        l++;
        i++;
    }
    char x = 42-(l*5/2);
    draw_string((x > 0) ? x : 0, y, string);
}

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    

