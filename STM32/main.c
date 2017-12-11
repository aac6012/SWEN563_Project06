
#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "PWM.h"
#include "ports.h"


int main(void) {
	
	int data ;
	
	System_Clock_Init() ; // Switch System Clock = 80 MHz
	LED_Init() ;
	GPIOAB_Init() ;
	PWM_Init() ;
	
	initialHandshake() ;
	
	/**
	 * Green LED on means Communication Error
	 */
	Green_LED_Off() ;
	
	while(1){
		if(isCommunicationActive()){
			Green_LED_Off() ;
			data = getDataFromHelios() ;
			// Verify that valid data was received
			if( data >= 0 && data <= 10 ){
				setPosition(data) ;
			}
		} else{
			Green_LED_On() ;
		}
	}
	
	while(1){}
}
