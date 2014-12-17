#include "Input.h"


Input::Input()
{

}

Input::~Input()
{

}

void Input::destroy()
{


}

void Input::update()
{
	m_Keyboard.update();
}

bool Input::init(const std::string& inputDBFilename)
{
	SDL_GameControllerAddMappingsFromFile(inputDBFilename.c_str());

	return true;
}