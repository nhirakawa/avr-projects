
#include "rs232.h"

#define FOSC 16000000
#define MYUBRR FOSC/16/BAUD-1

#define DELAY 1000

void io_init(unsigned int ubrr);
void usart_transmit(unsigned char data);

int main()
{

  io_init(MYUBRR);

  while(1)
  {
    PORTD ^= 0b100;
    usart_transmit('a');
    _delay_ms(DELAY);
    usart_transmit('b');
    _delay_ms(DELAY);
    usart_transmit('\n');
    PORTD ^= 0b100;
  }
}

void io_init(unsigned int ubrr)
{

  DDRD = 0b11111110;
  PORTD ^= 100;

  // set baud rate
  UBRR0H = (unsigned char) (ubrr >> 8);
  UBRR0L = (unsigned char) ubrr;

  // enable transmitter
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);

  //set frame format: 8 data bits, 1 stop bits
  UCSR0C = (0 << USBS0) | (3 << UCSZ00);
}

void usart_transmit(unsigned char data)
{
  //while(!(UCSR0A & (1 << UDRE0)))

  UDR0 = data;

}
