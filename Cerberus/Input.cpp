//
//  Input.cpp
//  GP2BaseCode
//
//  Created by Brian on 23/10/2014.
//  Copyright (c) 2014 Glasgow Caledonian University. All rights reserved.
//

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