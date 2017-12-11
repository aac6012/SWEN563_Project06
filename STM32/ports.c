/**
 * Implementation for communicating with Helios through GPIO PA0-PA3 and PB2-PB3
 */

#include "ports.h"
#include "stm32l476xx.h"

/** 
 * Initialize ports A & B:
 * - Turn on the peripheral clock for GPIOA
 * - Set ports PA0-PA3 to be input
 */
void GPIO_Init(void){
	// Enable GPIOA clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN ;
	
	// Set PA0-PA3 mode to input
	GPIOA->MODER &= ~(0x03 << 2*0) ;
	GPIOA->MODER &= ~(0x03 << 2*1) ;
	GPIOA->MODER &= ~(0x03 << 2*2) ;
	GPIOA->MODER &= ~(0x03 << 2*3) ;
	
	// Enable GPIOB clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN ;
	
	// Set PB2 to input and PB3 to output
	GPIOB->MODER &= ~(0x03 << 2*2) ; 
	
	GPIOB->MODER &= ~(0x03 << 2*3) ; 
	GPIOB->MODER &= (0x01 << 2*3) ; 
	
}


/**
 * This method is used to establish communication with Helios
 */
void initialHandshake(void){
	// Set output signal to tell Helios that it's ready.
	GPIOB->ODR = STM32_COMMUNICATION_ACTIVE_MASK ;
	
	// Wait to receive signal from Helios
	while( !(GPIOB->IDR & HELIOS_COMMUNICATION_ACTIVE_MASK) ){}
	
}


/**
 * Read data (servo positions) from ports PA0-PA3
 * Return [0,10] for position of servo
 * Return -1 if failed to get data.
 */
int getDataFromHelios(void){
	int data ;
	
	// Read the data (servo position) from GPIOA input registers PA0-PA3
	data = GPIOA->IDR & 0x0F ;
	
	return data ;
}


/**
 * Determine the communication status b/w STM32 and Helios
 * Return 1 if communication is active, 0 if communication has failed
 */
int isCommunicationActive(void){
	return (GPIOB->IDR & HELIOS_COMMUNICATION_ACTIVE_MASK) ? 1 : 0 ;
}
