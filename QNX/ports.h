/**
 * ports.h
 *
 */

#ifndef PORTS_H_
#define PORTS_H_

#define BASE_IO_REGISTER 0x280
#define PORT_A_REGISTER  0x288
#define PORT_B_REGISTER  0x289
#define IO_CTRL_REGISTER 0x28B

enum port{
    PORTA,
    PORTB
};

enum pin{
    PIN0 = (uint8_t) 0x01,
    PIN1 = (uint8_t) 0x02,
    PIN2 = (uint8_t) 0x04,
    PIN3 = (uint8_t) 0x08,
    PIN4 = (uint8_t) 0x10,
    PIN5 = (uint8_t) 0x20,
    PIN6 = (uint8_t) 0x40,
    PIN7 = (uint8_t) 0x80
};

int initIOCtrl(void);
void initPorts(void);
void setPin(enum port prt, enum pin pn);
void clearPin(enum port prt, enum pin pn);

#endif /* PORTS_H_ */
