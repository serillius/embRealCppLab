/*
 * SpiritLevel2D.cpp
 *
 *  Created on: Nov 19, 2024
 *      Author: seraphin
 */

#include "SpiritLevel2D.h"

SpiritLevel2D::SpiritLevel2D() {

}

SpiritLevel2D::~SpiritLevel2D() {

}

void SpiritLevel2D::init(I2C_HandleTypeDef *HandleToI2CDisp) {
	level.init();
	disp.setI2CSTMHandle(HandleToI2CDisp);
	disp.Init();
	level.setZero();
}

void SpiritLevel2D::setZero() {
	level.setZero();
}

void SpiritLevel2D::updateValues() {
	level.updateValues();
}

void SpiritLevel2D::show() {
	int32_t x,y,z;

	level.show();
	level.sensor.acc.getAVGValues(&x, &y, &z);

	x /= (1000/64);
	x += 64;

	y /= (1000/32);
	y += 32;

	disp.Clear();
	disp.DrawFilledCircle(x, y, 5, SSD1306_COLOR_WHITE);
	disp.DrawCircle(64, 32, 10, SSD1306_COLOR_WHITE);
	disp.UpdateScreen();

}

