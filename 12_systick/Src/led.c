#define STM32F756xx
#include "stm32f7xx.h"


#include "led.h"


void user_leds_init(void)
{
	RCC->AHB1ENR  |= GPIOB_CLK_EN;

	// Green Led mode
	// PB0 as output
	GPIOB->MODER  |= (1U << 0);
	GPIOB->MODER  &= ~(1U << 1);

	// Blue Led mode
	// PB7 as output
	GPIOB->MODER  |= (1U << 14);
	GPIOB->MODER  &= ~(1U << 15);

	// Red Led mode
	// PB14 as output
	GPIOB->MODER  |= (1U << 28);
	GPIOB->MODER  &= ~(1U << 29);

}

void all_leds_on(void)
{
	GPIOB->ODR |= (RED | GREEN | BLUE);
}

void all_leds_off(void)
{
	GPIOB->ODR &= ~(RED | GREEN | BLUE);
}

void all_leds_toggle(void)
{
	GPIOB->ODR ^= (RED | GREEN | BLUE);
}

void led_toggle(ledType led)
{
	GPIOB->ODR ^= led;
}

void led_on(ledType led)
{
	GPIOB->ODR |= led;
}

void led_off(ledType led)
{
	GPIOB->ODR &= ~led;
}
