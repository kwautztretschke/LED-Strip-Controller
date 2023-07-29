#include "Hardware.h"

namespace Hardware{

#define NUM_LEDS 133
#define SEG_R_INDEX 0
#define SEG_R_LENGTH 51
#define SEG_M_INDEX 60
#define SEG_M_LENGTH 17
#define SEG_L_INDEX 86
#define SEG_L_LENGTH 47
// Sum of segment lengths: 51+17+47 = 115

static CRGB s_Leds[NUM_LEDS] = {0};

int init(){
	FastLED.addLeds<WS2812B, DATA_PIN, GRB>(s_Leds, NUM_LEDS);
	return 0;
}

void display(CRGB* fb, uint8_t brightness){
	// three loops, each a segment, from right to left
	// right segment
	for(int i=0;i<SEG_R_LENGTH;i++){
		int phys = SEG_R_INDEX + i;
		int virt = i;
		s_Leds[phys] = fb[virt];
		s_Leds[phys].nscale8(brightness);
	}
	// middle segment
	for(int i=0;i<SEG_M_LENGTH;i++){
		int phys = SEG_M_INDEX + i;
		int virt = SEG_R_LENGTH + i;
		s_Leds[phys] = fb[virt];
		s_Leds[phys].nscale8(brightness);
	}
	// left segment
	for(int i=0;i<SEG_L_LENGTH;i++){
		int phys = SEG_L_INDEX + i;
		int virt = SEG_R_LENGTH + SEG_M_LENGTH + i;
		s_Leds[phys] = fb[virt];
		s_Leds[phys].nscale8(brightness);
	}

	FastLED.show();
}

void turnOff(){
	for(int i=0;i<NUM_LEDS;i++){
		s_Leds[i] = CRGB::Black;
	}
	//TODO show once, don't torture the data pin all the time
	FastLED.show();
}

}