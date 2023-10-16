#include "Program.h"
#include <string.h>
#include <stdlib.h>

#include "Hardware.h"

static class : public Program{
private:
	uint8_t m_History_R[32] = {0};
	ArtnetHelper m_ArtnetHelper_R = ArtnetHelper(m_History_R, 32, "R");
	uint8_t m_History_L[32] = {0};
	ArtnetHelper m_ArtnetHelper_L = ArtnetHelper(m_History_L, 32, "L");
	enum Mode{
		OUT,
		IN
	} m_Mode = IN;
	uint8_t m_Fade = 128;
	int m_ColorIndexOffset = 0;
	int m_FrameCounter = 0;
	int m_Interval = 20; // only dim once every n frames //TODO hacky!
public:
	using Program::Program;
	int init(){
		m_Name = "barStereoSync";
		return 0;
	}
	void activate(){
		m_ArtnetHelper_R.clearArtNetHistory();
		m_ArtnetHelper_L.clearArtNetHistory();
		m_FrameCounter = 0;
		for (int i=0;i<FB_SIZE;i++){
			m_FB[i] = CRGB::Black;
		}
	}
	int input(char* key, char* value){
		if (!Program::input(key, value))
			return 0; //input was handled by program (e.g. colorindex)
		if (!m_ArtnetHelper_R.input(key, value) || !m_ArtnetHelper_L.input(key, value))
			return 0; //input was handled by artnethelpers
		if(!strcmp(key, "fade")){
			m_Fade = strtol(value, NULL, 10);
			return 0;
		}else if(!strcmp(key, "colorindexoffset")){
			m_ColorIndexOffset = strtol(value, NULL, 10);
			return 0;
		}
		return 1; //no matching input found
	}
	void artnet(const uint8_t* data, const uint16_t size){
		m_ArtnetHelper_L.artnet(data, size);
		m_ArtnetHelper_R.artnet(data, size);
	}
	void render(long ms){
		CRGB cl = getColor();
		CRGB cr = getColorRelative(m_ColorIndexOffset);
		int dl = (FB_SIZE/2 * m_ArtnetHelper_L.getModulator()) / 512;
		int dr = (FB_SIZE/2 * m_ArtnetHelper_R.getModulator()) / 512;
		if (++m_FrameCounter > m_Interval){
			m_FrameCounter = 0;
			for(int i=0; i<FB_SIZE; i++){
				m_FB[i].nscale8(m_Fade); //slowly dim all LEDs
			}
		}
		//left speaker
		for(int i=0; i<dl; i++){
			m_FB[i] = m_FB[FB_SIZE/2-i-1] = cl;
		}
		//right speaker
		for(int i=0; i<dr; i++){
			m_FB[i + FB_SIZE/2] = m_FB[FB_SIZE-i-1] = cr;
		}

	}
} barStereoSync;
