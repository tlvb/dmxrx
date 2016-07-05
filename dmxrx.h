#ifndef __DMXRX_H__
#define __DMXRX_H__

#include <avr/io.h>
#include <avr/interrupt.h>

#define DR_DDR DDRD
#define DR_PORT PORTD
#define DR_RX PD2
#define DR_RXEN_ PD5

#define DR_UBRRH 0
#define DR_UBRRL 4
#define DR_RXBSZ 512

#define DR_IGNORE 0xfffe
#define DR_START 0xffff

#ifndef __DMXRX_C__
extern volatile uint8_t dr_heartbeat;
extern volatile uint8_t dr_rxb[DR_RXBSZ];
#endif

void dr_setup(void);

#endif
