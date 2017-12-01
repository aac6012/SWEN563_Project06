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

// TODO: tweak timeout values later after some testing.
#define HANDSHAKE_TIMEOUT_VALUE 1000000
#define TIMEOUT_VALUE 100000

// This mask is used to check if the STM is ready to receive messages through the port.
#define STM_PROCESSING_MASK 0x80

int initIOCtrl(void);
void initPorts(void);
int initialSTMHandshake(void) ;
int outputToSTM(unsigned char servo_pos);
int waitWithTimeout(int timeout) ;

#endif /* PORTS_H_ */
