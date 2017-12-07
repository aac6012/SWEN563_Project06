
#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "PWM.h"
#include "ports.h"


int main(void) {
	
	int data ;
	
	System_Clock_Init() ; // Switch System Clock = 80 MHz
	LED_Init() ;
	GPIOA_Init() ;
	PWM_Init() ;
	while(1){
		data = getDataFromHelios() ;
		// Verify that valid data was received
		if( data >= 0 && data <= 10 ){
			setPosition(data) ;
		}
	}
	
	while(1){}
}
