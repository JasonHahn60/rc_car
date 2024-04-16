#include <stdint.h>
#include <stdbool.h>

#define MAX_VOICEINDEX 20
#define HORN_FREQUENCY 350

// Tells if the sound is currently playing or not
extern bool Sound_Playing;

/**
 * @brief Initalizes the DAC on port D and Timer1A 
 * to control the output
 * 
 */
void Sound_Init(void);

/**
 * @brief Stops the sound from playing and updates the flag
 * 
 */
void Sound_Stop(void);

/**
 * @brief Starts the sound at an inital period and updates the flag
 * 
 * @param period 
 */
void Sound_Play(uint16_t period);

/**
 * @brief Changes the reload value of the timer to affect
 * the period of the sound
 * 
 * @param period 
 */
void Sound_Period(uint16_t period);
