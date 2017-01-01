
#include <avr/io.h>
#include <util/delay.h>
#include "pinDefines.h"

static inline void initADC0(void) {
  ADMUX |= (1 << REFS0);                  /* reference voltage on AVCC */
  ADCSRA |= (1 << ADPS2);                   /* ADC clock prescaler /16 */
  ADCSRA |= (1 << ADEN);                                 /* enable ADC */
}

int main(void) {

  uint8_t ledValue;
  uint16_t adcValue;
  uint8_t i;

  initADC0();
  initDDRD();
  initDDRB();
  LED_DDR = 0xff;

  while (1) {

    PORTB ^= 0b00000011;

    ADCSRA |= (1 << ADSC);                     /* start ADC conversion */
    loop_until_bit_is_clear(ADCSRA, ADSC);          /* wait until done */
    adcValue = ADC;                                     /* read ADC in */

    //writeInt(convertAdcReading(adcValue));
    writeInt(adcValue * (5000 / 1024));
    _delay_ms(1000);
  }                                                  /* End event loop */
  return 0;                            /* This line is never reached */
}

void initDDRD() {
  DDRD |= 0b11111111;
}

void initDDRB() {
  DDRB |= 0b00000011;
}

int convertAdcReading(int adc){
  int millivolts = adc * (5000 / 1024);
  return (millivolts - 500) / 10;
}

void writeInt(int i) {
  PORTB = (i >> 8) && 0x11;
  PORTD = 0xFF & i;
}
