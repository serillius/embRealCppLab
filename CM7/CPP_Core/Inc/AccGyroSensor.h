/*
 * AccGyroSensor.h
 *
 *  Created on: Nov 12, 2024
 *      Author: seraphin
 */

#ifndef SRC_ACCGYROSENSOR_H_
#define SRC_ACCGYROSENSOR_H_

#include <IKS01A3_Motion.h>

class AccGyroSensor {
public:

	AccGyroSensor();
	virtual ~AccGyroSensor();
	void initSensor();
	void updateValues();
	void setZero();

	IKS01A3_Motion gyro;
	IKS01A3_Motion acc;

private:

	const uint32_t INSTANCE = 0;
	const uint32_t FUNCTION_INIT_ACC_GYRO = MOTION_ACCELERO | MOTION_GYRO;
	const uint32_t FUNCTION_ACC = MOTION_ACCELERO;
	const uint32_t FUNCTION_GYRO = MOTION_GYRO;


};

#endif /* SRC_ACCGYROSENSOR_H_ */
