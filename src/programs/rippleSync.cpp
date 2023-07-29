#include "Program.h"
#include <string.h>
#include <stdlib.h>

#include "Hardware.h"

static class : public Program{
public:
	int m_Channel = 0;
	int m_Brightness = 255;
	enum Mode{
		R2L,
		L2R,
		OUT,
		IN
	} m_Mode = R2L;
	using Program::Program;
	int init(){
		m_Name = "rippleSync";
		return 0;
	}
	int input(char* key, char* value){
		if(!strcmp(key, "channel")){
			m_Channel = strtol(value, NULL, 10);
		}else if(!strcmp(key, "mode")){
			if(!strcmp(value, "R2L"))
				m_Mode = R2L;
			else if(!strcmp(value, "L2R"))
				m_Mode = L2R;
			else if(!strcmp(value, "OUT"))
				m_Mode = OUT;
			else if(!strcmp(value, "IN"))
				m_Mode = IN;
			else
				return 1;
		}else{
			// wrong input
			return 1;
		}
		return 0;
	}
	void artnet(const uint8_t* data, const uint16_t size){
		if(m_Channel >= size)
			return;
		m_Brightness = data[m_Channel];
	}
	void rippleL2R(CRGB c){
		for(int i=0; i<(FB_SIZE-1); i++){
			// shift each LED to the right
			m_FB[i] = m_FB[i+1];
		}
		// sync last LED
		m_FB[FB_SIZE-1] = c;
	}
	void rippleR2L(CRGB c){
		for(int i=FB_SIZE-1; i>0; i--){
			// shift each LED to the left
			m_FB[i] = m_FB[i-1];
		}
		// sync first LED
		m_FB[0] = c;
	}
	void rippleOUT(CRGB c){
		// ripple right segment to the right
		for(int i=0; i<SEG_R_LENGTH+1; i++){
			m_FB[i] = m_FB[i+1];
		}
		// ripple left segment to the left
		for(int i=FB_SIZE-1; i>(SEG_R_LENGTH+SEG_M_LENGTH-1);i--){
			m_FB[i] = m_FB[i-1];
		}
		// update center
		for(int i=0;i<SEG_M_LENGTH;i++){
			m_FB[SEG_R_LENGTH+i] = c;
		}
	}
	void rippleIN(CRGB c){
		// ripple right half to the left
		for(int i=(FB_SIZE/2)-1; i>0; i--){
			m_FB[i] = m_FB[i-1];
		}
		// ripple left half to the right
		for(int i=FB_SIZE/2; i<(FB_SIZE-1); i++){
			m_FB[i] = m_FB[i+1];
		}
		// sync outmost LEDs
		m_FB[0] = c;
		m_FB[FB_SIZE-1] = c;
	}
	
	void render(long ms){
		CRGB c = ProgramManager::getColor();
		c.nscale8(m_Brightness);
		switch(m_Mode){
			case R2L:
				rippleR2L(c);
				break;
			case L2R:
				rippleL2R(c);
				break;
			case OUT:
				rippleOUT(c);
				break;
			case IN:
				rippleIN(c);
				break;
		}
	}
} rippleSync(true);
