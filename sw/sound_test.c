#include <stdint.h>
#include "lib/sound/sound.h"
#include "inc/PLL.h"

int main_sound_test(void){
	PLL_Init(Bus80MHz);
	Sound_Init();
	Sound_Play(80000000/(2000*MAX_VOICEINDEX));
	while(1){}
}