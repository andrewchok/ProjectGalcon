#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

#include "baseTypes.h"

class StateManagerC
{
public:
	enum class State
	{
		INVAL_State = -1,

		MENU,
		RUNNING,
		PAUSED,
		GAME_OVER,
		RESTART,

		MAX_STATE
	};

	enum class Mode
	{
		INVAL_MODE = -1,

		GAME,
		DEBUG,

		MAX_MODE
	};

	enum class Winner
	{
		INVAL_WINNER = -1,

		PLAYER_ONE,
		PLAYER_TWO,

		MAX_WINNER
	};

public:
	static StateManagerC	*GetInstance();
	~StateManagerC(){};

	void init();
	void update();
	void shutdown();

	State getState() const;
	void setState(State state);
	Mode getMode() const;
	void setMode(Mode mode);

	Winner getWinner() const;
	void setWinner(Winner player);



private:
	StateManagerC() noexcept {};

	static StateManagerC *sInstance;

	State mCurrentState = State::MENU;
	Mode mCurrentMode = Mode::GAME;
	Winner mCurrentWinner = Winner::INVAL_WINNER;

};


#endif // !STATE_MANAGER_H