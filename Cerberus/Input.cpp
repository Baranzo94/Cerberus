#include "Input.h"


Input::Input()
{

}

Input::~Input()
{

}

void Input::destroy()
{

	if (m_Mouse)
	{
		delete m_Mouse;
		m_Mouse = NULL;
	}
	if (m_Keyboard)
	{
		delete m_Keyboard;
		m_Keyboard = NULL;
	}
}

void Input::update()
{
	m_Keyboard->update();
}

bool Input::init()
{
	m_Keyboard = new Keyboard();
	m_Mouse = new Mouse();
	//SDL_GameControllerAddMappingsFromFile(inputDBFilename.c_str());

	return true;
}

//to be put in or removed from last function
/*const std::string& inputDBFilename*/