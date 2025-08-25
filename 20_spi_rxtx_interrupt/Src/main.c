#define STM32F756xx
#include "stm32f7xx.h"

#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "rcc.h"
#include "gpio.h"
#include "led.h"
#include "spi.h"

uint8_t tx_buff[] = "Hello from SPI";
uint8_t tx_size = sizeof(tx_buff) - 1; // Avoid sending null terminator
volatile uint8_t tx_idx = 0;

uint8_t rx_buff[sizeof(tx_buff)];
uint8_t rx_size = sizeof(tx_buff) - 1;
volatile uint8_t rx_idx = 0;

void enable_spi_interrupts(void)
{
    // Enable TXE interrupt for SPI1 (Master)
    SPI1->CR2 |= SPI_CR2_TXEIE;

    // Enable RXNE interrupt for SPI3 (Slave)
    SPI3->CR2 |= SPI_CR2_RXNEIE;

    // Enable NVIC IRQs
    NVIC_EnableIRQ(SPI1_IRQn);
    NVIC_EnableIRQ(SPI3_IRQn);
}

int main(void)
{
    /* Configure Master and Slave */
    spi1_config();    // Master
    spi3_config();    // Slave

    spi3_activate();  // Enable slave first
    spi1_activate();  // Then enable master

    enable_spi_interrupts();

    while (1)
    {
        // Optional: Check if transmission and reception are complete
        if (tx_idx >= tx_size && rx_idx >= rx_size)
        {
            // Transmission complete
            // You can process rx_buff here or add a flag
        }
    }
}

/* SPI1 Master Transmit Callback */
void spi1_callback(void)
{
    if (tx_idx < tx_size)
    {
        volatile uint8_t *spidr = ((volatile uint8_t *)&SPI1->DR);
        *spidr = tx_buff[tx_idx++];
    }
    else
    {
        // Disable TXE interrupt once done
        SPI1->CR2 &= ~SPI_CR2_TXEIE;
    }
}

void SPI1_IRQHandler(void)
{
    if (SPI1->SR & SPI_SR_TXE)
    {
        spi1_callback();
    }
}

/* SPI3 Slave Receive Callback */
void spi3_callback(void)
{
    if (rx_idx < rx_size)
    {
        rx_buff[rx_idx++] = SPI3->DR;
    }
    else
    {
        // Optional: disable RXNE interrupt when complete
        SPI3->CR2 &= ~SPI_CR2_RXNEIE;
    }
}

void SPI3_IRQHandler(void)
{
    if (SPI3->SR & SPI_SR_RXNE)
    {
        spi3_callback();
    }
}
