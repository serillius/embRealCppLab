#include "cpp_main.h"
#include "main.h"

void cpp_main(){


	while(1){
		HAL_Delay(10);
	}
}

void cpp_irq() {
	HAL_GPIO_TogglePin(LD1_GPIO_Port, LD1_Pin);
}
