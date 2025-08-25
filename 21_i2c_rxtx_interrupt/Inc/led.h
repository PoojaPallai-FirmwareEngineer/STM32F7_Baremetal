/*
 * led.h
 *
 *  Created on: 27-Jun-2025
 *      Author: ADMIN
 */

#ifndef LED_H_
#define LED_H_

#define STM32F756xx

#include "stm32f7xx.h"
#include <stdint.h>

#define USER_LED1		(1U << 0) // Green led
#define USER_LED2		(1U << 7) // Blue led
#define USER_LED3		(1U << 14) // Red led

#define GREEN 			USER_LED1
#define BLUE 			USER_LED2
#define RED				USER_LED3

//#define USER_LED1_MODER			(1U << 0)
//#define USER_LED2_MODER			(1U << 14)
//#define USER_LED3_MODER			(1U << 28)

#define GPIOB_CLK_EN		(1U << 1)

typedef uint32_t ledType;

void user_leds_init(void);
void all_leds_on(void);
void all_leds_off(void);
void all_leds_toggle(void);
void led_toggle(ledType led);
void led_on(ledType led);
void led_off(ledType led);

#endif /* LED_H_ */
