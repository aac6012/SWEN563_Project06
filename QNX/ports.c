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

uintptr_t portAReg, portBReg, portCReg;

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

    return 0;
}


/**
 * Initializes GPIO ports:
 * Port A will connect to the STM32 for servo position(output)
 * Ports B/C will be used to monitor communicatino b/w devices
 */
void initPorts(){

    ioCtrlReg  = mmap_device_io(1, IO_CTRL_REGISTER);
    baseReg    = mmap_device_io(1, BASE_IO_REGISTER);

	portAReg = mmap_device_io(1, PORT_A_REGISTER) ;
	portBReg = mmap_device_io(1, PORT_B_REGISTER) ;
	portCReg = mmap_device_io(1, PORT_C_REGISTER) ;

    out8(baseReg, 0x44);
    // Set low bits (0-3) of port C to input mode
    out8(ioCtrlReg, 0x01);

}


/**
 * Establishes communications with the STM board.
 */
void initialHandshake(void){
	// Send initial handshake
	out8(portBReg, HELIOS_COMMUNICATION_ACTIVE_MASK) ;

	// Wait for response from STM32
	while( !(in8(portCReg) & STM32_COMMUNICATION_ACTIVE_MASK) ){}
	
}


/**
 * Writes the servo_pos value to the STM32.
 */
void outputToSTM(unsigned char servo_pos){
	// Write new data to port A
	out8(portAReg, servo_pos) ;
}


/**
 * Determine the communication status b/w Helios and STM32
 * Return 1 if communication is active, 0 if communication has failed
 */
int isCommunicationActive(void){
	return ( in8(portCReg) & STM32_COMMUNICATION_ACTIVE_MASK ) ? 1 : 0 ;
}
