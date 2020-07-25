#include "PlayerManager.h"

#include "InputManager.h"
#include "PlanetManager.h"
#include "random.h"


/* Constants */

const uchar8_t PlayerManagerC::NUM_PLAYERS = 2;
const uint32_t PlayerManagerC::PLAYER_ONE_COLOR = 0x000000FF;
const uint32_t PlayerManagerC::PLAYER_TWO_COLOR = 0x00FF0000;
const float_t PlayerManagerC::PLAYER_START_SHIPCOUNT = 50.0f;


PlayerManagerC* PlayerManagerC::sInstance = nullptr;


/* Methods */

PlayerManagerC* PlayerManagerC::CreateInstance()
{
	if (sInstance == nullptr)
	{
		sInstance = new PlayerManagerC();
	}

	return sInstance;
}

void PlayerManagerC::init()
{
	PlanetManagerC* planetManager = PlanetManagerC::GetInstance();
	uint32_t numPlanets = planetManager->getNumPlanets();

	PlanetC* planetPtr = nullptr;


	// Player One

	mPlayers.push_back(new PlayerC(0));
	mPlayers[0]->setColor(PLAYER_ONE_COLOR);
	
	planetPtr = planetManager->getPlanetPtr(0);
	planetPtr->setPlanetColor(PLAYER_ONE_COLOR);
	planetPtr->setShipCount(PLAYER_START_SHIPCOUNT);
	mPlayers[0]->setHighlightedPlanet(planetPtr);
	

	// Player Two

	mPlayers.push_back(new PlayerC(1));
	mPlayers[1]->setColor(PLAYER_TWO_COLOR);

	planetPtr = planetManager->getPlanetPtr(1);
	planetPtr->setPlanetColor(PLAYER_TWO_COLOR);
	planetPtr->setShipCount(PLAYER_START_SHIPCOUNT);
	mPlayers[1]->setHighlightedPlanet(planetPtr);
}

void PlayerManagerC::update(DWORD milliseconds)
{
	for (size_t i = 0; i < mPlayers.size(); i++)
	{
		if (i == 0)
		{
			if (InputManagerC::GetInstance()->getKeyEvent('A'))
				mPlayers[i]->setHighlightedPlanet(PlanetC::Neighbor::LEFT);
			else if (InputManagerC::GetInstance()->getKeyEvent('D'))
				mPlayers[i]->setHighlightedPlanet(PlanetC::Neighbor::RIGHT);
			else if (InputManagerC::GetInstance()->getKeyEvent('W'))
				mPlayers[i]->setHighlightedPlanet(PlanetC::Neighbor::UP);
			else if (InputManagerC::GetInstance()->getKeyEvent('S'))
				mPlayers[i]->setHighlightedPlanet(PlanetC::Neighbor::DOWN);

			if (InputManagerC::GetInstance()->getKeyEvent('Q'))
				mPlayers[i]->changePercentageSelection();

			if (InputManagerC::GetInstance()->getKeyEvent('E'))
				mPlayers[i]->selectPlanet();
		}

		if (i == 1)
		{
			if (InputManagerC::GetInstance()->getKeyEvent(VK_NUMPAD4))
				mPlayers[i]->setHighlightedPlanet(PlanetC::Neighbor::LEFT);
			else if (InputManagerC::GetInstance()->getKeyEvent(VK_NUMPAD6))
				mPlayers[i]->setHighlightedPlanet(PlanetC::Neighbor::RIGHT);
			else if (InputManagerC::GetInstance()->getKeyEvent(VK_NUMPAD8))
				mPlayers[i]->setHighlightedPlanet(PlanetC::Neighbor::UP);
			else if (InputManagerC::GetInstance()->getKeyEvent(VK_NUMPAD5))
				mPlayers[i]->setHighlightedPlanet(PlanetC::Neighbor::DOWN);

			if (InputManagerC::GetInstance()->getKeyEvent(VK_NUMPAD7))
				mPlayers[i]->changePercentageSelection();

			if (InputManagerC::GetInstance()->getKeyEvent(VK_NUMPAD9))
				mPlayers[i]->selectPlanet();
		}

		mPlayers[i]->update(milliseconds);
	}
}

void PlayerManagerC::render()
{
	for (size_t i = 0; i < mPlayers.size(); i++)
	{
		mPlayers[i]->render();
	}
}

void PlayerManagerC::shutdown()
{
	for (size_t i = 0; i < mPlayers.size(); i++)
	{
		mPlayers.at(i)->shutdown();
		delete(mPlayers.at(i));
	}
	mPlayers.clear();
}

PlayerC* PlayerManagerC::getPlayer(char playerID)
{
	return mPlayers.at(playerID);
}


int PlayerManagerC::getPlayerTravellingShips(char playerID)
{
	return getPlayer(playerID)->getNumberOfTravellingShips();
}

int32_t PlayerManagerC::getPlayerPercentageSelect(char playerID)
{
	return getPlayer(playerID)->GetPecentageSelection();
}
