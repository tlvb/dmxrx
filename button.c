#include "button.h"

inline void button_setup(void) {
	BUTTONDDR &= ~_BV(BUTTON);
	BUTTONPORT |= _BV(BUTTON);
}
