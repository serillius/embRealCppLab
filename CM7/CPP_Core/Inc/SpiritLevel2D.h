/*
 * SpiritLevel2D.h
 *
 *  Created on: Nov 19, 2024
 *      Author: seraphin
 */

#ifndef SRC_SPIRITLEVEL2D_H_
#define SRC_SPIRITLEVEL2D_H_

#include <SpiritLevel.h>
#include "OLEDSSD1306.h"

class SpiritLevel2D {
public:
	SpiritLevel2D();
	virtual ~SpiritLevel2D();

	void init(I2C_HandleTypeDef *HandleToI2CDisp);
	void setZero();
	void updateValues();
	void show();

private:
	SpiritLevel level;
	OLED_SSD1306 disp;

};

#endif /* SRC_SPIRITLEVEL2D_H_ */
