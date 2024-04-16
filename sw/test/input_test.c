#include <stdint.h>
#include "lib/input/input.h"
#include "inc/Unified_Port_Init.h"
#include "inc/PLL.h"

int main_input_test(void){
	PLL_Init(Bus80MHz);
	Input_Init();
	Port_F_Init();
	while(1){
		blynk_info_t packet = blynk_to_tm4c();
		if(packet.integer_value == 1 && packet.pin_number == 0){
			PF1 ^= 0x02;
		}
	}	
}