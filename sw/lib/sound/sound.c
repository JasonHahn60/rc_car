#include <stdint.h>
#include <stdbool.h>
#include "sound.h"
#include "lib/DAC/DAC.h"
#include "inc/Timer1A.h"
#include "inc/tm4c123gh6pm.h"

bool Sound_Playing = false;

const unsigned short engine[MAX_VOICEINDEX] = {
0xd5,0xd3,0x5c,0x52,0xb6,0xe3,0x80,0x87,0x66,0x00,0x6d,0xb1,0x2b,0x50,0xb0,0x6a,
0x4b,0x66,0x69,0xd8
};

static uint8_t voiceIndex = 0;

void Sound_Handler(void){
    DAC_Out(engine[voiceIndex] << 4);
    voiceIndex = (voiceIndex+1)%MAX_VOICEINDEX;
}

void Sound_Init(void){
    DAC_Init(0);
}

void Sound_Stop(void){
    Sound_Playing = false;
    Timer1A_Disarm();
}

void Sound_Play(uint16_t period){
    Sound_Playing = true;
    Timer1A_Init(&Sound_Handler, period, 0);
}

void Sound_Period(uint16_t period){
    TIMER1_TAILR_R = period-1;
}
