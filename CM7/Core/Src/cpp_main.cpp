#include "cpp_main.h"
#include "NonBlockingSystemTickDelay.h"
#include "STM32H7Led.h"
#include "main.h"

enum class state_t {INIT, BLINK1HZ, BLINK3HZ};

void cpp_main(){

	state_t State = state_t::INIT;

	NonBlockingSystemTickDelay delay_LD1;
	STM32H7Led ld1(LD1_GPIO_Port, LD1_Pin);

	uint8_t button_new, button_old = 0;

	while(1){

		button_new = HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin);

		switch(State) {
			case state_t::INIT:
				State = state_t::BLINK1HZ;
				delay_LD1.initialise(1000);

			case state_t::BLINK1HZ:
				if (button_new and !button_old) {
					State = state_t::BLINK3HZ;
					delay_LD1.initialise(333);
				}
				if (delay_LD1.checkExpiration()) {
					ld1.toggleLED();
					delay_LD1.initialise(1000);
				}
				break;

			case state_t::BLINK3HZ:
				if (button_new and !button_old) {
					State = state_t::BLINK1HZ;
					delay_LD1.initialise(1000);
				}
				if (delay_LD1.checkExpiration()) {
					ld1.toggleLED();
					delay_LD1.initialise(333);
				}
				break;

			default:
				break;

		}

		button_old = button_new;
	}
}
