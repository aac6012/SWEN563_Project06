/**
 * Header for communicating with Helios through GPIO PA0-PA4
 */

#ifndef __PORTS_H
#define __PORTS_H

// PB2 is used to input signal from Helios
#define HELIOS_COMMUNICATION_ACTIVE_MASK (0x01 << 2) 
// PB3 is used to output signal to Helios
#define STM32_COMMUNICATION_ACTIVE_MASK (0x01 << 3)

void GPIOAB_Init(void) ;
void initialHandshake(void) ;
int getDataFromHelios(void) ;
int isCommunicationActive(void) ;

#endif
