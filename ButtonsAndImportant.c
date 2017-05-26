#include <avr/io.h>
#include "cpu_speed.h"
#include <math.h> //what's the difference between " and <
#include <util/delay.h>

char pinPos(int pos) {
  return (char)pow(2, pos + 1);
}

int main() {
  set_clock_speed(CPU_8MHz);

  //DDRx - data direction register: whether inputs or outputs
  //PORTx
  //PINx

  DDRF = 0b00000000; //sw1, sw2 all inputs
  DDRB = 0b00001100; //both LEDs as outputs, down as input, press as input
  DDRD = 0b00000000; //down as input

  // char pinSw1 = pinPos(6);//F
  // char pinSw2 = pinPos(5);//F

  // char pinLed0 = pinPos(2);//B
  // char pinLed1 = pinPos(3);//B

  // char pinUp = pinPos(1);//D
  // char pinDown = pinPos(7);//B
  // char pinPress = pinPos(0);//B

  while(1) {
    //left button turns left on, right off
    // if (PINF & pinSw1) {
    if (PINF & 0b01000000) {
      // PORTB = pinLed0;
      PORTB = 0b0000100;
    }
    // if (PINF & pinSw2) {
    if (PINF & 0b00100000) {
      // PORTB = pinLed1;
      PORTB = 0b0001000;
    }

    //up turns both on
    if (PIND & 0b00000010) {
      PORTB = 0b0001100;
    }

    //down turns both off
    if (PINB & 0b10000000) {
      PORTB = 0b00000000;
    }
    //centre press toggles current state, delay by 500ms for usability
    //_delay_ms(500)
    if (PINB & 0b00000001) {
      //port b 0b00001100
      PORTB ^= (3<<2);
      _delay_ms(500);
    }
  }

  return 0;
}