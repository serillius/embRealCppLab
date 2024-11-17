/*
 * BlinkingLed.h
 *
 *  Created on: Nov 12, 2024
 *      Author: seraphin
 */

#ifndef SRC_BLINKINGLED_H_
#define SRC_BLINKINGLED_H_

#include <NonBlockingSystemTickDelay.h>
#include <STM32H7Led.h>

namespace myhal {

	class BlinkingLed: protected NonBlockingSystemTickDelay, protected STM32H7Led {
	public:
		BlinkingLed();
		BlinkingLed(GPIO_TypeDef* port, uint16_t pin);
		BlinkingLed(GPIO_TypeDef* port, uint16_t pin, float frequency);
		virtual ~BlinkingLed();

		void processBlinking();
		void setFrequency(float);

	private:
		uint32_t frequency_;
	};

}



#endif /* SRC_BLINKINGLED_H_ */
