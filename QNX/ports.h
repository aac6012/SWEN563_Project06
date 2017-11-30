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
#define IO_CTRL_REGISTER 0x28B

int initIOCtrl(void);
void initPorts(void);

#endif /* PORTS_H_ */
