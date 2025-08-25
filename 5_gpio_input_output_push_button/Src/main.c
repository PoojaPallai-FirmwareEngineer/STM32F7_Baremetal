#include "stm32f756xx.h"
#include <stdint.h>

#define GPIOB_CLK_EN      (1U<<1) //  0000 0000 0000 0000 0000 0000 0000 0010
#define GPIOC_CLK_EN      (1U<<2) //  0000 0000 0000 0000 0000 0000 0000 0100

#define USER_LED1_MODER   (1U<<0)  //  0000 0000 0000 0000 0000 0000 0000 0001
#define USER_LED2_MODER   (1U<<14)
#define USER_LED3_MODER   (1U<<28)

#define USER_LED1  (1U<<0)   //Green Led
#define USER_LED2  (1U<<7)   //Blue Led
#define USER_LED3  (1U<<14)  //Red Led

#define PIN13 		(1U << 13)
#define BTN_PIN13	PIN13

int main(void)
{
	/*Enable clock access to Port B*/
	RCC->AHB1ENR |= GPIOB_CLK_EN;

	/*Enable clock access to Port C*/
	RCC->AHB1ENR |= GPIOC_CLK_EN;

	/*Configure led pins as output pins*/
	GPIOB->MODER |= USER_LED1_MODER | USER_LED2_MODER | USER_LED3_MODER;

	/*Configure led pins as input pins*/
	// Reference manual GPIO Moder. for input pins set to0 it seems clear the pins.
	GPIOC->MODER &= ~(1U << 26);
	GPIOC->MODER &= ~(1U << 27);

	while(1)
	{
		// check the button is pressed
		if(GPIOC->IDR & BTN_PIN13)
		{
			// On the led
			GPIOB->BSRR = (1U << 0) | (1U << 7) | (1U << 14);
		}
		else
		{
			// Off the led
			GPIOB->BSRR = (1U << 16) | (1U << 23) | (1U << 30);
		}
	}
}


