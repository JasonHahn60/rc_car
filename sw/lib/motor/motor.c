#include <stdint.h>
#include "inc/tm4c123gh6pm.h"

#define SERVO_PERIOD 25000 // gives us 20 ms
#define MOTOR_PERIOD 40000

#define PC4       (*((volatile uint32_t *)0x40006040))
#define PC5       (*((volatile uint32_t *)0x40006080))
#define PC6       (*((volatile uint32_t *)0x40006100))
#define PC7       (*((volatile uint32_t *)0x40006200))

#define INPUT1 PC4
#define INPUT2 PC5
#define INPUT3 PC6
#define INPUT4 PC7

void PWMA_Init(uint16_t period, uint16_t duty){
  SYSCTL_RCGCPWM_R |= 0x01;             // 1) activate PWM0
  SYSCTL_RCGCGPIO_R |= 0x02;            // 2) activate port B
  while((SYSCTL_PRGPIO_R & 0x02) == 0){};
  GPIO_PORTB_AFSEL_R |= 0x20;           // enable alt funct on PB5
  GPIO_PORTB_PCTL_R &= ~0x00F00000;     // configure PB5 as PWM3
  GPIO_PORTB_PCTL_R |= 0x00400000;
  GPIO_PORTB_AMSEL_R &= ~0x20;          // disable analog functionality on PB5
  GPIO_PORTB_DIR_R |= 0x20;             // PB5 output
  GPIO_PORTB_DEN_R |= 0x20;             // enable digital I/O on PB5
  SYSCTL_RCC_R = 0x001A0000 |           // 3) use PWM divider 
      (SYSCTL_RCC_R & (~0x000E0000));   //    configure for /64 divider
  PWM0_1_CTL_R = 0;                     // 4) re-loading down-counting mode
  PWM0_1_GENB_R = 0xC08;                // low on LOAD, high on CMPB down
  // PB5 goes low on LOAD
  // PB45 goes high on CMPB down
  PWM0_1_LOAD_R = period - 1;           // 5) cycles needed to count down to 0
  PWM0_1_CMPB_R = duty - 1;             // 6) count value when output rises
  PWM0_1_CTL_R |= 0x00000001;           // 7) start PWM0
  PWM0_ENABLE_R |= 0x00000008;          // enable PB5/M0PWM1B is PWM3
}

void PWMB_Init(uint16_t period, uint16_t duty){
  SYSCTL_RCGCPWM_R |= 0x01;             // 1) activate PWM0
  SYSCTL_RCGCGPIO_R |= 0x02;            // 2) activate port B
  while((SYSCTL_PRGPIO_R & 0x02) == 0){};
  GPIO_PORTB_AFSEL_R |= 0x80;           // enable alt funct on PB7
  GPIO_PORTB_PCTL_R &= ~0xF0000000;     // configure PB7 as PWM0B = M0PWM1
  GPIO_PORTB_PCTL_R |= 0x40000000;
  GPIO_PORTB_AMSEL_R &= ~0x80;          // disable analog functionality on PB7
  GPIO_PORTB_DIR_R |= 0x80;             // PB7 output
  GPIO_PORTB_DEN_R |= 0x80;             // enable digital I/O on PB7
  SYSCTL_RCC_R = 0x001A0000 |           // 3) use PWM divider 
      (SYSCTL_RCC_R & (~0x000E0000));   //    configure for /64 divider
  PWM0_0_CTL_R = 0;                     // 4) re-loading down-counting mode
  PWM0_0_GENB_R = 0xC08;                // low on LOAD, high on CMPB down
  // PB5 goes low on LOAD
  // PB45 goes high on CMPB down
  PWM0_0_LOAD_R = period - 1;           // 5) cycles needed to count down to 0
  PWM0_0_CMPB_R = duty - 1;             // 6) count value when output rises
  PWM0_0_CTL_R |= 0x00000001;           // 7) start PWM0
  PWM0_ENABLE_R |= 0x00000002;          // enable PB7/M0PWM1
}

void Servo_Init(uint16_t period, uint16_t duty){
  SYSCTL_RCGCPWM_R |= 0x02;             // 1) activate PWM1
	for(int i=0;i<99;i++){}								// delay because 1_PWM is weird
  SYSCTL_RCGCGPIO_R |= 0x01;            // 2) activate port A
  while((SYSCTL_PRGPIO_R&0x01) == 0){};
  GPIO_PORTA_AFSEL_R |= 0x80;           // enable alt funct on PA7
  GPIO_PORTA_PCTL_R &= ~0xF0000000;     // configure PA7 as PWM3
  GPIO_PORTA_PCTL_R |= 0x50000000;
  GPIO_PORTA_AMSEL_R &= ~0x80;          // disable analog functionality on PA7
  GPIO_PORTA_DIR_R |= 0x80;             // PA7 output
  GPIO_PORTA_DEN_R |= 0x80;             // enable digital I/O on PA7
  SYSCTL_RCC_R = 0x001A0000 |           // 3) use PWM divider 
      (SYSCTL_RCC_R & (~0x000E0000));   //    configure for /64 divider
  PWM1_1_CTL_R = 0;                     // 4) re-loading down-counting mode
  PWM1_1_GENB_R = 0xC08;                // low on LOAD, high on CMPA down
  //(*((volatile uint32_t *)0x400290A4)) = 0xC08;                 // low on LOAD, high on CMPA down
  // PD0 goes low on LOAD
  // PD0 goes high on CMPA down
  PWM1_1_LOAD_R = period - 1;           // 5) cycles needed to count down to 0
  PWM1_1_CMPB_R = duty - 1;             // 6) count value when output rises
  PWM1_1_CTL_R |= 0x00000001;           // 7) start PWM1
  PWM1_ENABLE_R |= 0x00000008;          // enable PD0/M0PWM3A is PWM1
}

void Motor1_Init(){
  PWMA_Init(MOTOR_PERIOD, 0);

  SYSCTL_RCGCGPIO_R     |=  0x04;          // Activate clock for Port C
  while((SYSCTL_PRGPIO_R & 0x04) == 0){};  // Allow time for clock to start

  GPIO_PORTC_PCTL_R     &= ~0x00FF0000;   // regular GPIO
  GPIO_PORTC_AMSEL_R    &= ~0x30;         // disable analog function 
  GPIO_PORTC_DIR_R      |= 0x30;          // outputs on PC5-4
  GPIO_PORTC_AFSEL_R    &= ~0x30;         // regular port function
  GPIO_PORTC_PDR_R       =  0x30;         // enable pull-down on PC5-4
  GPIO_PORTC_DEN_R      |=  0x30;         // enable digital port 
}

void Motor2_Init(){
  PWMB_Init(MOTOR_PERIOD, 0);

  SYSCTL_RCGCGPIO_R     |=  0x04;          // Activate clock for Port C
  while((SYSCTL_PRGPIO_R & 0x04) == 0){};  // Allow time for clock to start

  GPIO_PORTC_PCTL_R     &= ~0xFF000000;   // regular GPIO
  GPIO_PORTC_AMSEL_R    &= ~0xC0;         // disable analog function 
  GPIO_PORTC_DIR_R      |= 0xC0;          // outputs on PC7-6
  GPIO_PORTC_AFSEL_R    &= ~0xC0;         // regular port function
  GPIO_PORTC_PDR_R       =  0xC0;         // enable pull-down on PC7-6
  GPIO_PORTC_DEN_R      |=  0xC0;         // enable digital port 
}

void MotorServo_Init(){
  Motor1_Init();
  Motor2_Init();
  Servo_Init(SERVO_PERIOD, 2050);
}

void Motor1_Duty(uint16_t duty){
  PWM0_1_CMPB_R = duty - 1;
}

void Motor2_Duty(uint16_t duty){
  PWM0_0_CMPB_R = duty - 1;
}

void Servo_Duty(uint16_t duty){
  PWM1_1_CMPB_R = duty - 1;
}

void Motor1_Foward(void){
  INPUT1 = 0x10;
  INPUT2 = 0x00;
}

void Motor1_Backwards(void){
  INPUT1 = 0x00;
  INPUT2 = 0x20;
}

void Motor1_Off(void){
  INPUT1 = 0x00;
  INPUT2 = 0x00;
}

void Motor2_Foward(void){
  INPUT3 = 0x40;
  INPUT4 = 0x00;
}

void Motor2_Backwards(void){
  INPUT3 = 0x00;
  INPUT4 = 0x80;
}

void Motor2_Off(void){
  INPUT3 = 0x00;
  INPUT4 = 0x00;
}