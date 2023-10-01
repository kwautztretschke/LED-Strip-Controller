#include "Program.h"
#include <string.h>
#include <stdlib.h>

#include "Hardware.h"

static class : public Program{
private:
	uint8_t m_ArtNetHistory[32] = {0};
	ArtnetHelper m_ArtnetHelper = ArtnetHelper(m_ArtNetHistory, 32);
	uint8_t m_Fade = 230;
	int m_FrameCounter = 0;
	int m_Interval = 20; // only dim once every n frames //TODO hacky!
public:
	using Program::Program;
	int init(){
		m_Name = "barFadeSync";
		return 0;
	}
	int input(char* key, char* value){
		if (!Program::input(key, value))
			return 0; //input was handled by program (e.g. colorindex)
		if (!m_ArtnetHelper.input(key, value))
			return 0; //input was handled by artnethelper
		if(!strcmp(key, "fade")){
			m_Fade = strtol(value, NULL, 10);
			return 0;
		}
		return 1; //no matching input found
	}
	void artnet(const uint8_t* data, const uint16_t size){
		m_ArtnetHelper.artnet(data, size);
	}
	void render(long ms){
		CRGB color = getColor();
		int distance = (FB_SIZE/2 * m_ArtnetHelper.getModulator()) / 512;
		if (++m_FrameCounter > m_Interval){
			m_FrameCounter = 0;
			for(int i=0; i<FB_SIZE/2; i++){
				m_FB[i].nscale8(m_Fade); //slowly dim all LEDs
			}
		}
		for(int i=0; i<distance; i++){
			m_FB[i] = m_FB[FB_SIZE/2-i-1] = color;
		}
		// copy the first half to the second half
		memcpy(m_FB + FB_SIZE/2, m_FB, FB_SIZE/2 * sizeof(CRGB));
		//TODO handle each speaker separately
	}
} barFadeSync;
