#include "Program.h"

#define SEG_LONG 27
#define SEG_BUSH 8
#define SEG_SHORT 15

static class : public Program{
public:
	using Program::Program;
	int init(){
		m_Name = "twinkle";
		return 0;
	}
	int input(char* key, char* value){
		if (!Program::input(key, value))
			return 0; //input was handled by program (e.g. colorindex)
		return 1;
	}
	void render(long ms){
		for(int i = 0; i < SEG_LONG; i++){
			m_FB[i] = CHSV((i+ms/100)%255, 255, 255);
		}
		//fill the bush segment with the same color as the middle of the long segment (cyclic)
		for(int i = 0; i < SEG_BUSH; i++){
			m_FB[i + SEG_LONG] = CHSV((i*3+ms/100)%255, 255, 255);
		}
		//fill the short segment with a shifted subtle gradient (top down)
		for(int i = 0; i < SEG_SHORT; i++){
			m_FB[FB_SIZE - i] = CHSV((i+ms/100 + 50)%255, 255, 255);
		}
		//apply a perlin noise brightness scaling to the whole strip
		for(int i = 0; i < FB_SIZE-1; i+=2){
			m_FB[i].nscale8(inoise8(i*50, ms));
			m_FB[i+1].nscale8(255 - inoise8((i+1)*50, ms));
		}
	}
} twinkle;
