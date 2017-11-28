/*
 * ports.c
 *
 */

#include "ports.h"

#include <sys/mman.h>
#include <sys/neutrino.h>
#include <hw/inout.h>
#include <pthread.h>
#include <stdio.h>

uintptr_t portAReg;
uintptr_t portBReg;

int initIOCtrl(void){
    if (ThreadCtl(_NTO_TCTL_IO,NULL)){
        printf("Failed to get access to Helios IO Ports\n");
        return -1;
    }

    ioCtrlReg  = mmap_device_io(1, IO_CTRL_REGISTER);
    baseReg    = mmap_device_io(1, BASE_IO_REGISTER);

    out8(baseReg, 0x44);
    out8(ioCtrlReg, 0x00);

    return 0;
}

/**
 * Initializes ports A and B:
 * Port A will connect to the STM32 (output)
 * Port B will connect to the signal generator (input)
 */
void initPorts(){
	portAReg = mmap_device_io(1, PORT_A_REGISTER);
	portBReg = mmap_device_io(1, PORT_B_REGISTER);
}

void setPin(enum port prt, enum pin pn){
	uint8_t pins;
	switch(prt){
		case PORTA :
			pins = in8(portAReg);
			pins |= pn;
			out8(portAReg, pins);
			break;
		case PORTB :
			pins = in8(portBReg);
			pins |= pn;
			out8(portBReg, pn);
			break;
		case PORTC :
			pins = in8(portCReg);
			pins |= pn;
			out8(portCReg, pn);
		default :
			break;
	}
}

void clearPin(enum port prt, enum pin pn){
	uint8_t pins;
	    switch(prt){
	        case PORTA :
	            pins = in8(portAReg);
	            pins &= ~pn;
	            out8(portAReg, pins);
	            break;
	        case PORTB :
	            pins = in8(portBReg);
	            pins &= ~pn;
	            out8(portBReg, pn);
	            break;
	        case PORTC :
	            pins = in8(portCReg);
	            pins &= ~pn;
	            out8(portCReg, pn);
	        default :
	            break;
	    }
}
