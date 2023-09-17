#include "Program.h"

static class : public Program{
public:
	using Program::Program;
	int init(){
		m_Name = "solidColor";
		return 0;
	}
	void render(long ms){
		m_FB[0] = ProgramManager::getColor();
	}
} solidColor;
