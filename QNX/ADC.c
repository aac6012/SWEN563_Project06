/**
 * ADC.c
 *
 * This file implements the operations to use the
 * Analog-to-Digital Converter on the Helios boxes.
 *
 */

#include <sys/mman.h>
#include <hw/inout.h>
#include <stdio.h>

#include "ADC.h"

uintptr_t 	command_reg,
			out_low_reg,
			page_reg,
			out_high_reg,
			channel_reg,
			input_gain_control_reg,
			input_status_reg ;


/**
 * Initializes the Analog-to-Digital Converter to
 */
void initADC(void) {

	initADCPtrs() ;

	// Set the input channel for ADC
	// Vin0 = pin34 on Data Acquisition
	// Set both upper and lower limits to 0 (limits to only channel 0)
	out8(channel_reg,0x00) ;

	// Set the analog input range
	// Bipolar range => [-5,5]V
	out8(input_gain_control_reg, 0x01) ;

}

/**
 * Initializes pointers to ADC ports
 */
void initADCPtrs(void){
	command_reg = mmap_device_io(1,ADC_COMMAND_REGISTER) ;
	out_low_reg = command_reg ;

	page_reg = mmap_device_io(1,ADC_PAGE_REGISTER) ;
	out_high_reg = page_reg ;

	channel_reg = mmap_device_io(1,ADC_CHANNEL_REGISTER) ;

	input_gain_control_reg = mmap_device_io(1,ADC_INPUT_GAIN_CONTROL_REGISTER) ;
	input_status_reg = input_gain_control_reg ;
}


int readADC(void){
	int8_t high, low ;
	signed int result ;

	// Initiate conversion by setting STARTAD bit (7)
	out8(command_reg, 0x80) ;

	// Wait for conversion to complete (until ADBUSY bit goes low)
	while (in8(input_status_reg) & 0x80);

	// Read results
	low = in8(out_low_reg) ;
	high = in8(out_high_reg) ;
	result = ( (int)high * 256 ) + low ;

	return result ;
}

