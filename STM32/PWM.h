/**
 * Header file for controlling servos through PWM
 */
 
#define DUTY_CYCLE 414
#define NUM_POSITIONS 11

#define MIN_DUTY_CYCLE_PERCENT 2
#define MAX_DUTY_CYCLE_PERCENT 12

int dutyCycleLookup[11] = {
	
} ;

void PWM_Init(void) ;
void setPosition(int position) ;
