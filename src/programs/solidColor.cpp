#include "Program.h"

static class : public Program{
public:
	using Program::Program;
	int init(){
		m_Name = "solidColor";
		return 0;
	}
	int input(char* key, char* value){
		if (!Program::input(key, value))
			return 0; //input was handled by program (e.g. colorindex)
		return 1;
	}
	void render(long ms){
		for (int i=0;i<FB_SIZE;i++){
			m_FB[i] = getColor();
		}
	}
} solidColor;
