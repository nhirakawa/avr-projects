
#include "rs232.h"

int main()
{

  io_init(MYUBRR);

  FILE out = FDEV_SETUP_STREAM(usart_write, NULL, _FDEV_SETUP_WRITE);

  while(1)
  {

    fputs("it's working!\n", &out);
    _delay_ms(DELAY);
    /*
       PORTD ^= 0b100;
       usart_transmit('a');
       _delay_ms(DELAY);
       usart_transmit('b');
       _delay_ms(DELAY);
       usart_transmit('\n');
       PORTD ^= 0b100;
       */
  }
}

void io_init(unsigned int ubrr)
{

  DDRD = 0b11111110;
  PORTD ^= 100;

  // set baud rate
  UBRR0H = (unsigned char) (ubrr >> 8);
  UBRR0L = (unsigned char) ubrr;

  // enable transmit
  UCSR0B = (1 << TXEN0);

  //set frame format: 8 data bits, 1 stop bits
  UCSR0C = (0 << USBS0) | (3 << UCSZ00);
}

void usart_transmit(unsigned char data)
{
  while(!(UCSR0A & (1 << UDRE0)));
  UDR0 = data;
}

uint8_t usart_write(char c, FILE *stream)
{
  while(!(UCSR0A & (1 << UDRE0)));
  UDR0 = c;
  return 0;
}
