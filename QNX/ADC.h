/**
 * ADC.h
 */

#include "ports.h"

#ifndef ADC_H_
#define ADC_H_

// See http://www.se.rit.edu/~swen-563/resources/helios/Helios%20User%20Manual.pdf Page 39
#define ADC_COMMAND_REGISTER 			( BASE_IO_REGISTER + 0 ) // Write
#define ADC_OUTPUT_LOW_REGISTER 		( BASE_IO_REGISTER + 0 ) // Read

#define ADC_PAGE_REGISTER 				( BASE_IO_REGISTER + 1 ) // Write
#define ADC_OUTPUT_HIGH_REGISTER 		( BASE_IO_REGISTER + 1 ) // Read

#define ADC_CHANNEL_REGISTER 			( BASE_IO_REGISTER + 2 ) // Write/Read

#define ADC_INPUT_GAIN_CONTROL_REGISTER ( BASE_IO_REGISTER + 3 ) // Write
#define ADC_INPUT_STATUS_REGISTER 		( BASE_IO_REGISTER + 3 ) // Read


#define MIN_ADC_OUTPUT -32768
#define MAX_ADC_OUTPUT 32767

void initADC(void) ;
void initADCPtrs(void) ;
int readADC(void) ;

#endif /* ADC_H_ */
