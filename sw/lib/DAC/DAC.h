#include <stdint.h>

/**
 * @brief Initializes the DAC with SSI1, runs at 10 MHz, 
 * 16 bits, and SCR = 0, SPH = 0, SPO = 1 Freescale
 * 
 * @param InitData initial data wanted in the DAC
 */
void DAC_Init(uint16_t InitData);

/**
 * @brief Send out data to the DAC through SSI
 * 
 * @param data 
 */
void DAC_Out(uint16_t data);