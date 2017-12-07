/**
 * Header for communicating with Helios through GPIO PA0-PA4
 */

#ifndef __PORTS_H
#define __PORTS_H
 
#define HELIOS_SENT_DATA_MASK 0x10

#define TIMEOUT_VALUE 100000

void GPIOA_Init(void) ;
int getDataFromHelios(void) ;
int waitWithTimeout(int timeout) ;

#endif
