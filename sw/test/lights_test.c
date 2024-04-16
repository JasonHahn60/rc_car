#include <stdint.h>
#include "lib/lights/lights.h"

int main_lights_test(void){
    Lights_Init();
		while(1){
			PA2 ^= 0x04;
			PA3 ^= 0x08;
			PA4 ^= 0x10;
			PA5 ^= 0x20;
			for (int i = 0; i < 99999; i++){} // some delay
		}
}