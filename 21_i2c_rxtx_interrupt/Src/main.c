#define STM32F756xx
#include "stm32f7xx.h"

#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "rcc.h"
#include "gpio.h"
#include "led.h"
#include "i2c.h"

// Transmission buffer (from master to slave)
const uint8_t msg[] = "Hello";
uint8_t* p_tx_buff = (uint8_t*)msg;
uint8_t tx_size = sizeof(msg);
volatile uint8_t tx_idx = 0;

// Reception buffer (on slave)
uint8_t rx_buff[sizeof(msg)];
uint8_t rx_size = sizeof(msg);
volatile uint8_t rx_idx = 0;

static void handle_i2c_master(void);

int main(void)
{
    uart3_tx_init();
    printf("Starting I2C Communication\n");

    i2c2_slave_config();       // PB10 (SCL), PB11 (SDA)
    i2c1_master_config();      // PB6  (SCL), PB9  (SDA)

    // Enable NVIC interrupt for I2C2 (slave)
    // NVIC_EnableIRQ(I2C2_EV_IRQn);

    handle_i2c_master();

    while (1)
    {
        // Waiting for interrupt-driven slave response
    }
}

static void handle_i2c_master(void)
{
	/*Set slave  address*/
	I2C1->CR2 |=SLAVE_OWN_ADDRESS;

    // 7-bit addressing
    I2C1->CR2 &= ~(1U << 11);

    // Set number of bytes to send
    I2C1->CR2 |= (tx_size << 16);

    // Enable auto-end
    I2C1->CR2 |= (1U << 25);

    // Generate START
    I2C1->CR2 |= (1U << 13);

    // Wait for STOPF flag
    while (!(I2C1->ISR & (1U << 5)))
    {
        if (I2C1->ISR & (1U << 1))  // TXIS flag
        {
            I2C1->TXDR = (*p_tx_buff++);
        }
    }

    // Clear STOP flag
    I2C1->ICR |= (1U << 5);
}

void slave_reception_callback(void)
{
	 /* Read character in Receive Data register.
	  RXNE flag is cleared by reading data in RXDR register */

	  /*Read first 8 bits */
	  rx_buff[rx_idx++] = (I2C2->RXDR & 0xFF);
}

void slave_complete_callback(void)
{
    printf("Transmission complete...\n");
}

void I2C2_EV_IRQHandler(void)
{
    if (I2C2->ISR & (1U << 3))  // ADDR matched
    {
        if (i2c2_get_address_matchcode() == SLAVE_OWN_ADDRESS)
        {
            I2C2->ICR |= (1U << 3);  // Clear ADDR
            I2C2->CR1 |= (1U << 2);  // Enable RXNE interrupt
        }
    }
    else if (I2C2->ISR & (1U << 2))  // RXNE
    {
        slave_reception_callback();
    }
    else if (I2C2->ISR & (1U << 5))  // STOPF
    {
        I2C2->ICR |= (1U << 5);  // Clear STOPF
        slave_complete_callback();
    }
    else
    {
    	// Implement Error
    }
}
