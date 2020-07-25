#ifndef PLAYER_H
#define PLAYER_H
#include <stdlib.h>
#include <vector>
#include "baseTypes.h"
#include "LinkedList.h"
#include "Fleet.h"
#include "Planet.h"

class PlayerC
{
public:
	static const float_t HIGHLIGHT_OFFSET;


public:
	PlayerC(const char8_t playerID);
	~PlayerC() {};

	void update(DWORD milliseconds);
	void render();

	void shutdown();
	
	const char8_t getPlayerID();
	void setColor(uint32_t xxRRGGBB);

	// get, set current/selectedPlanets
	void setHighlightedPlanet(PlanetC* planet);
	void setHighlightedPlanet(PlanetC::Neighbor neighbor);
	void selectPlanet();

	int32_t GetPecentageSelection();

	void changePercentageSelection();

	// get number of ships that are enroute
	int32_t getNumberOfTravellingShips();

	void sendFleet(int32_t numOfShips);
private:
	char8_t mPlayerID;
	uint32_t mColor = 0x00FFFFFF;

	PlanetC* mHighlightedPlanet = nullptr;
	PlanetC* mSelectedPlanet = nullptr;

	// array of fleets
	LinkedListC<FleetC*> mFleetList;

	// value [0..100]
	int32_t mPercentageSelection;

	//std::vector<PlanetC*> mOwnedPlanetList;
};

#endif // !PLAYER_H
