
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#define DS_PORT    PORTB
#define DS_PIN     2
#define ST_CP_PORT PORTB
#define ST_CP_PIN  1
#define SH_CP_PORT PORTB
#define SH_CP_PIN  0
 
#define DS_low()  DS_PORT&=~_BV(DS_PIN)
#define DS_high() DS_PORT|=_BV(DS_PIN)
#define ST_CP_low()  ST_CP_PORT&=~_BV(ST_CP_PIN)
#define ST_CP_high() ST_CP_PORT|=_BV(ST_CP_PIN)
#define SH_CP_low()  SH_CP_PORT&=~_BV(SH_CP_PIN)
#define SH_CP_high() SH_CP_PORT|=_BV(SH_CP_PIN)

#define DELAY 100
#define ITERATIONS 5

int main(void);

void init_ddrb(void);

void output_led_state(uint8_t led_state);

void blink(void);

void criss_cross(void);

void knight_rider(void);
