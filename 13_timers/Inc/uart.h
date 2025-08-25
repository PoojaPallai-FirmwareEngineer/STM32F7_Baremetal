#ifndef UART_H_
#define UART_H_

#define STM32F756xx

#include "stm32f7xx.h"
#include <stdint.h>

void uart3_tx_init(void);
uint8_t uart_read(USART_TypeDef *USARTx);
void uart3_rxtx_init(void);

#endif /* UART_H_ */
