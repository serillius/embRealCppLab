#include "cpp_main.h"
#include "main.h"

void cpp_main(){

	uint8_t button, old_button = 0;

	while(1){

		button = HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin);

		if (button > old_button) {
			HAL_EXTI_D2_EventInputConfig(EXTI_LINE3, EXTI_MODE_IT, DISABLE);
			HAL_EXTI_D1_EventInputConfig(EXTI_LINE3, EXTI_MODE_IT, ENABLE);
			HAL_EXTI_GenerateSWInterrupt(EXTI_LINE3);
		}

		old_button = button;

		HAL_Delay(10);

	}
}
