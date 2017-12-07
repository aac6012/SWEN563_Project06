/**
 * Implementation for communicating with Helios through GPIO PA0-PA4
 */

#include "ports.h"
#include "stm32l476xx.h"

/** 
 * Initialize ports:
 * - Turn on the peripheral clock for GPIOA
 * - Set ports PA0-PA5 to be input
 */
void GPIOA_Init(void){
	// Enable GPIOA clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN ;
	
	// Set PA0-PA4 mode to input
	GPIOA->MODER &= ~(0x03 << 2*0) ;
	GPIOA->MODER &= ~(0x03 << 2*1) ;
	GPIOA->MODER &= ~(0x03 << 2*2) ;
	GPIOA->MODER &= ~(0x03 << 2*3) ;
	GPIOA->MODER &= ~(0x03 << 2*4) ;
}


/**
 * Read data (servo positions) from ports PA0-PA3
 * Return [0,10] for position of servo
 * Return -1 if failed to get data.
 */
int getDataFromHelios(void){
	int data ;
	/*
	// Waits for Helios to send signal that data is ready to be read
	if( waitWithTimeout(TIMEOUT_VALUE) ){
		return -1 ; // Communication timeout
	}
	*/
	
	// Read the data (servo position) from GPIOA input registers PA0-PA3
	data = GPIOA->IDR & 0x0F ;
	
	/*
	// Clear PA4 to signal to Helios that the STM has received the data
	GPIOA->MODER &= ~( 2 << 2*4 ) ; // Output mode
	GPIOA->ODR &= ~(0x10) ;
	GPIOA->MODER &= ~( 3 << 2*4 ) ; // Input mode
	*/
	
	return data ;
}


/**
 * Waits for Helios to clear PA4 which signals
 * that STM32 is ready to receive more data.
 *
 * Returns 0 if success, 1 if failure
 */
int waitWithTimeout(int timeout){
	while(timeout-- > 0){
		// Wait for PA4 to be set which signals that Helios has sent data.
		if( GPIOA->IDR & HELIOS_SENT_DATA_MASK ){
			return 0 ; // Success
		}
	}
	return 1 ; // Failure
}
