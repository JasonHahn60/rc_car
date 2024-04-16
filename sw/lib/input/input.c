#include "inc/Blynk.h"
#include "inc/Unified_Port_Init.h"
#include "input.h"
#include "inc/UART.h"

#define BLYNK_AUTH_TOKEN "6A1hFXD51bmKwC8Cm-G1cBJDtJEjeddx"



/*
#define BLYNK_TEMPLATE_ID "TMPLimDygxnH"
#define BLYNK_DEVICE_NAME "Lab 11"
#define BLYNK_AUTH_TOKEN "6A1hFXD51bmKwC8Cm-G1cBJDtJEjeddx"
*/

void Input_Init(void){
    //Port_E_Init();
		UART_Init();
    blynk_init("Pixel_1956", "12345678", BLYNK_AUTH_TOKEN, false);
}

// Might want to make some parser that returns the data back in some struct 
// based on the fields of the data