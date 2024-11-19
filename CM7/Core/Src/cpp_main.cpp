#include "cpp_main.h"
#include "main.h"
#include "retarget.h"
#include <iostream>

#include "fonts.h"

#include "NonBlockingSystemTickDelay.h"
#include "SpiritLevel2D.h"

extern UART_HandleTypeDef huart3;
extern I2C_HandleTypeDef hi2c2;

void cpp_main(){
	RetargetInit(&huart3);

	std::cout << "\n\r\n\rStart up\n\r" << std::endl;

	myhal::NonBlockingSystemTickDelay delay;
	delay.initialise(500);

	SpiritLevel2D spiritLevel;
	spiritLevel.init(&hi2c2);

	while(1){

		if (delay.checkExpiration()) {
			spiritLevel.updateValues();
			spiritLevel.show();

			delay.initialise(500);
		}

		if (HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)) {
			spiritLevel.setZero();
		}

	}
}
