#define GAME_CPP
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "baseTypes.h"
#include "openglframework.h"	
#include "openGLStuff.h"
#include "game.h"
#include "StateManager.h"
#include "UIManager.h"
#include "PlanetManager.h"
#include "PlayerManager.h"

// Declarations
const char8_t CGame::mGameTitle[]="Project Galcon";
CGame* CGame::sInstance=nullptr;


CGame* CGame::GetInstance()
{
	if (sInstance == nullptr) sInstance = new CGame();
	return sInstance;
}

BOOL Initialize (GL_Window* window, Keys* keys)					// Any OpenGL Initialization Goes Here
{
	initOpenGLDrawing(window,keys,0.0f, 0.0f, 0.0f);
	CGame::GetInstance();
	CGame::GetInstance()->init();
	return TRUE;						
}

void CGame::init()
{
	StateManagerC::GetInstance()->init();
	UIManagerC::GetInstance()->init();
	PlanetManagerC::GetInstance()->init();
	PlayerManagerC::GetInstance()->init();
}
void CGame::UpdateFrame(DWORD milliseconds)
{
	keyProcess();

	StateManagerC* stateManager = StateManagerC::GetInstance();
	const StateManagerC::State state = stateManager->getState();
	
	stateManager->update();

	if (state == StateManagerC::State::RUNNING)
	{
		PlayerManagerC::GetInstance()->update(milliseconds);
		PlanetManagerC::GetInstance()->updatePlanets(milliseconds);

		if (checkGameOver()) stateManager->setState(StateManagerC::State::GAME_OVER);
	}
	else if (state == StateManagerC::State::RESTART)
	{
		PlayerManagerC::GetInstance()->shutdown();
		PlanetManagerC::GetInstance()->deletePlanets();

		init();
	}

}

void CGame::DrawScene(void)											
{
	startOpenGLDrawing();

	const StateManagerC::State state = StateManagerC::GetInstance()->getState();
	UIManagerC* uiManager = UIManagerC::GetInstance();

	switch (state)
	{

	case StateManagerC::State::MENU:
		UIManagerC::GetInstance()->render();
		break;

	case StateManagerC::State::RUNNING:
		uiManager->renderBackground();
		PlayerManagerC::GetInstance()->render();
		PlanetManagerC::GetInstance()->renderPlanets();
		uiManager->render();
		break;

	case StateManagerC::State::PAUSED:
		uiManager->renderBackground();
		PlayerManagerC::GetInstance()->render();
		PlanetManagerC::GetInstance()->renderPlanets();
		uiManager->render();
		break;

	case StateManagerC::State::GAME_OVER:
		uiManager->renderBackground();
		PlayerManagerC::GetInstance()->render();
		PlanetManagerC::GetInstance()->renderPlanets();
		uiManager->render();
		break;

	default:
		break;
	}
}

void CGame::shutdown()
{
	StateManagerC::GetInstance()->shutdown();
	PlayerManagerC::GetInstance()->shutdown();
	PlanetManagerC::GetInstance()->deletePlanets();
}

bool8_t CGame::checkGameOver()
{
	bool8_t gameOver = false;

	PlayerManagerC* playerManager = PlayerManagerC::GetInstance();
	PlanetManagerC* planetManager = PlanetManagerC::GetInstance();

	StateManagerC::Winner winner = StateManagerC::Winner::INVAL_WINNER;

	for (uchar8_t i = 0; i < PlayerManagerC::NUM_PLAYERS; i++)
	{
		gameOver = (planetManager->getNumPlanets(i) == 0) && (playerManager->getPlayerTravellingShips(i) == 0);

		if (gameOver)
		{
			if (i == 0) winner = StateManagerC::Winner::PLAYER_TWO;
			else if (i == 1) winner = StateManagerC::Winner::PLAYER_ONE;
			break;
		}
	}

	StateManagerC::GetInstance()->setWinner(winner);

	return gameOver;
}
void CGame::DestroyGame(void)
{
	delete StateManagerC::GetInstance();
	delete PlanetManagerC::GetInstance();
	delete PlayerManagerC::GetInstance();
}