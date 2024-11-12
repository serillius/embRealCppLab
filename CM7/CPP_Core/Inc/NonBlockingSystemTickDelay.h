/*
 * NonBlockingSystemTickDelay.h
 *
 *  Created on: Nov 5, 2024
 *      Author: seraphin
 */

#ifndef NONBLOCKINGSYSTEMTICKDELAY_H_
#define NONBLOCKINGSYSTEMTICKDELAY_H_

#include "main.h"

class NonBlockingSystemTickDelay {
public:
	NonBlockingSystemTickDelay(): wait(0), tickstart(0) {}
	virtual ~NonBlockingSystemTickDelay();

	void initialise(uint32_t delay);
	uint8_t checkExpiration();

private:
	uint32_t wait;
	uint32_t tickstart;
};


#endif /* NONBLOCKINGSYSTEMTICKDELAY_H_ */
