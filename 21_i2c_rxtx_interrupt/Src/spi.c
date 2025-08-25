#define STM32F756xx
#include "stm32f7xx.h"

#include "rcc.h"
#include "gpio.h"
#include "spi.h"

#define GPIOAEN		(1U<<0)
#define GPIOBEN		(1U<<1)

#define SPI1EN		(1U<<12)
#define SPI3EN		(1U<<15)

void spi1_config(void)
{
	/* Enable the peripheral clock of GPIOA */
	RCC->AHB1ENR |= GPIOAEN;

	/*Configure SPI SCK Pin PA5*/
	GPIOA->MODER &=~(1U<<10);
	GPIOA->MODER |=(1U<<11);

	/*Select alternate function type as AF5*/
	GPIOA->AFR[0] |=(1U<<20);
	GPIOA->AFR[0] &= ~(1U<<21);
	GPIOA->AFR[0] |=(1U<<22);
	GPIOA->AFR[0] &= ~(1U<<23);

	/*Set pin speed to Very High*/
	GPIOA->OSPEEDR |=(1U<<10);
	GPIOA->OSPEEDR |=(1U<<11);

	/*Enable internal pull-down*/
	GPIOA->PUPDR &=~(1U<<10);
	GPIOA->PUPDR |=(1U<<11);

	/*Configure SPI MOSI Pin PA7*/
	GPIOA->MODER &=~(1U<<14);
	GPIOA->MODER |=(1U<<15);

	/*Select alternate function type as AF5*/
	GPIOA->AFR[0] |=(1U<<28);
	GPIOA->AFR[0] &= ~(1U<<29);
	GPIOA->AFR[0] |=(1U<<30);
	GPIOA->AFR[0] &= ~(1U<<31);

	/*Set pin speed to Very High*/
	GPIOA->OSPEEDR |=(1U<<14);
	GPIOA->OSPEEDR |=(1U<<15);

	/*Enable internal pull-down*/
	GPIOA->PUPDR &=~(1U<<14);
	GPIOA->PUPDR |=(1U<<15);

	/*SPI interrupt in the NVIC*/
    NVIC_EnableIRQ(SPI1_IRQn);

    /* Configure SPI1 communication */
    RCC->APB2ENR |=SPI1EN;

	/*Set clock to fPCLK/256*/
    SPI1->CR1 |=(1U<<3);
	SPI1->CR1 |=(1U<<4);
	SPI1->CR1 |=(1U<<5);

	 /*Select TX only*/
	SPI1->CR1 |=(1U<<14);

	/*Select 1-line bidirectional data mode selected*/
	SPI1->CR1 |=(1U<<15);

	/*Set CPOL to 1 and CPHA to 1*/
	SPI1->CR1 |=(1U<<0);
	SPI1->CR1 |=(1U<<1);

	/*Set data width to 8 bit*/
	SPI1->CR2 |=(1U<<8);
	SPI1->CR2 |=(1U<<9);
	SPI1->CR2 |=(1U<<10);
	SPI1->CR2 &=~(1U<<11);

	/*Enable software slave management*/
	SPI1->CR1 |= (1U<<9);

	/*Enable Slave Select Output*/
	SPI1->CR2 |= (1U<<2);

	/*Set fifo reception threshold*/
	SPI1->CR2 |=(1U<<12);

    /* Enable TXE  Interrupt */
	SPI1->CR2 |=(1U<<7);

	/*Set mode to MASTER*/
	SPI1->CR1 |= (1U<<2);

}


void spi3_config(void)
{
	  /* Enable the peripheral clock of GPIOB */
	  RCC->AHB1ENR |= GPIOBEN;

	  /*Configure SPI3 SCK Pin PB3*/
	  GPIOB->MODER &=~(1U<<6);
	  GPIOB->MODER |=(1U<<7);

	  /*Select alternate type AF6*/
	  GPIOB->AFR[0] &=~(1U<<12);
	  GPIOB->AFR[0] |=(1U<<13);
	  GPIOB->AFR[0] |=(1U<<14);
	  GPIOB->AFR[0] &=~(1U<<15);

	  /*Set pin speed to Very High*/
	  GPIOB->OSPEEDR |=(1U<<6);
	  GPIOB->OSPEEDR |=(1U<<7);

	  /*Enable internal pull-down*/
	  GPIOB->PUPDR &=~(1U<<6);
	  GPIOB->PUPDR |=(1U<<7);

	  /*Configure SPI3 MISO Pin PB4*/
	  GPIOB->MODER &=~(1U<<8);
	  GPIOB->MODER |=(1U<<9);

	 /*Select alternate type AF6*/
	  GPIOB->AFR[0] &=~(1U<<16);
	  GPIOB->AFR[0] |=(1U<<17);
	  GPIOB->AFR[0] |=(1U<<18);
	  GPIOB->AFR[0] &=~(1U<<19);

	  /*Set pin speed to Very High*/
	  GPIOB->OSPEEDR |=(1U<<8);
	  GPIOB->OSPEEDR |=(1U<<9);

	  /*Enable internal pull-down*/
	  GPIOB->PUPDR &=~(1U<<8);
	  GPIOB->PUPDR |=(1U<<9);

	  /*Enable SPI3 interrupt in NVIC*/
	  NVIC_EnableIRQ(SPI3_IRQn);


	  /* Configure SPI3 communication */

	  /*Enable clock access to SPI3*/
	  RCC->APB1ENR |=SPI3EN;


	  /*Set clock to fPCLK/256*/
	   SPI3->CR1 |=(1U<<3);
	   SPI3->CR1 |=(1U<<4);
	  SPI3->CR1 |=(1U<<5);

	 /*Set CPOL to 1 and CPHA to 1*/
	 SPI3->CR1 |=(1U<<0);
	 SPI3->CR1 |=(1U<<1);

	/*Set data width to 8 bit*/
	SPI3->CR2 |=(1U<<8);
	SPI3->CR2 |=(1U<<9);
	SPI3->CR2 |=(1U<<10);
	SPI3->CR2 &=~(1U<<11);

	/*Enable software slave management*/
	SPI3->CR1 |= (1U<<9);

	/*Enable Slave Select Output*/
	SPI3->CR2 |= (1U<<2);

	/*Select 1-line bidirectional data mode selected*/
	SPI3->CR1 |=(1U<<15);

	 /*Select RX only*/
	SPI3->CR1 &=~(1U<<14);

	/*Set fifo reception threshold*/
	SPI3->CR2 |=(1U<<12);

	/* Enable RXNE  Interrupt */
	SPI3->CR2 |=(1U<<6);

}

void spi1_activate(void)
{
	  /* Enable SPI1 */
	  SPI1->CR1 |=(1U<<6);
}

void spi3_activate(void)
{
  /* Enable SPI3 */
  SPI3->CR1 |=(1U<<6);

}
