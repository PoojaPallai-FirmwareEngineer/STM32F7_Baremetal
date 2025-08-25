#include <stdint.h>

#define PERIPH_BASE       0x40000000UL
#define AHB1_OFFSET       0x00020000UL
#define AHB1PERIPH_BASE   (PERIPH_BASE + AHB1_OFFSET)
#define GPIOB_OFFSET   	  0x400UL
#define GPIOB_BASE 		  (AHB1PERIPH_BASE + GPIOB_OFFSET)

#define RCC_OFFSET		  0x3800UL
#define RCC_BASE		  (AHB1PERIPH_BASE + RCC_OFFSET)

#define GPIOB_CLK_EN      (1U<<1) //  0000 0000 0000 0000 0000 0000 0000 0010

#define USER_LED1_MODER   (1U<<0)  //  0000 0000 0000 0000 0000 0000 0000 0001
#define USER_LED2_MODER   (1U<<14)
#define USER_LED3_MODER   (1U<<28)

#define USER_LED1  (1U<<0)   //Green Led
#define USER_LED2  (1U<<7)   //Blue Led
#define USER_LED3  (1U<<14)  //Red Led
typedef struct
{
	volatile uint32_t DUMMY[12];
	volatile uint32_t AHB1ENR;
}RCC_TypeDef;

typedef struct
{
 volatile uint32_t MODER;    /*!< GPIO port mode register,               Address offset: 0x00      */
 volatile uint32_t DUMMY[4];
 volatile uint32_t ODR;      /*!< GPIO port output data register,        Address offset: 0x14      */
}GPIO_TypeDef;

#define GPIOB    ((GPIO_TypeDef *)GPIOB_BASE)
#define RCC		 ((RCC_TypeDef*)RCC_BASE)

int main(void)
{
	/*Enable clock access to Port B*/
	RCC->AHB1ENR |= GPIOB_CLK_EN;

	/*Configure led pins as output pins*/
	GPIOB->MODER |= USER_LED1_MODER | USER_LED2_MODER | USER_LED3_MODER;

	while(1)
	{
		/*toggle*/
		GPIOB->ODR ^= USER_LED1 | USER_LED2 | USER_LED3;
		for(int i=0;i<1000000;i++){}
	}
}
