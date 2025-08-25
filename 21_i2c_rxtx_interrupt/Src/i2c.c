#define STM32F756xx
#include "stm32f7xx.h"

#include "rcc.h"
#include "gpio.h"
#include "i2c.h"

#define GPIOBEN				(1U << 1)
#define I2C2EN				(1U << 22)
#define I2C1EN				(1U << 21)

#define I2C_TIMING			0x00303D5B

static void i2c2_setOwnAddress1(uint32_t OwnAddress1, uint32_t OwnAddrSize);

void i2c2_slave_config(void)
{
	/* Enable the peripheral clock of GPIOB */
	RCC->AHB1ENR |= GPIOBEN;

	/*---------------------- I2C Slave - PIN PB10 - SCL --------------------------*/
	/* Configure PB10 mode to alternate function */
	GPIOB->MODER &= ~(1U << 20);
	GPIOB->MODER |= (1U << 21);

	/* Select alternate function type as AF4 (I2C_SCL)*/
	GPIOB->AFR[1] &= ~(1U << 8);
	GPIOB->AFR[1] &= ~(1U << 9);
	GPIOB->AFR[1] |= (1U << 10);
	GPIOB->AFR[1] &= ~(1U << 11);

	/* Set pin output type to open drain */
	GPIOB->OTYPER |= (1U << 10);

	/* Enable internal pull up resistor */
	GPIOB->PUPDR |= (1U << 20);
	GPIOB->PUPDR &= ~(1U << 21);

	/*---------------------- I2C Slave - PIN PB11 - SDA --------------------------*/
	/* Configure PB11 mode to alternate function */
	GPIOB->MODER &= ~(1U << 22);
	GPIOB->MODER |= (1U << 23);

	/* Select alternate function type as AF4 (I2C_SCL)*/
	GPIOB->AFR[1] &= ~(1U << 12);
	GPIOB->AFR[1] &= ~(1U << 13);
	GPIOB->AFR[1] |= (1U << 14);
	GPIOB->AFR[1] &= ~(1U << 15);

	/* Set pin output type to open drain */
	GPIOB->OTYPER |= (1U << 11);

	/* Enable internal pull up resistor */
	GPIOB->PUPDR |= (1U << 22);
	GPIOB->PUPDR &= ~(1U << 23);

	/*---------- Configure I2C Parameters -------------------*/
	/* Enable the Clock access to the I2C module */
	RCC->APB1ENR |= I2C2EN;

	/* Enable I2C interrupt in the NVIC */
    NVIC_EnableIRQ(I2C2_EV_IRQn);

	/* Disable I2C module */
    // I2C_CR1
    I2C2->CR1 &= ~(1U << 0);

	/* Set device address */
    i2c2_setOwnAddress1(SLAVE_OWN_ADDRESS, 0);

    /* Enable Own address */
    I2C2->OAR1 |= (1U << 15);

	/* Enable I2C module */
    I2C2->CR1 |= (1U << 0);

	/* Enable ADDR Interrupt */
    I2C2->CR1 |= (1U << 3);

	/* Enable NACK Interrupt */
    I2C2->CR1 |= (1U << 4);

	/* Enable STOP Interrupt */
    I2C2->CR1 |= (1U << 5);
}

// I2C1
// SCL - PB6
// SDA - PB7
void i2c1_master_config(void)
{
	/* Enable the peripheral clock of GPIOB */
	RCC->AHB1ENR |= GPIOBEN;

	/* I2C1 SCL Pin PB6 as : Alternate function, open drain, pull up*/
	GPIOB->MODER &= ~(1U << 12);
	GPIOB->MODER |= (1U << 13);

	GPIOB->AFR[0] &= ~(1U << 24);
	GPIOB->AFR[0] &= ~(1U << 25);
	GPIOB->AFR[0] |= (1U << 26);
	GPIOB->AFR[0] &= ~(1U << 27);

	GPIOB->OTYPER |= (1U << 6);

	GPIOB->PUPDR |= (1U << 12);
	GPIOB->PUPDR &= ~(1U << 13);

	/* I2C1 SDA Pin PB7 as : Alternate function, open drain, pull up*/
	GPIOB->MODER &= ~(1U << 18);
	GPIOB->MODER |= (1U << 19);

	GPIOB->AFR[1] &= ~(1U << 4);
	GPIOB->AFR[1] &= ~(1U << 5);
	GPIOB->AFR[1] |= (1U << 6);
	GPIOB->AFR[1] &= ~(1U << 7);

	GPIOB->OTYPER |= (1U << 9);

	GPIOB->PUPDR |= (1U << 18);
	GPIOB->PUPDR &= ~(1U << 19);

	/*---------- Configure I2C Parameters -------------------*/
	RCC->APB1ENR |= I2C1EN;

	I2C1->CR1 &= ~(1U << 0);

	// Set the timing
	I2C1->TIMINGR = I2C_TIMING;

	// Enable I2C1
	I2C1->CR1 |= (1U << 0);
}

static void i2c2_setOwnAddress1(uint32_t OwnAddress1, uint32_t OwnAddrSize)
{
    // I2C_OAR1
	MODIFY_REG(I2C2->OAR1, I2C_OAR1_OA1 | I2C_OAR1_OA1MODE, OwnAddress1 | OwnAddrSize);
}

uint32_t i2c2_get_address_matchcode(void)
{
	return (uint32_t)(READ_BIT(I2C2->ISR, I2C_ISR_ADDCODE) >> I2C_ISR_ADDCODE_Pos << 1);
}

