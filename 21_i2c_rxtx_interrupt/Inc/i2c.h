/*
 * i2c.h
 *
 *  Created on: 29-Jul-2025
 *      Author: ADMIN
 */

#ifndef I2C_H_
#define I2C_H_

#define STM32F756xx
#include "stm32f7xx.h"
#include <stdint.h>

#define SLAVE_OWN_ADDRESS			0x5A

void i2c2_slave_config(void);
void i2c1_master_config(void);

#define I2C_DIRECTION_WRITE              0x00000000U
uint32_t i2c2_get_address_matchcode(void);

#endif /* I2C_H_ */
