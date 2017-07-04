
#include "rs232.h"

int main()
{

  io_init(MYUBRR);

  FILE out = FDEV_SETUP_STREAM(usart_write, NULL, _FDEV_SETUP_WRITE);

  while(1)
  {
    fprintf(&out, "asdf");
    uint8_t temp = read_temp();
    fprintf(&out, "Current temperature: %d\n", temp);
    _delay_ms(5000);
  }
  return 0;
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

  TWBR = 64; // 16 MHz / (16 + 2 * 64) = 111.11kHz
  TWCR |= (1 << TWEN); // enable
}

uint8_t usart_write(char c, FILE *stream)
{
  while(!(UCSR0A & (1 << UDRE0)));
  UDR0 = c;
  return 0;
}

void i2cWaitForComplete(void)
{
  loop_until_bit_is_set(TWCR, TWINT);
}

void i2cStart(void)
{
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTA);
  i2cWaitForComplete();
}

void i2cStop(void)
{
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWSTO);
}

uint8_t i2cReadAck(void)
{
  TWCR = (1 << TWINT) | (1 << TWEN) | (1 << TWEA);
  i2cWaitForComplete();
  return TWDR;
}

uint8_t i2cReadNack(void)
{
  TWCR = (1 << TWINT) | (1 << TWEN);
  i2cWaitForComplete();
  return TWDR;
}

void i2cSend(uint8_t data)
{
  TWDR = data;
  TWCR = (1 << TWINT) | (1 << TWEN);
  i2cWaitForComplete();
}

uint8_t read_temp(void)
{
  i2cStart();
  i2cSend(SLAVE_ADDR_W);
  i2cReadAck();
  i2cSend(READ_TEMP_COMMAND);
  i2cReadAck();
  i2cStart();
  i2cSend(SLAVE_ADDR_R);
  i2cReadAck();
  uint8_t data = i2cReadNack();
  i2cStop();
  return data;
}
