/**
 * Project06.c
 *
 * Main class to run the project.
 */

#include <stdlib.h>
#include <stdio.h>

#include "ports.h"
#include "ADC.h"

#define NUM_SERVO_POSITIONS 11

unsigned char calculateServoPosition(int reading) ;

int main(int argc, char *argv[]) {

	int adc_reading ;
	unsigned char servo_position ;

	initIOCtrl() ;
	initPorts() ;

	initADC() ;

	// Establish communication with STM32
	initialHandshake() ;

	while(1){
		adc_reading = readADC() ;
		servo_position = calculateServoPosition(adc_reading) ;
		if( isCommunicationActive() ){
			outputToSTM(servo_position) ;
		} else{
			printf("Communication failure between Helios and STM32!") ;
		}
	}

	return EXIT_SUCCESS;
}

/**
 * Determines which of the 11 positions the provided ADC reading corresponds to.
 * Output is in the range [0,10]
 */
unsigned char calculateServoPosition(int reading){
	return (unsigned char) ( (reading - MIN_ADC_OUTPUT) / ( (MAX_ADC_OUTPUT - MIN_ADC_OUTPUT) / NUM_SERVO_POSITIONS ) ) ;
}
