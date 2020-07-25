#include "InputManager.h"
#include "game.h"



InputManagerC* InputManagerC::sInstance = nullptr;


InputManagerC *InputManagerC::GetInstance()
{
	if (sInstance == nullptr)
	{
		sInstance = new InputManagerC();
	}

	return sInstance;
}

Coord2D InputManagerC::getCurrentMousePosition()
{
	return { (float_t)mouse_x, (float_t)((CGame::SCREEN_HEIGHT) - mouse_y )};
}

bool InputManagerC::getKeyEvent(uchar8_t keyIndex)
{
	if (keyIndex > 0 && keyIndex < g_keys->count)
	{
		if (keysPressed.keyDown[keyIndex] && g_keys->keyDown[keyIndex])
		{
			return false;
		}
		else if (g_keys->keyDown[keyIndex])
		{
			keysPressed.keyDown[keyIndex] = true;
		}
		else
		{
			keysPressed.keyDown[keyIndex] = false;
		}
	}

	return keysPressed.keyDown[keyIndex];
}
