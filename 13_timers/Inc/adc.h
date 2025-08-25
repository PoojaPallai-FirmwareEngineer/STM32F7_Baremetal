#ifndef ADC_H_
#define ADC_H_

#define STM32F756xx
#include "stm32f7xx.h"

#include <stdint.h>

void pa4_adc1_init(void);
uint32_t adc_get_data(void);
void start_conversion(void);

#endif /* ADC_H_ */
