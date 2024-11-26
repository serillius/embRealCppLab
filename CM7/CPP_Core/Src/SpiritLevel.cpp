/*
 * SpiritLevelSingleAxis3LED.cpp
 *
 *  Created on: Nov 19, 2024
 *      Author: seraphin
 */

#include <SpiritLevel.h>
#include "retarget.h"
#include <iostream>
#include <string>
#include "util_ring_allocator_std.h"

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
	int32_t x_AVG,y_AVG,z_AVG,x_Min,y_Min,z_Min,x_Max,y_Max,z_Max;

//	sensor.gyro.getAVGValues(&x, &y, &z);
//	std::cout << "---- Gyro ----" << "\r" << std::endl;
//	std::cout << "x axis: " << x << "\r" << std::endl;
//	std::cout << "y axis: " << y << "\r" << std::endl;
//	std::cout << "z axis: " << z << "\r" << std::endl;
//	std::cout << "\n\r" << std::endl;

	std::basic_string<char,std::char_traits<char>,util::ring_allocator_std<char>> PointString;

	sensor.acc.getAVGValues(&x_AVG, &y_AVG, &z_AVG);
	sensor.acc.getMaxValues(&x_Max, &y_Max, &z_Max);
	sensor.acc.getMinValues(&x_Min, &y_Min, &z_Min);
	PointString = "---- Accelerometer ----\r\n";
	PointString.append("x AVG: ");
	PointString.append(std::to_string(x_AVG).c_str());
	PointString.append("\n\r");
	PointString.append("y AVG: ");
	PointString.append(std::to_string(y_AVG).c_str());
	PointString.append("\n\r");
	PointString.append("z AVG: ");
	PointString.append(std::to_string(z_AVG).c_str());
	PointString.append("\n\r");
	std::cout << PointString;

	std::cout << "x Min: " << x_Min << "\r" << std::endl;
	std::cout << "y Min: " << y_Min << "\r" << std::endl;
	std::cout << "z Min: " << z_Min << "\r" << std::endl;
	std::cout << "x Max: " << x_Max << "\r" << std::endl;
	std::cout << "y Max: " << y_Max << "\r" << std::endl;
	std::cout << "z Max: " << z_Max << "\r" << std::endl;
	std::cout << "\n\r" << std::endl;

	if (y_AVG < -THRESHOLD){
		LedNegAngle.setLED();
		LedBalanced.unsetLED();
		LedPosAngle.unsetLED();
	} else if(y_AVG > THRESHOLD) {
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

