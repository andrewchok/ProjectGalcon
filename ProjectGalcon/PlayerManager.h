#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H
#include <stdlib.h>
#include <vector>
#include "baseTypes.h"
#include "Player.h"

class PlayerManagerC
{
public:
	/* Constants */
	static const uchar8_t NUM_PLAYERS;
	static const uint32_t PLAYER_ONE_COLOR;
	static const uint32_t PLAYER_TWO_COLOR;
	static const float_t PLAYER_START_SHIPCOUNT;


public:
	static PlayerManagerC* CreateInstance();
	static PlayerManagerC* GetInstance() { return CreateInstance(); };
	~PlayerManagerC() {};

	void init();
	void update(DWORD milliseconds);
	void render();
	void shutdown();

	// Get the of Player of player ID
	PlayerC* getPlayer(char playerID);

	int getPlayerTravellingShips(char playerID);
	
	int32_t getPlayerPercentageSelect(char playerID);

private:
	static PlayerManagerC* sInstance;
	std::vector<PlayerC*> mPlayers;

	PlayerManagerC() {};
};

#endif // !PLAYERMANAGER_H


