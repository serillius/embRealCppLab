/*
 * AccGyroSensor.cpp
 *
 *  Created on: Nov 12, 2024
 *      Author: seraphin
 */

#include "AccGyroSensor.h"

AccGyroSensor::AccGyroSensor() {}

AccGyroSensor::~AccGyroSensor() {}

void AccGyroSensor::initSensor(){
	gyro.init(INSTANCE, FUNCTION_INIT_ACC_GYRO);
	//acc.init(INSTANCE, FUNCTION_INIT_ACC_GYRO);
	//acc_.init(INSTANCE, FUNCTION_ACC);
}

void AccGyroSensor::updateValues(){
	gyro.updateValues(INSTANCE, FUNCTION_GYRO);
	acc.updateValues(INSTANCE, FUNCTION_ACC);
}

void AccGyroSensor::setZero(){
	gyro.setZero(INSTANCE, FUNCTION_GYRO);
	acc.setZero(INSTANCE, FUNCTION_ACC);
}
