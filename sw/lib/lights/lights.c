#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "lights.h"
#include "inc/Timer5A.h"

#define LIGHT_PERIOD 40000000    // 0.5 second

 bool lightState = false;

void lightHandler(void){
    lightState = !lightState;
}


void Lights_Init(void){
    SYSCTL_RCGCGPIO_R     |=  0x01;          // Activate clock for Port A
    while((SYSCTL_PRGPIO_R & 0x01) == 0){};  // Allow time for clock to start

    GPIO_PORTA_PCTL_R     &= ~0x00FFFF00;   // regular GPIO
    GPIO_PORTA_AMSEL_R    &= ~0x3C;         // disable analog function 
    GPIO_PORTA_DIR_R      |= 0x3C;          // outputs on PA5-2
    GPIO_PORTA_AFSEL_R    &= ~0x3C;         // regular port function
    GPIO_PORTA_PDR_R       =  0x3C;         // enable pull-down on PA5-2
    GPIO_PORTA_DEN_R      |=  0x3C;         // enable digital port 

    Timer5A_Init(&lightHandler, LIGHT_PERIOD, 5);
}

