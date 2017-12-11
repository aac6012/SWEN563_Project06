/**
 * ports.h
 *
 */

#include <stdint.h>

#ifndef PORTS_H_
#define PORTS_H_

#define BASE_IO_REGISTER 0x280
#define PORT_A_REGISTER  0x288
#define IO_CTRL_REGISTER 0x28B

// GPOIA bit 4 is used to output signal to STM32
#define HELIOS_COMMUNICATION_ACTIVE_MASK (0x01 << 4)
// GPIOA bit 5 is used to input signal from STM32
#define STM32_COMMUNICATION_ACTIVE_MASK (0x01 << 5)

int initIOCtrl(void);
void initPorts(void);
void initialHandshake(void) ;
void outputToSTM(unsigned char servo_pos);
int isCommunicationActive(void) ;

#endif /* PORTS_H_ */
