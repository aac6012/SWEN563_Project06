#include <string.h>
#include <stdio.h>

#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"

int main(void) {
	
	System_Clock_Init(); // Switch System Clock = 80 MHz
	LED_Init();
	
}
