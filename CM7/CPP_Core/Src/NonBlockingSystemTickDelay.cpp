/*
 * NonBlockingSystemTickDelay.cpp
 *
 *  Created on: Nov 5, 2024
 *      Author: seraphin
 */

#include "NonBlockingSystemTickDelay.h"

NonBlockingSystemTickDelay::~NonBlockingSystemTickDelay() {}

void NonBlockingSystemTickDelay::initialise(uint32_t delay) {
	wait = delay;
	tickstart = HAL_GetTick();

}

uint8_t NonBlockingSystemTickDelay::checkExpiration() {
	return (HAL_GetTick() >= tickstart + wait);
}

