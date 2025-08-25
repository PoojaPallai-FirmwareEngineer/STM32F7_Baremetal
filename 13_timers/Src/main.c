#define STM32F756xx
#include "stm32f7xx.h"

#include <stdint.h>
#include <stdio.h>
#include "uart.h"
#include "rcc.h"
#include "gpio.h"
#include "led.h"
#include "adc.h"
#include "systick.h"
#include "timer.h"

int sensor_value;

int main(void)
{
	uart3_rxtx_init();
	tim1_1hz_init();

	while(1)
	{
		// Wait for UIF
		while(!(TIM1->SR & SR_UIF)) {}

		// Clear UIF
		TIM1->SR &= ~SR_UIF;
		printf("A Timer second just passed!! \n\r");
	}
}

