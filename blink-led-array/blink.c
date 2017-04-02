#include "blink.h"

int main(void)
{
  init_ddrb();

  while (1)
  {
    for(int i = 0; i < ITERATIONS; i++)
    {
      knight_rider();
    }

    for(int i = 0; i < 2 * ITERATIONS; i++)
    {
      blink();
    }

    for(int i = 0; i < ITERATIONS; i++)
    {
      criss_cross();
    }
  }
}

void blink()
{
  uint8_t off = 0xFF;
  output_led_state(off);
  _delay_ms(4 * DELAY);
  uint8_t on = 0x00;
  output_led_state(on);
  _delay_ms(4 * DELAY);
}

void criss_cross()
{
  uint8_t pattern = 0xAA;
  for(int i = 0; i < 8; i++)
  {
    pattern = ~pattern;
    output_led_state(pattern);
    _delay_ms(2 * DELAY);
  }
}

void knight_rider()
{
  for (int i = 8; i >= 0; i--)
  {
    output_led_state(_BV(i));
    _delay_ms(DELAY);
  }
  for (int i = 0; i < 8; i++)
  {
    output_led_state(_BV(i));
    _delay_ms(DELAY);
  }
}

void init_ddrb(void)
{
  DDRB = 0b00000111; //1 = output, 0 = input
  PORTB = 0b00000000;
}

void output_led_state(uint8_t led_state)
{
  SH_CP_low();
  ST_CP_low();
  for (int i = 0; i < 8; i++)
  {
    if ((_BV(i) & led_state) != _BV(i))
    {
      DS_high();
    }
    else
    {
      DS_low();
    }

    SH_CP_high();
    SH_CP_low();
  }
  ST_CP_high();
}
