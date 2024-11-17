/*
 * BlinkingLed.cpp
 *
 *  Created on: Nov 12, 2024
 *      Author: seraphin
 */

#include "BlinkingLed.h"

namespace myhal {

	BlinkingLed::BlinkingLed() {}

	BlinkingLed::BlinkingLed(GPIO_TypeDef* port, uint16_t pin)
	: STM32H7Led(port, pin)
	{
		setFrequency(1);
		initialise(frequency_);
	}

	BlinkingLed::BlinkingLed(GPIO_TypeDef* port, uint16_t pin, float frequency)
	: STM32H7Led(port, pin)
	{
		setFrequency(frequency);
		initialise(frequency_);
	}


	BlinkingLed::~BlinkingLed() {}


	void BlinkingLed::processBlinking() {
		if (checkExpiration()) {
			toggleLED();
			initialise(frequency_);
		}
	}

	void BlinkingLed::setFrequency(float frequency) {
		if (frequency != 0) {
			frequency_ = myHelper::millToHz(frequency);
		}
	}

}

