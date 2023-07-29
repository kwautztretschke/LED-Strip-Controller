#include "Hardware.h"


namespace Hardware{

static CRGB s_Leds[PHYS_NUM_LEDS] = {0};

int init(){
	FastLED.addLeds<WS2812B, DATA_PIN, GRB>(s_Leds, PHYS_NUM_LEDS);
	return 0;
}

void display(CRGB* fb, uint8_t brightness){
	// map the one continuous framebuffer to the three physical segments
	// right segment
	for(int i=0;i<SEG_R_LENGTH;i++){
		int phys = SEG_R_PHYS_ADDRESS + i;
		int virt = i;
		s_Leds[phys] = fb[virt];
		s_Leds[phys].nscale8(brightness);
	}
	// middle segment
	for(int i=0;i<SEG_M_LENGTH;i++){
		int phys = SEG_M_PHYS_ADDRESS + i;
		int virt = SEG_R_LENGTH + i;
		s_Leds[phys] = fb[virt];
		s_Leds[phys].nscale8(brightness);
	}
	// left segment
	for(int i=0;i<SEG_L_LENGTH;i++){
		int phys = SEG_L_PHYS_ADDRESS + i;
		int virt = SEG_R_LENGTH + SEG_M_LENGTH + i;
		s_Leds[phys] = fb[virt];
		s_Leds[phys].nscale8(brightness);
	}

	FastLED.show();
}

void turnOff(){
	for(int i=0;i<PHYS_NUM_LEDS;i++){
		s_Leds[i] = CRGB::Black;
	}
	//TODO show once, don't torture the data pin all the time
	FastLED.show();
}

}