#include "cpp_main.h"
#include "main.h"
#include "retarget.h"
#include <iostream>

#include "BlinkingLed.h"
#include "AccGyroSensor.h"
#include "IKS01A3Motion.h"

extern UART_HandleTypeDef huart3;

void cpp_main(){
	RetargetInit(&huart3);

	std::cout << "\n\r\n\rStart up\n\r" << std::endl;

	myhal::BlinkingLed ld1(LD1_GPIO_Port, LD1_Pin, 4);
	myhal::BlinkingLed ld2(LD2_GPIO_Port, LD2_Pin, 2);
	myhal::BlinkingLed ld3(LD3_GPIO_Port, LD3_Pin, 1);

	IKS01A3_Motion gyro;
	IKS01A3_Motion acc;
	AccGyroSensor sensor(gyro, acc);
	myhal::NonBlockingSystemTickDelay delay;
	sensor.initSensor();
	sensor.setZero();
	delay.initialise(500);

	int32_t x,y,z;

	while(1){
		ld1.processBlinking();
		ld2.processBlinking();
		ld3.processBlinking();

		if (delay.checkExpiration()) {
			sensor.updateValues();

			gyro.getAVGValues(&x, &y, &z);
			std::cout << "---- Gyro ----" << "\r" << std::endl;
			std::cout << "x axis: " << x << "\r" << std::endl;
			std::cout << "y axis: " << y << "\r" << std::endl;
			std::cout << "z axis: " << z << "\r" << std::endl;
			std::cout << "\n\r" << std::endl;

			acc.getAVGValues(&x, &y, &z);
			std::cout << "---- Accelerometer ----" << "\r" << std::endl;
			std::cout << "x axis: " << x << "\r" << std::endl;
			std::cout << "y axis: " << y << "\r" << std::endl;
			std::cout << "z axis: " << z << "\r" << std::endl;
			std::cout << "\n\r" << std::endl;

			delay.initialise(500);
		}

		if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)) {
			sensor.setZero();
		}

	}
}
