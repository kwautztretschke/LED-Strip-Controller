#include "Program.h"
#include <string.h>
#include <stdlib.h>

#include "Hardware.h"

static class : public Program{
private:
	uint8_t m_ArtNetHistory[32] = {0};
	ArtnetHelper m_ArtnetHelper = ArtnetHelper(m_ArtNetHistory, 32);
public:
	using Program::Program;
	int init(){
		m_Name = "barSync";
		return 0;
	}
	int input(char* key, char* value){
		if (!Program::input(key, value))
			return 0; //input was handled by program (e.g. colorindex)
		if (!m_ArtnetHelper.input(key, value))
			return 0; //input was handled by artnethelper
		return 1; //no matching input found
	}
	void artnet(const uint8_t* data, const uint16_t size){
		m_ArtnetHelper.artnet(data, size);
	}
	void render(long ms){
		CRGB color = getColor();
		CRGB background = getColorRelative(1);
		int distance = (FB_SIZE/2 * m_ArtnetHelper.getModulator()) / 512;
		for(int i=0; i<FB_SIZE/4; i++){
			m_FB[i] = m_FB[FB_SIZE/2-i-1] = i<distance?color:background;
		}
		// copy the first half to the second half
		memcpy(m_FB + FB_SIZE/2, m_FB, FB_SIZE/2 * sizeof(CRGB));
		//TODO handle each speaker separately
	}
} barSync;
