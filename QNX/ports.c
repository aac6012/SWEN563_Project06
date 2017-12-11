/**
 * ports.c
 *
 */

#include <sys/mman.h>
#include <sys/neutrino.h>
#include <hw/inout.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "ports.h"

uintptr_t portAReg;

uintptr_t ioCtrlReg;
uintptr_t baseReg;


/**
 * Gets privity to IO ports
 * Returns 0 if success, 1 if failure
 */
int initIOCtrl(void){
    if (ThreadCtl(_NTO_TCTL_IO,NULL)){
        printf("Failed to get access to Helios IO Ports\n");
        return 1;
    }
    printf("Successfully got access to Helios IO Ports\n") ;

    ioCtrlReg  = mmap_device_io(1, IO_CTRL_REGISTER);
    baseReg    = mmap_device_io(1, BASE_IO_REGISTER);

    out8(baseReg, 0x44);
    out8(ioCtrlReg, 0x00);

    return 0;
}


/**
 * Initializes ports A and B:
 * Port A will connect to the STM32 (output)
 */
void initPorts(){
	portAReg = mmap_device_io(1, PORT_A_REGISTER);
}


/**
 * Establishes communications with the STM board.
 */
void initialHandshake(void){
	// Send initial handshake
	out8(portAReg, HELIOS_COMMUNICATION_ACTIVE_MASK) ;
	
	// Wait for response from STM32
	while( !(in8(portASReg, STM32_COMMUNICATION_ACTIVE_MASK)) ){}
	
}


/**
 * Writes the servo_pos value to the STM32.
 */
void outputToSTM(unsigned char servo_pos){
	// Maintain bits 4-7 for communication status
	unsigned char currentMSB = in8(portAReg) & 0xF0 ;
	
	// Write new data to port A
	out8(portAReg, currentMSB & servo_pos) ;
	
}


/**
 * Determine the communication status b/w Helios and STM32
 * Return 1 if communication is active, 0 if communication has failed
 */
int isCommunicationActive(void){
	return ( in8(portAReg) & STM32_COMMUNICATION_ACTIVE_MASK) ) ? 1 : 0 ;
}
