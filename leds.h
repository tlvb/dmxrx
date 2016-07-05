#ifndef __LEDS_H__
#define __LEDS_H__

#include <avr/io.h>
#define F_CPU 20000000
#include <util/delay.h>

#define LEDPIN PINB
#define LEDDDR DDRB
#define LEDPORT PORTB
#define LED2 PB7
#define LED1 PB6
#define LED0 PB5

#define leds_on() LEDPORT &= ~(_BV(LED2)|_BV(LED1)|_BV(LED0))
#define leds_off() LEDPORT |= _BV(LED2)|_BV(LED1)|_BV(LED0)
#define led_on(x) LEDPORT &=~ _BV(x)
#define led_off(x) LEDPORT |= _BV(x)
#define led_toggle(x) LEDPIN |= _BV(x)

void led_setup(void);
void led_hello(void);
void led_error(void);

#endif
