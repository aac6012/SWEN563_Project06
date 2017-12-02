/**
 * ports.c
 *
 */

#include "ports.h"

#include <sys/mman.h>
#include <sys/neutrino.h>
#include <hw/inout.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

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
 * Returns 0 if success, 1 if failure.
 */
int initialSTMHandshake(void){
	//Send initial handshake
	out8(portAReg, STM_PROCESSING_MASK) ;

	// Wait for response
	return waitWithTimeout(HANDSHAKE_TIMEOUT_VALUE) ;
}



/**
 * Waits for STM32 to signal that it's ready to receive data and
 * then writes the servo_pos value to the connected port.
 *
 * After writing data, then it masks the data to tell the STM32
 * that it's finished writing the data.  The STM32 will clear this
 * bit when it's finished processing the data and ready to receive again.
 *
 * Return 0 if success, 1 if failure.
 */
int outputToSTM(unsigned char servo_pos){

	// Wait until STM is done processing last data
	if( waitWithTimeout(TIMEOUT_VALUE) != 0 ){
		return 1 ; // Failure
	}

	// Write new data to port
	out8(portAReg, servo_pos) ;

	// Write mask to signal to STM that it can process new data.
	out8(portAReg, STM_PROCESSING_MASK & servo_pos) ;

	//DEBUG CODE - in the future, STM_PROCESSING_MASK will be cleared by STM32
	out8(portAReg, servo_pos) ; // Delete this when able to test with STM

	return 0 ; // Success
}

/**
 * Waits for STM to clear bit of STM_PROCESSING_MASK
 * to signal that it's ready to receive data.
 *
 * Returns 0 if success, 1 if failure
 */
int waitWithTimeout(int timeout){
	while(timeout--	 > 0){
		// Wait for mask bit to be cleared by STM
		if( !(in8(portAReg) & STM_PROCESSING_MASK) ){
			return 0 ; // Success
		}
	}
	return 1 ; // Failure
}
