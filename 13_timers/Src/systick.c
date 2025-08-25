#define STM32F756xx
#include "stm32f7xx.h"

#define SYSTICK_LOAD_VAL 		16000
#define CTRL_ENABLE 			(1U << 0)
#define CTRL_CLKSRC 			(1U << 2)
#define CTRL_COUNTFLAG 			(1U << 16)

void systickdelaysms(int delay)
{
	// Reload the number of clocks per milliseconds
	SysTick->LOAD = SYSTICK_LOAD_VAL;

	// Clear the current value register
	SysTick->VAL = 0;

	// Select clock source and enable systick
	SysTick->CTRL = CTRL_ENABLE |CTRL_CLKSRC;

	for(int i = 0; i < delay; i++)
	{
		// Wait until countflag is set
		while((SysTick->CTRL & CTRL_COUNTFLAG) == 0) {}
	}

	SysTick->CTRL = 0;
}
