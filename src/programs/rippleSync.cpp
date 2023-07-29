#include "Program.h"
#include <string.h>
#include <stdlib.h>

static class : public Program{
public:
	int m_Channel = 0;
	int m_Brightness = 255;
	using Program::Program;
	int init(){
		m_Name = "rippleSync";
		return 0;
	}
	int input(char* key, char* value){
		if(strcmp(key, "channel"))
			m_Channel = strtol(value, NULL, 10);
		else{
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
	void render(long ms){
		CRGB c = ProgramManager::getColor();
		c.nscale8(m_Brightness);
		for(int i=0; i<(NUM_LEDS-1); i++){
			// ripple backwards from last LED
			m_FB[i] = m_FB[i+1];
		}
		// sync last LED
		m_FB[NUM_LEDS-1] = c;
	}
} rippleSync(true);
