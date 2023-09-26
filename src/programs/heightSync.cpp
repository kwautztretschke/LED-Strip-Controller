#include "Program.h"
#include <string.h>
#include <stdlib.h>

static class : public Program{
public:
	int m_Channel = 0;
	int m_Height = 0;
	int m_ColorIndex = 0;
	using Program::Program;
	int init(){
		m_Name = "heightSync";
		return 0;
	}
	int input(char* key, char* value){
		if(strcmp(key, "channel"))
			m_Channel = strtol(value, NULL, 10);
		else if(!strcmp(key, "colorindex"))	
			m_ColorIndex = strtol(value, NULL, 10);
		else{
			// wrong input
			return 1;
		}
		return 0;
	}
	void artnet(const uint8_t* data, const uint16_t size){
		if(m_Channel >= size)
			return;
		// the height can only be 0-32 anyways
		m_Height = data[m_Channel] / 8;
	}
	void render(long ms){
		for(int i=0;i<(FB_SIZE/4);i++){
			m_FB[i] = (i<=m_Height)? ProgramManager::getColor(m_ColorIndex) : CRGB::Black;
			m_FB[(FB_SIZE/2)-1 - i] = m_FB[i];
		}
		// copy the first half to the second half
		memcpy(m_FB + FB_SIZE/2, m_FB, FB_SIZE/2 * sizeof(CRGB));
	}
} heightSync;
