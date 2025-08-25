#define STM32F756xx
#include "stm32f7xx.h"
#include "rcc.h"

// Set the AHB1
void set_ahb1_periph_clock(uint32_t perihs)
{
	SET_BIT(RCC->AHB1ENR,perihs);
}

// Set the AHB2
void set_ahb2_periph_clock(uint32_t perihs)
{
	SET_BIT(RCC->AHB2ENR,perihs);
}

// Set the APB1
void set_apb1_periph_clock(uint32_t perihs)
{
	SET_BIT(RCC->APB1ENR,perihs);
}

// Set the APB2
void set_apb2_periph_clock(uint32_t perihs)
{
	SET_BIT(RCC->APB2ENR,perihs);
}

