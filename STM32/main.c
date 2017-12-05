
#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "PWM.h"
#include "ports.h"


int main(void) {
	
	System_Clock_Init() ; // Switch System Clock = 80 MHz
	/*
	LED_Init() ;
	
	GPIOA_Init() ;
	*/
	PWM_Init() ;
	while(1){}
}
