
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
	
	
	/**
	 * LED Errors:
	 * - Green = Invalid data received (outside of possible range)
	 * - Red = Communication with Helios lost
	 */
	Red_LED_Off() ;
	Green_LED_Off() ;
	
	while(1){
		if(isCommunicationActive()){
			Red_LED_Off() ;
			data = getDataFromHelios() ;
			// Verify that valid data was received
			if( data >= 0 && data <= 10 ){
				Green_LED_Off() ;
				setPosition(data) ;
			} else{
				Green_LED_On() ;
			}
		} else{
			Red_LED_On() ;
		}
	}
	
	while(1){}
}
