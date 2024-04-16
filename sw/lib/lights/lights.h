#include <stdbool.h>

#define PA2       (*((volatile uint32_t *)0x40004010))
#define PA3       (*((volatile uint32_t *)0x40004020))
#define PA4       (*((volatile uint32_t *)0x40004040))     
#define PA5       (*((volatile uint32_t *)0x40004080)) 

#define TURNL_2_2 PA2 
#define TURNL_1_3 PA3 
#define BRAKEL_2_4 PA4 
#define BRAKEL_1_5 PA5 

extern bool lightState;

/**
 * @brief Initalizes 4 GPIO outputs on port A
 * to be used to control 4 LEDs in the project.
 * Their pins are tied to the names of the outputs
 * on the schematic with the defines above
 * 
 * Also initalizes Timer5 to help blink the light
 * 
 */
void Lights_Init(void);