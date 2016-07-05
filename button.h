#ifndef __BUTTON_H__
#define __BUTTON_H__

#include <avr/io.h>

#define BUTTONDDR DDRB
#define BUTTONPORT PORTB
#define BUTTONPIN PINB
#define BUTTON PB4

#define button() ((BUTTONPIN & _BV(BUTTON)) == 0)

void button_setup(void);

#endif
