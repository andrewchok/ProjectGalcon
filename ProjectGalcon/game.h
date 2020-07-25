#ifndef GAME_H
#define GAME_H

#include "baseTypes.h"

class CGame
{
public:
	/* Constants */
	static const char8_t mGameTitle[20];
	static const uint32_t SCREEN_WIDTH = 1600;
	static const uint32_t SCREEN_HEIGHT = 900;
	static const uint32_t BITS_PER_PIXEL = 32;

public:
	~CGame();

	static CGame	*GetInstance();

	void init();
	void UpdateFrame(DWORD milliseconds);
	void DrawScene();
	void DestroyGame();
	void shutdown();

private:
	static CGame *sInstance;

private:
	CGame(){};

	bool8_t checkGameOver();
};

#endif // !GAME_H