/**
 * @file TLV5616.c
 * @author Evan Rosenthal, Ayan Basu
 * @brief Low level driver for the TLV5616 12-bit SPI DAC.
 * @version 0.2.0
 * @date 2022-10-07
 *
 * @copyright Copyright (c) 2022
 * @note Reference datasheet:
 *     https://www.ti.com/lit/ds/symlink/tlv5616.pdf?ts=1644622732627&ref_url=https%253A%252F%252Fwww.ti.com%252Fproduct%252FTLV5616
 */

#include "./lib/TLV5616/TLV5616.h"
#include "./inc/tm4c123gh6pm.h"

void tlv5616_init() {
	SYSCTL_RCGCSSI_R |= 0x02;
	while((SYSCTL_PRSSI_R&0x2) != 0x02);
	SSI1_CR1_R = 0x00000000;
	SSI1_CPSR_R = 0x04;
	SSI1_CR0_R = 0;
	SSI1_CR0_R |= 0x0000001F;
	SSI1_CR1_R |= 0x00000002;
    /**
     * Unified_Port_Init in Lab5.c calls Port_D_Init, which initializes the Port
     * D GPIOs for the appropriate alternate functionality (SSI).
     *
     * According to Table 15-1. SSI Signals in the datasheet, this corresponds
     * to SSI1. The corresponding Valvanoware register defines are at L302 and
     * L2670 in inc/tm4c123gh6pm.h. Use this in combination with the datasheet
     * or any existing code to write your driver! An example of how to
     * initialize SSI is found in L741 in inc/ST7735.c.
     */
	//return 0;
}

int tlv5616_output(uint16_t data) {
	while((SSI1_SR_R&0x00000002) == 0){
	}
	SSI1_DR_R = (data & 0x0FFF);
	//SSI1_DR_R = data;
    // An example of how to send data via SSI is found in L534 of inc/ST7735.c.
    return 1; // UNIMPLEMENTED
}
