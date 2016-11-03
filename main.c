#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"

#define A	GPIO_PIN_5		//Rotary encoder channel a PC5
#define B	GPIO_PIN_6		//Rotary encoder channel PC6
#define BUTTON	GPIO_PIN_7	//Rotary encodder channel PC7

volatile uint8_t encoder_counter = 0;
volatile uint8_t channel_a = 0;
volatile uint8_t channel_b = 0;

int main(void) {
	//init limits gpio
	SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
	GPIODirModeSet(GPIO_PORTC_BASE, A | B, GPIO_DIR_MODE_IN);
	GPIOPadConfigSet(GPIO_PORTC_BASE, A | B, GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);
	GPIOIntTypeSet(GPIO_PORTC_BASE, A | B, GPIO_BOTH_EDGES);

	//IntMasterEnable();
	IntEnable(INT_GPIOC);
	GPIOIntEnable(GPIO_PORTC_BASE, A | B);
	while(1){

	}
}


void Channel_ISR(void){
	uint32_t status = 0;

	status = GPIOIntStatus(GPIO_PORTC_BASE,true);
	GPIOIntClear(GPIO_PORTC_BASE,status);

	if( (status & GPIO_INT_PIN_5) == GPIO_INT_PIN_5){
	  //Then there was a pin5 interrupt
		channel_a ^= 1;
	}

	if( (status & GPIO_INT_PIN_6) == GPIO_INT_PIN_6){
	  //Then there was a pin6 interrupt
		channel_b ^= 1;
	}
}
