/*
 * SpiritLevelSingleAxis3LED.cpp
 *
 *  Created on: Nov 19, 2024
 *      Author: seraphin
 */

#include <SpiritLevel.h>
#include "retarget.h"
#include <iostream>

#include "fonts.h"

SpiritLevel::SpiritLevel() {

}

SpiritLevel::~SpiritLevel() {

}

void SpiritLevel::init() {
	LedNegAngle.init(LD1_GPIO_Port, LD1_Pin);
	LedBalanced.init(LD2_GPIO_Port, LD2_Pin);
	LedPosAngle.init(LD3_GPIO_Port, LD3_Pin);

	sensor.initSensor();
}

void SpiritLevel::updateValues() {
	sensor.updateValues();
}

void SpiritLevel::show() {
	int32_t x,y,z;

	sensor.gyro.getAVGValues(&x, &y, &z);
	std::cout << "---- Gyro ----" << "\r" << std::endl;
	std::cout << "x axis: " << x << "\r" << std::endl;
	std::cout << "y axis: " << y << "\r" << std::endl;
	std::cout << "z axis: " << z << "\r" << std::endl;
	std::cout << "\n\r" << std::endl;

	sensor.acc.getAVGValues(&x, &y, &z);
	std::cout << "---- Accelerometer ----" << "\r" << std::endl;
	std::cout << "x axis: " << x << "\r" << std::endl;
	std::cout << "y axis: " << y << "\r" << std::endl;
	std::cout << "z axis: " << z << "\r" << std::endl;
	std::cout << "\n\r" << std::endl;

	if (y < -THRESHOLD){
		LedNegAngle.setLED();
		LedBalanced.unsetLED();
		LedPosAngle.unsetLED();
	} else if(y > THRESHOLD) {
		LedNegAngle.unsetLED();
		LedBalanced.unsetLED();
		LedPosAngle.setLED();
	} else {
		LedNegAngle.unsetLED();
		LedBalanced.setLED();
		LedPosAngle.unsetLED();
	}

}

void SpiritLevel::setZero() {
	sensor.setZero();
}

