#ifndef Input_h
#define Input_h

#ifdef __APPLE__
#include <SDL2/SDL.h>
#elif WIN32
#include <SDL.h>
#endif

#include "Keyboard.h"
#include "Mouse.h"


#include <string>
#include <vector>

class Input
{
public:
	Input();
	~Input();

	bool init(const std::string& inputDBFilename);
	void destroy();

	void update();

	Keyboard* getKeyboard()
	{
		return m_Keyboard;
	};

	Mouse* getMouse()
	{
		return m_Mouse;
	};

	static Input& getInput()
	{
		static Input input;
		return input;
	}

private:
	Keyboard *m_Keyboard;
	Mouse *m_Mouse;
};



#endif
