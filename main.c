#include <avr/io.h>
#include <leds.h>
#include "dmxrx.h"
#include "button.h"
#define F_CPU 20000000
#include <util/delay.h>

#define LISTENCHAN0 200
#define LISTENCHAN1 201


int main(void) {
	led_setup();
	led_hello();
	UCSR0B |= _BV(TXEN0);
	UCSR0C |= _BV(UPM01) | _BV(UPM00) | _BV(UCSZ01) | _BV(UCSZ00);
	UBRR0H = 0;
	UBRR0L = 0;

	button_setup();
	dr_setup();
	sei();

	uint8_t state = 0x00;
	uint8_t b[3] = {0,0,0};

	const uint16_t base = 99;
	DDRA |= _BV(PA1) | _BV(PA0);
	//PORTA |= (_BV(PA0)|_BV(PA1));
	//for (;;);


	UDR0 = 0xff;
	for(;;) {

		// setting gpio pins (port a) based on the
		// monitored state of two dmx entries
		if (dr_rxb[LISTENCHAN0-1] > 0x7f || button()) {
			PORTA |= _BV(PA0);
			led_on(LED0);
		}
		else {
			PORTA &= ~(_BV(PA0));
			led_off(LED0);
		}
		if (dr_rxb[LISTENCHAN1-1] > 0x7f || button()) {
			PORTA |= _BV(PA1);
			led_on(LED2);
		}
		else {
			PORTA &= ~(_BV(PA1));
			led_off(LED2);
		}

		// put the state of some of the dmx entries onto
		// the computer connected usart for e.g. debugging,
		// a small state machine is implemented
		for (uint16_t addr = base; addr < base+8; ++addr) {
			uint8_t val = dr_rxb[addr];
			while (!(UCSR0A & (1<<UDRE0)));
			switch (state) {
			case 0x00:
				// Spreading in total 17 bits over three
				// bytes, so that they may be identified
				//
				// addr = c8  c7 c6 c5 c4  c3 c2 c1 c0
				// val	=     v7 v6 v5 v4  v3 v2 v1 v0
				//
				// b[0] =      0  0 c8 c7  c6 c5 c4 c3
				// b[1] =      0  1  0 c2  c1 c0 v7 v6
				// b[2] =      1  1 v5 v4  v3 v2 v1 v0
				//
				b[0] = (uint8_t)((addr >> 3)&0x3f);
				b[1] = (uint8_t)((((addr & 0x07)<<2)|(val>>6))&0x3f);
				b[2] = (uint8_t)(val & 0x3f);
				UDR0 = 0x00|b[0];
				//_delay_us(15);
				state = 0x40;
				break;
			case 0x40:
				UDR0 = 0x40|b[1];
				//_delay_us(15);
				state = 0xC0;
				break;
			case 0xC0:
				UDR0 = 0xC0|b[2];
				if (++val == 0) {
					addr = (addr+1) & 511;
				}
				_delay_us(1000);
			default:
				state = 0x00;
				break;
			}
		}
	}
}
