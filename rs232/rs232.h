
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <inttypes.h>

#define FOSC 16000000
#define MYUBRR FOSC/16/BAUD-1

#define DELAY 1000

#define READ_TEMP_COMMAND 0b00000000
#define SLAVE_ADDR_W 0b10011010
#define SLAVE_ADDR_R 0b10011011

void io_init(unsigned int ubrr);
uint8_t usart_write(char c, FILE *stream);
void i2cWaitForComplete(void);
void i2cStart(void);
void i2cStop(void);
uint8_t i2cReadAck(void);
uint8_t i2cReadNack(void);
void i2cSend(uint8_t data);

uint8_t read_temp(void);

int main(void);

