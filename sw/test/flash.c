#include <stdint.h>
#include "inc/Unified_Port_Init.h"

int main_flash(void){
	Port_F_Init();
	while(1){
		PF1 ^= 0x02;
		for(int i = 0; i < 999999; i++){};
	}
}