#ifndef Keyboard_h
#define Keyboard_h

class Keyboard
{
public:
	Keyboard();
	~Keyboard();

	void setKeyDown(int keyCode);
	void setKeyUp(int keyCode);

	bool isKeyDown(int keyCode);
	bool isKeyUp(int keyCode);

	void update();
private:
	const static int MAX_NO_KEYS = 256;
	bool keysDown[MAX_NO_KEYS];
	bool keysUp[MAX_NO_KEYS];
};


#endif
