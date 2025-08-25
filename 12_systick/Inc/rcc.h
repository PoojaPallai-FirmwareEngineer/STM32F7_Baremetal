#ifndef RCC_H_
#define RCC_H_

#define STM32F756xx
#include "stm32f7xx.h"

#include <stdint.h>

void set_ahb1_periph_clock(uint32_t perihs);
void set_ahb2_periph_clock(uint32_t perihs);
void set_apb1_periph_clock(uint32_t perihs);
void set_apb2_periph_clock(uint32_t perihs);

#endif /* RCC_H_ */
