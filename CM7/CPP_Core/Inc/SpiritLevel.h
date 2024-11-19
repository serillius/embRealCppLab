/*
 * SpiritLevelSingleAxis3LED.h
 *
 *  Created on: Nov 19, 2024
 *      Author: seraphin
 */

#ifndef SRC_SPIRITLEVELSINGLEAXIS3LED_H_
#define SRC_SPIRITLEVELSINGLEAXIS3LED_H_

#include "AccGyroSensor.h"
#include "STM32H7Led.h"

class SpiritLevel {
public:
	SpiritLevel();
	virtual ~SpiritLevel();

	void init();
	void updateValues();
	void show();
	void setZero();

	AccGyroSensor sensor;

private:
	const uint8_t THRESHOLD = 100;
	myhal::STM32H7Led LedNegAngle;
	myhal::STM32H7Led LedBalanced;
	myhal::STM32H7Led LedPosAngle;

};

#endif /* SRC_SPIRITLEVELSINGLEAXIS3LED_H_ */
