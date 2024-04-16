#include <stdint.h>
#include "lib/motor/motor.h"
#include "inc/PWM.h"
#include "TM4C123Drivers/lib/PWM/PWM.h"
#include "inc/PLL.h"

#define PC4       (*((volatile uint32_t *)0x40006040))
#define PC5       (*((volatile uint32_t *)0x40006080))
#define PC6       (*((volatile uint32_t *)0x40006100))
#define PC7       (*((volatile uint32_t *)0x40006200))
	
#define INPUT1 PC4
#define INPUT2 PC5
#define INPUT3 PC6
#define INPUT4 PC7

int main(void){
	// Tests if each PWM works and if the duty cycle can be changed
//	 PLL_Init(Bus80MHz);
//	 Motor1_Init();
//	 Motor1_Backwards();
//	 Motor2_Init();
//	 Motor2_Backwards();
//	 Servo_Init(200, 10);
//	 while(1){
//		for(int i = 0;i< 9999999;i++){} // delay. not sure how long
//		Motor1_Duty(30000);
//		Motor2_Duty(100);
//		Servo_Duty(160);
//		for(int i = 0;i< 9999999;i++){} // delay. not sure how long
//		Motor1_Duty(10000);
//		Motor2_Duty(1500);
//		Servo_Duty(10);
//	 }
	
	// Tests how to control the servo, from 0-90-180 degrees
//	PLL_Init(Bus80MHz);
//	Servo_Init(25000, 0);
//	while(1){
//		Servo_Duty(1100);
//		for(int i = 0;i< 9999999;i++){} // delay. not sure how long
//		Servo_Duty(2050);
//		for(int i = 0;i< 9999999;i++){} // delay. not sure how long
//		Servo_Duty(3000);
//		for(int i = 0;i< 9999999;i++){} // delay. not sure how long
//	}
	
	// Tests the actual angle produced
//	PLL_Init(Bus80MHz);
//	Servo_Init(25000, 0);
//	while(1){
//		Servo_Duty(2050);
//		for(int i = 0;i< 9999999;i++){} // delay. not sure how long
//	}

	// Tests the motor and their direction
	 PLL_Init(Bus80MHz);
	 Motor1_Init();
	 Motor1_Foward();
	 Motor2_Init();
	 Motor2_Foward();
	 while(1){
		Motor1_Duty(39990);
		Motor2_Duty(39990);
		for(int i = 0;i< 9999999;i++){} // delay. not sure how long
	 }
	 
	 // Tests the motor inputs
//	 Motor1_Init();
//	 while(1){
//		 INPUT1 ^= 0x10;
//		 for(int i = 0;i< 9999;i++){} // delay. not sure how long
//	 }
}