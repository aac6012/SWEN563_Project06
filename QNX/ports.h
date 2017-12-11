/**
 * ports.h
 *
 */

#include <stdint.h>

#ifndef PORTS_H_
#define PORTS_H_

#define BASE_IO_REGISTER 0x280
#define PORT_A_REGISTER  0x288
#define PORT_B_REGISTER  0x289
#define PORT_C_REGISTER  0x28A
#define IO_CTRL_REGISTER 0x28B

// GPOIB bit 2 is used to output signal to STM32
#define HELIOS_COMMUNICATION_ACTIVE_MASK (0x01 << 2)
// GPIOC bit 3 is used to input signal from STM32
#define STM32_COMMUNICATION_ACTIVE_MASK (0x01 << 3)

int initIOCtrl(void);
void initPorts(void);
void initialHandshake(void) ;
void outputToSTM(unsigned char servo_pos);
int isCommunicationActive(void) ;

#endif /* PORTS_H_ */
