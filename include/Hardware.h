#ifndef __HARDWARE_H__
#define __HARDWARE_H__

#include <Arduino.h>
#include <FastLED.h>

#define DATA_PIN 13
#define PHYS_NUM_LEDS 133
#define SEG_R_PHYS_ADDRESS 0
#define SEG_R_LENGTH 51
#define SEG_M_PHYS_ADDRESS 60
#define SEG_M_LENGTH 17
#define SEG_L_PHYS_ADDRESS 86
#define SEG_L_LENGTH 47
// Sum of segment lengths: 51+17+47 = 115
#define FB_SIZE 115

namespace Hardware{

int 		init();
void		display(CRGB* fb, uint8_t brightness);
void		turnOff();

}

#endif // __HARDWARE_H__