#include "leds.h"

void led_setup(void) {
	LEDDDR |= _BV(LED2) | _BV(LED1) | _BV(LED0);
	leds_off();
}

void led_hello(void) {
	for (uint8_t i=7; i>4; --i) {
		PORTB &=~ _BV(i);
		_delay_ms(100);
	}
	_delay_ms(200);
	for (uint8_t i=7; i>4; --i) {
		PORTB |= _BV(i);
		_delay_ms(100);
	}
	_delay_ms(200);
}

void led_error(void) {
	leds_on();
	_delay_ms(125);
	leds_off();
	_delay_ms(125);
}
