/**
 * @file        lab.c
 * @author      your name (your_email@doman.com), Jonathan Valvano, Matthew Yu
 *              <TA NAME and LAB SECTION # HERE>
 * @brief       An empty main file for running your lab.
 * @version     0.1.0
 * @date        2022-10-08 <REPLACE WITH DATE OF LAST REVISION>
 * @copyright   Copyright (c) 2022
 * @note        Potential Pinouts:
 *                  Backlight (pin 10) connected to +3.3 V
 *                  MISO (pin 9) unconnected
 *                  SCK (pin 8) connected to PA2 (SSI0Clk)
 *                  MOSI (pin 7) connected to PA5 (SSI0Tx)
 *                  TFT_CS (pin 6) connected to PA3 (SSI0Fss)
 *                  CARD_CS (pin 5) unconnected
 *                  Data/Command (pin 4) connected to PA6 (GPIO)
 *                  RESET (pin 3) connected to PA7 (GPIO)
 *                  VCC (pin 2) connected to +3.3 V
 *                  Gnd (pin 1) connected to ground
 *
 *                  Center of 10k-ohm potentiometer connected to PE2/AIN1
 *                  Bottom of 10k-ohm potentiometer connected to ground
 *                  Top of 10k-ohm potentiometer connected to +3.3V
 *
 *              Warning. Initial code for the RGB driver creates bright flashing
 *              lights. Remove this code and do not run if you have epilepsy.
 */

/** File includes. */
#include <stdint.h>

/* Register definitions. */
#include "./inc/tm4c123gh6pm.h"
/* Clocking. */
#include "./inc/PLL.h"
/* Clock delay and interrupt control. */
#include "./inc/CortexM.h"
/* Initialization of all the pins. */
#include "./inc/Unified_Port_Init.h"
/* Talking to PC via UART. */
#include "./inc/UART.h"
/* Add whatever else you need here! */
#include "lib/lights/lights.h"
#include "lib/motor/motor.h"
#include "lib/sound/sound.h"
#include "inc/Blynk.h"
#include "lib/DAC/DAC.h"

#define BLYNK_TEMPLATE_ID "TMPLimDygxnH"
#define BLYNK_DEVICE_NAME "Lab 11 Mobile"
#define BLYNK_AUTH_TOKEN "ViKTALtpbtuHBG14DDpCsj9I0Ziuh129"

#define KPN 1
#define KPD 10
#define KIN 5
#define KID 100

uint32_t motorTarget = 0;	// PWM Active Period
uint32_t motorActual = 0;	// PWM Active Period
uint32_t steeringAngle = 2050;	// range and meaning defined in motor.h
bool TURNL_1_ON = false;
bool TURNL_2_ON = false;
bool reverse = false;	// false is foward
int32_t I = 0;

int main0(void) {
    /* Disable interrupts for initialization. */
    DisableInterrupts();

    /* Initialize clocking. */
    PLL_Init(Bus80MHz);


    /* Initialize all ports. */
    // Unified_Port_Init();

		/* Used for debugging. */
		Port_F_Init();
		
		Lights_Init();	// Uses Timer5
		MotorServo_Init();
		Motor1_Foward();
		Motor2_Foward();
		Sound_Init();	// Uses Timer1
		UART_Init();
		
    /* Allows any enabled timers to begin running. */
    EnableInterrupts();
	
    blynk_init("Pixel_1956", "12345678", BLYNK_AUTH_TOKEN, false);
		
		// Sound_Play(80000000/(HORN_FREQUENCY*MAX_VOICEINDEX));

    while (1) {
			//Get control data from Blynk
			struct blynk_info packet = blynk_to_tm4c();

			if(packet.pin_number == 0){	// left turn signal
				TURNL_1_ON = packet.integer_value == 0 ? false : true;
			}else if(packet.pin_number == 1){	// right turn signal
				TURNL_2_ON = packet.integer_value == 0 ? false : true;
			}else if(packet.pin_number == 2){	// speed
				motorTarget = (uint32_t)packet.float_value;
			}else if(packet.pin_number == 3){	// steering
				// caps in case value is out of range, which should not happen
				if(packet.integer_value < MIN_SERVO){
					packet.integer_value = MIN_SERVO;
				}else if(packet.integer_value > MAX_SERVO){
					packet.integer_value = MAX_SERVO;
				}

				Servo_Duty(packet.integer_value);
			}else if(packet.pin_number == 4){	// direction
				reverse = packet.integer_value == 0 ? false : true;
				if(reverse){
					Motor1_Backwards();
					Motor2_Backwards();
				}else{
					Motor1_Foward();
					Motor2_Foward();
				}
			}else if(packet.pin_number == 5){	// horn
				bool play = packet.integer_value == 0 ? false : true;
				if(play){
					Sound_Play(80000000/(HORN_FREQUENCY*MAX_VOICEINDEX));
				}else{
					Sound_Stop();
				}
			}else if(packet.pin_number == 255){	// no data
				// do nothing
			}
			
			if(TURNL_1_ON){
				TURNL_1_3 = lightState << 3;
				PF1 = lightState << 1;
			}
			
			if(TURNL_2_ON){
				TURNL_2_2 = lightState << 2;
				PF1 = lightState << 1;
			}
			
			int32_t err = motorTarget - motorActual;
			int32_t P = (KPN * err) / KPD;
			if(P < 0){
				P = 0;         // Minimum PWM output = 300
			}
			if(P > 39990){
				P = 39990;       // Maximum PWM output = 39900
			}
			
			I = I + ((KIN * err) / KID);
			if(I <  0) {
				I = 0;         // Minimum PWM output = 300
			}
			if(I > 39990) {
				I = 39990;       // Maximum PWM output = 39900
			}
			
			int32_t U = P + I;
			if(U < 0)  {
				U = 0;           // Minimum PWM output
			}
			if(U > 39990) {
				U = 39990;         // 3000 to 39900
			}
			motorActual = U;
			Motor1_Duty(motorActual);
			Motor2_Duty(motorActual);

			if(err < -25 || reverse == true || motorTarget < 5000){	// TODO: Make the 5000 the point at which the motors don't turn on
				BRAKEL_1_5 = 1 << 5;
				BRAKEL_2_4 = 1 << 4;
			}else{
				BRAKEL_1_5 = 0;
				BRAKEL_2_4 = 0;
			}

//			UART_OutUDec(motorActual);
//			UART_OutString(" : ");
//			UART_OutUDec(err);
//			UART_OutString("\n\r");
			// for(int i = 0; i < 99999; i++){}
    }
}
