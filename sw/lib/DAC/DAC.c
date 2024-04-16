#include "DAC.h"
#include "./inc/tm4c123gh6pm.h"
#include "../../inc/Unified_Port_Init.h"

// hardware connections
// **********ST7735 TFT and SDC*******************
// ST7735
// Backlight (pin 10) connected to +3.3 V
// MISO (pin 9) unconnected
// SCK (pin 8) connected to PD0 (SSI3Clk) (PA2)
// MOSI (pin 7) connected to PD3 (SSI3Tx) (PA5)
// TFT_CS (pin 6) connected to PD1 (SSI3Fss) (PA3)
// CARD_CS (pin 5) unconnected
// Data/Command (pin 4) connected to PD6 (GPIO), high for data, low for command (PA6)
// RESET (pin 3) connected to PD7 (GPIO) (PA7)
// VCC (pin 2) connected to +3.3 V
// Gnd (pin 1) connected to ground

#define SSI_SR_TNF 0x00000002  // SSI Transmit FIFO Not Full

void DAC_Init(uint16_t InitData){
    Port_D_Init();
    SYSCTL_RCGCSSI_R |= 0x02;                   //activate SSI1
    while((SYSCTL_RCGCSSI_R & 0x0002) == 0){};  //ready?
    SSI1_CR1_R = 0x00000000;		                //disable SSI, master mode
    SSI1_CPSR_R = 0x08;					                //80Mhz/8 = 10MHz SSIClk
    SSI1_CR0_R &= ~(0x0000FFF0);                //SCR = 0, SPH = 0, SPO = 1 Freescale
    SSI1_CR0_R += 0x40;					                //SPO = 1
    SSI1_CR0_R |= 0x0F;					                //DSS = 16-bit data
    SSI1_DR_R = InitData;				                //put data into transmit FIFO
    SSI1_CR1_R |= 0x00000002;		                //enable SSI
}

void DAC_Out(uint16_t data){
  while((SSI1_SR_R&SSI_SR_TNF)==0){};   // wait until transmit FIFO not full
  SSI1_DR_R = data;                     // data out
}