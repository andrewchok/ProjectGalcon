#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "openGLFramework.h"
#include "baseTypes.h"


class InputManagerC
{
public:
	static InputManagerC*	GetInstance();
	void					init(){};
	void					update(){};

	Coord2D				getCurrentMousePosition();
	bool					getKeyEvent(uchar8_t keyIndex);

private:
	static InputManagerC *sInstance;
	Keys keysPressed;

private:
	InputManagerC(){};


};
#endif