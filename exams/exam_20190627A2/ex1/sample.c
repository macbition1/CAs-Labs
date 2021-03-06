/*----------------------------------------------------------------------------
 * Name:    sample.c
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2019 Politecnico di Torino. All rights reserved.
 *----------------------------------------------------------------------------*/
                  
#include <stdio.h>
#include "LPC17xx.h"                    /* LPC17xx definitions                */
#include "led/led.h"
#include "button/button.h"
#include "timer/timer.h"
#include "ADC_DAC/adc_dac.h"

extern int GoldbachConjecture(int x);

int pressed_button;
void sleep(void);

/*----------------------------------------------------------------------------
  Main Program
 *----------------------------------------------------------------------------*/
int main (void)
{  
	// Uncomment the instructions (and add others) according to your needs
	LED_init();					/* LED Initialization */
	BUTTON_init();				/* BUTTON Initialization */
	init_timer(0,0x0EE6B280);		/* TIMER0 Initialization */
	//enable_timer(0);
	//ADC_init();
	//DAC_init();
	int bin, result = 0;
	
	//LPC_SC->PCON |= 0x1;	/* power-down mode */								
	//LPC_SC->PCON &= 0xFFFFFFFFD; 
	//SCB->SCR |= 0x2;			/* set SLEEPONEXIT */	
	
	//ADC_start_conversion();

	//__ASM("wfi");
	
	while (1) {
		sleep();
		if (pressed_button == 0) {					/* pressed INT0 */
			bin = (bin << 1);
			result = GoldbachConjecture(bin);
			if (result > 255)
				result = 255;
			all_LED_off();
			multiple_LED_on(result);
			result = 0;
		}
		else if (pressed_button == 1)				/* pressed KEY1 */
			bin = bin << 1;
		else if (pressed_button == 2)				/* pressed KEY2 */
			bin = (bin << 1) + 1;
	}
}

void sleep(void) {
	LPC_SC->PCON |= 0x1;								/* power-down mode */								
	LPC_SC->PCON &= 0xFFFFFFFFD; 
	//SCB->SCR |= 0x2;									/* set SLEEPONEXIT */	
	__ASM("wfi");
}
