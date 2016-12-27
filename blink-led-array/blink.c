/* Blinker Demo */

#include <avr/io.h>
#include <util/delay.h>


int main(void) {

  DDRD |= 0b11111111;            /* Data Direction Register B:
                                    writing a one to the bit
                                    enables output. */
  while (1) {

    int i;
    for(i = 0; i < 255; i++){
      writeInt(i);
      _delay_ms(100);
    }
  }
  return (0);
}

void writeInt(int i){
  PORTD = 0xFF & i;
}
