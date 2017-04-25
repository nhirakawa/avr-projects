
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>

#define FOSC 16000000
#define MYUBRR FOSC/16/BAUD-1

#define DELAY 1000

void io_init(unsigned int ubrr);
void usart_transmit(unsigned char data);
uint8_t usart_write(char c, FILE *stream);

int main(void);

