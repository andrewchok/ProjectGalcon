#pragma once

#include <vector>

#include "baseTypes.h"
#include "Planet.h"

class PlanetManagerC
{
public:
	static PlanetManagerC* GetInstance();
	~PlanetManagerC() {};

public:
	/* Constants (defined in source file) */
	static const int32_t NUM_PLANETS;
	static const float_t INTER_PLANET_OFFSET;
	static const float_t HOME_PLANET_RADIUS;

public:
	void init();
	void updatePlanets(DWORD milliseconds);
	void renderPlanets();
	void deletePlanets();
	
	uint32_t getNumPlanets() noexcept { return NUM_PLANETS; }
	uint32_t getNumPlanets(uchar8_t playerID);
	
	std::vector<PlanetC*> getPlanets();
	std::vector<PlanetC*> getPlanets(uchar8_t playerID);
	PlanetC* getPlanetPtr(int32_t index);

private:
	static PlanetManagerC* sInstance;
	std::vector<PlanetC*> mPlanetPtrs;

private:
	PlanetManagerC() {};
	
	void initPlanetNeighbors();
};

