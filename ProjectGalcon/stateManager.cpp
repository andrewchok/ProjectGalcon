#define STATE_MANAGER_CPP

#include "StateManager.h"

#include "InputManager.h"

StateManagerC* StateManagerC::sInstance=nullptr;


StateManagerC *StateManagerC::GetInstance()
{
	if(sInstance==nullptr) sInstance = new StateManagerC();
	return sInstance;
}

void StateManagerC::init()
{
	mCurrentState = State::MENU;
	mCurrentMode = Mode::GAME;
	mCurrentWinner = Winner::INVAL_WINNER;
}

void StateManagerC::update()
{
	InputManagerC* inputManager = InputManagerC::GetInstance();

	switch (mCurrentState)
	{
	case State::MENU:
		if (inputManager->getKeyEvent(VK_SPACE))
			mCurrentState = State::RUNNING;
		break;

	case State::RUNNING:
		if (inputManager->getKeyEvent('P'))
			mCurrentState = State::PAUSED;
		break;

	case State::PAUSED:
		if (inputManager->getKeyEvent('P'))
			mCurrentState = State::RUNNING;
		break;

	case State::GAME_OVER:
		if (inputManager->getKeyEvent(VK_SPACE))
			mCurrentState = State::RESTART;
		break;

	default:
		break;
	}

	if (inputManager->getKeyEvent('M'))
	{
		if (mCurrentMode == Mode::DEBUG)
		{
			mCurrentMode = Mode::GAME;
		}
		else
		{
			mCurrentMode = Mode::DEBUG;
		}
	}
}

StateManagerC::State StateManagerC::getState() const
{
	return mCurrentState;
}

void StateManagerC::setState(State state)
{
	mCurrentState = state;
}
StateManagerC::Mode StateManagerC::getMode() const
{
	return mCurrentMode;
}

void StateManagerC::setMode(Mode mode)
{
	mCurrentMode = mode;
}

StateManagerC::Winner StateManagerC::getWinner() const
{
	return mCurrentWinner;
}

void StateManagerC::setWinner(Winner player)
{
	mCurrentWinner = player;
}

void StateManagerC::shutdown()
{
}