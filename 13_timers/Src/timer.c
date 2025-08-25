#define STM32F756xx
#include "stm32f7xx.h"

#define TIM1EN 		    (1U << 0)
#define CR1_CEN 		(1U << 0)


void tim1_1hz_init(void)
{
	// Enable clock access to TIM1
	RCC->APB2ENR |= TIM1EN;

	// Set the prescaler
	TIM1->PSC = 1600 - 1;

	// set auto reload value
	TIM1->ARR = 10000 - 1;

	// enable timer
	TIM1->CR1 |= CR1_CEN;
}
