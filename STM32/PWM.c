/**
 * Implementation for controlling the PWM to the Servos
 */

#include "PWM.h"
#include "stm32l476xx.h"

void PWM_Init(void) {
	
	// Enable GPIO A clock
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN ;
	
	/**
	* GPIO PA0 / TIM2 setup
	*/
	// Set GPIO PA0 mode to Alternate Function
	GPIOA->MODER &= ~(0x03) ;
	GPIOA->MODER |= 0x02 ;
	
	// Set GPIO A pin0 alternate function to AF1
	GPIOA->AFR[0] |= 0x01;
	
	// Enable Timer 2 clock
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
	
	// Max count
	TIM2->ARR = DUTY_CYCLE ;
	
	// Set the timer prescalar value
	// This value will set the PWM to 20ms periods
	TIM2->PSC =  4000;
	
	// Load new prescalar value by forcing update event.
	TIM2->EGR |= TIM_EGR_UG;
	
	// Set the input mode of the Timer (Input, CC1 is mapped to timer input 1)
	TIM2->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2 ;
	TIM2->CCMR1 |= TIM_CCMR1_OC1PE ;
	
	TIM2->CR1 |= TIM_CR1_ARPE ;
	
	// Enable input capture
	TIM2->CCER |= TIM_CCER_CC1E ;
	
	// Clear update flag
	TIM2->SR &= ~TIM_SR_UIF ;
	
	TIM2->DIER |= TIM_DIER_UIE ;
	TIM2->CR1 |= TIM_CR1_CEN ;
	
	//Initialize with 2% duty cycle
	TIM2->CCR1 = DUTY_CYCLE * (0.02) ;
	
	/**
	* GPIO PA1 / TIM5 setup
	*/
	// Set GPIO PA1 mode to Alternate Function
	GPIOA->MODER &= ~(0x03 << 2) ;
	GPIOA->MODER |= (0x02 << 2) ;
	
	// Set GPIO A pin1 to alternate function to AF2
	//GPIOA->AFR[0] &= ~(0x0F << 4) ;
	GPIOA->AFR[0] |= (0x02 << 4) ;
	
}


/**
 * Set the servo position in the range of [0,10]
 */
void setPosition(int position){
	
	
	
}
