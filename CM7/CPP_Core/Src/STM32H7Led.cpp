/*
 * STM32H7Led.cpp
 *
 *  Created on: Nov 6, 2024
 *      Author: seraphin
 */

#include "STM32H7Led.h"

namespace myhal {

	STM32H7Led::STM32H7Led() {}

	STM32H7Led::~STM32H7Led() {}

	void STM32H7Led::init(GPIO_TypeDef* port, const uint16_t pin) {
		port_ = port;
		pin_ = pin;
	}

	void STM32H7Led::setLED() {
		HAL_GPIO_WritePin(port_, pin_, GPIO_PIN_SET);
	}

	void STM32H7Led::unsetLED(){
		HAL_GPIO_WritePin(port_, pin_, GPIO_PIN_RESET);
	}
}


