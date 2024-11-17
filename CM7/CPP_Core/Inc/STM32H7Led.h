/*
 * STM32H7Led.h
 *
 *  Created on: Nov 6, 2024
 *      Author: seraphin
 */

#ifndef SRC_STM32H7LED_H_
#define SRC_STM32H7LED_H_

#include "main.h"

namespace myhal{
	class STM32H7Led {
	public:
		STM32H7Led();
		STM32H7Led(GPIO_TypeDef* port, const uint16_t pin) : port_(port), pin_(pin) {}
		virtual ~STM32H7Led();

		void toggleLED();

	private:
		GPIO_TypeDef* const port_;
		const uint16_t pin_;
	};
}

#endif /* SRC_STM32H7LED_H_ */
