#ifndef TIMER_H_
#define TIMER_H_

#define STM32F756xx
#include "stm32f7xx.h"

void tim1_1hz_init(void);

#define SR_UIF 		(1U << 0)

#endif /* TIMER_H_ */
