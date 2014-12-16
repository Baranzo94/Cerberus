
#include "Keyboard.h"

Keyboard::Keyboard()
{
	for (int i = 0; i<MAX_NO_KEYS; i++)
	{
		keysDown[i] = false;
		keysUp[i] = false;
	}
}

Keyboard::~Keyboard()
{

}

void Keyboard::update()
{
	for (int i = 0; i<MAX_NO_KEYS; i++)
	{
		keysDown[i] = false;
		keysUp[i] = false;
	}

}

void Keyboard::setKeyDown(int index)
{
	keysDown[index] = true;
}

void Keyboard::setKeyUp(int index)
{
	keysUp[index] = true;
}

bool Keyboard::isKeyDown(int index)
{
	return keysDown[index];
}

bool Keyboard::isKeyUp(int index)
{
	return keysUp[index];
}

/*void Keyboard::setKeyDown(short keyCode)
{
	keysDown[keyCode] = true;
}

void Keyboard::setKeyUp(short keyCode)
{
	keysUp[keyCode] = true;
}

bool Keyboard::isKeyDown(short keyCode)
{
	return keysDown[keyCode];
}

bool Keyboard::isKeyUp(short keyCode)
{
	return keysUp[keyCode];
}*/