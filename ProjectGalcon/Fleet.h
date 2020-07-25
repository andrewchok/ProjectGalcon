#ifndef FLEET_H
#define FLEET_H
#include <stdlib.h>
#include <vector>
#include <windows.h>
#include "baseTypes.h"
#include "Ship.h"
#include "Planet.h"
#include "PlanetManager.h"

class FleetC
{
public:
	FleetC()
	{
		mNumOfShips = 0;
		mDestination = nullptr;
		mSource = nullptr;
	};
	FleetC(int32_t numOfShips, PlanetC* destination, PlanetC* source, uint32_t color);
	~FleetC() {};

	void update(DWORD milliseconds);

	void render();

	void shutdown();

	int32_t getNumberOfShipsInFleet();

	void flockFleet();
	

private:
	// list of Ships
	std::vector<ShipC*> mShipList;

	// actual number of ships, each ship even though rendered to the screen as one could hold multiple ships
	int32_t mNumOfShips;

	// destination
	PlanetC* mDestination;

	// start position
	PlanetC* mSource;

	uint32_t mColor;
};


#endif // !FLEET_H
