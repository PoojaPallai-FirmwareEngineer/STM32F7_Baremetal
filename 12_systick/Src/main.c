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

int sensor_value;

int main(void)
{
	uart3_rxtx_init();

	while(1)
	{
		printf("A second just passed!! \n\r");
		systickdelaysms(1000);
	}
}

