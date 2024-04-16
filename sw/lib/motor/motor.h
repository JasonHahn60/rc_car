#include <stdint.h>



#define MIN_SERVO 1700
#define MAX_SERVO 2300

/**
 * @brief Initalizes a PWM signal on PB5 with a clock
 * of 40 MHz to be used to control Motor1
 * 
 * @param period 
 * @param duty 
 */
void PWMA_Init(uint16_t period, uint16_t duty);

/**
 * @brief Initalizes a PWM signal on PB7 with a clock
 * of 40 MHz to be used to control Motor2
 * 
 * @param period 
 * @param duty 
 */
void PWMB_Init(uint16_t period, uint16_t duty);

/**
 * @brief Initializes a PWM signal on PA7 with a clock
 * of 40 MHz to be used to control a servo
 * 
 * @param period 
 * @param duty 
 */
void Servo_Init(uint16_t period, uint16_t duty);

/**
 * @brief Initalizes the PWM signal on PB5 and the GPIO
 * outputs on PC5-4 to control the direction
 * 
 */
void Motor1_Init();

/**
 * @brief Initalizes the PWM signal on PB7 and the GPIO
 * outputs on PC7-6 to control the direction
 * 
 */
void Motor2_Init();

/**
 * @brief Initalizes both motors and the servo
 * 
 */
void MotorServo_Init();

/**
 * @brief Changes the duty for PWMA
 * 
 * @param duty 
 */
void Motor1_Duty(uint16_t duty);

/**
 * @brief Changes the duty for PWMB
 * 
 * @param duty 
 */
void Motor2_Duty(uint16_t duty);

/**
 * @brief Changes the duty for the Servo's PWM
 * 1100 ~ 170 degrees
 * 3000 ~ 10 degrees
 * 2050 ~ 90 degrees
 * 
 * @param duty 
 */
void Servo_Duty(uint16_t duty);

/**
 * @brief Sets the appropriate GPIO C pins to 
 * tell the motor driver to go in a foward direction
 * for motor 1
 * 
 */
void Motor1_Foward(void);

/**
 * @brief Sets the appropriate GPIO C pins to 
 * tell the motor driver to go in a backwards direction
 * for motor 1
 * 
 */
void Motor1_Backwards(void);

/**
 * @brief Sets the appropriate GPIO C pins to 
 * tell the motor driver to turn off motor 1
 * 
 */
void Motor1_Off(void);

/**
 * @brief Sets the appropriate GPIO C pins to 
 * tell the motor driver to go in a foward direction
 * for motor 2
 * 
 */
void Motor2_Foward(void);

/**
 * @brief Sets the appropriate GPIO C pins to 
 * tell the motor driver to go in a backwards direction
 * for motor 2
 * 
 */
void Motor2_Backwards(void);

/**
 * @brief Sets the appropriate GPIO C pins to 
 * tell the motor driver to turn off motor 2
 * 
 */
void Motor2_Off(void);