#define PLANET_MANAGER_CPP


/* Includes */

#include "PlanetManager.h"

#include <stdio.h>	// Header File For Standard Input / Output
#include <stdarg.h>	// Header File For Variable Argument Routines
#include <math.h>	// Header File For Math Operations

#include <gl\gl.h>	// Header File For The OpenGL32 Library
#include <gl\glu.h>	// Header File For The GLu32 Library

#include "random.h"
#include "game.h"
#include "PlayerManager.h"


/* Constants */

const int32_t PlanetManagerC::NUM_PLANETS = 30;
const float_t PlanetManagerC::INTER_PLANET_OFFSET = 20;
const float_t PlanetManagerC::HOME_PLANET_RADIUS = PlanetC::MAX_RADIUS / 2;


PlanetManagerC* PlanetManagerC::sInstance = nullptr;


/* Methods */

PlanetManagerC* PlanetManagerC::GetInstance()
{
	if (sInstance == nullptr)
	{
		sInstance = new PlanetManagerC();
	}

	return sInstance;
}

void PlanetManagerC::init()
{
	printf("Hey initing the planet manager!\n");
	mPlanetPtrs.reserve(NUM_PLANETS);

	for (uint32_t i = 0; i < NUM_PLANETS; i++)
	{
		PlanetC* newPlanet = nullptr;

		while (newPlanet == nullptr)
		{
			PlanetC* testPlanet = new PlanetC();
			testPlanet->initRandom();

			const Coord2D testCoord = testPlanet->getPosition();

			if (i < PlayerManagerC::NUM_PLAYERS) testPlanet->setRadius(HOME_PLANET_RADIUS);

			const float_t testRadius = testPlanet->getRadius();

			bool noCollisions = true;
			for (uint32_t prevIndex = 0; prevIndex < i; prevIndex++)
			{
				const Coord2D planetPos = mPlanetPtrs.at(prevIndex)->getPosition();
				const float_t planetRadius = mPlanetPtrs.at(prevIndex)->getRadius() + INTER_PLANET_OFFSET;

				if ((testCoord.x + testRadius >= planetPos.x - planetRadius)
					&& (testCoord.x - testRadius <= planetPos.x + planetRadius)
					&& (testCoord.y + testRadius >= planetPos.y - planetRadius)
					&& (testCoord.y - testRadius <= planetPos.y + planetRadius))
				{
					noCollisions = false;
					break;
				}
			}

			if (noCollisions)
			{
				newPlanet = testPlanet;
			}
			else
			{
				delete testPlanet;
			}
		}

		mPlanetPtrs.push_back(newPlanet);
	}

	initPlanetNeighbors();
}


void PlanetManagerC::deletePlanets()
{
	for (uint32_t i = 0; i < NUM_PLANETS; i++)
	{
		delete mPlanetPtrs.at(i);
	}
	mPlanetPtrs.clear();
}
void PlanetManagerC::updatePlanets(DWORD milliseconds)
{
	for (uint32_t i = 0; i < NUM_PLANETS; i++)
	{
		mPlanetPtrs.at(i)->update(milliseconds);
	}
}

void PlanetManagerC::renderPlanets()
{
	for (uint32_t i = 0; i < NUM_PLANETS; i++)
	{
		mPlanetPtrs.at(i)->render();
	}
}

uint32_t PlanetManagerC::getNumPlanets(uchar8_t playerID)
{
	uint32_t count = 0;


	uint32_t color = 0;

	if (playerID == 0)
		color = PlayerManagerC::PLAYER_ONE_COLOR;
	else if (playerID == 1)
		color = PlayerManagerC::PLAYER_TWO_COLOR;

	for (size_t i = 0; i < mPlanetPtrs.size(); i++)
	{
		if (mPlanetPtrs.at(i)->getPlanetColor() == color)
		{
			count++;
		}
	}

	return count;
}

std::vector<PlanetC*> PlanetManagerC::getPlanets()
{
	return mPlanetPtrs;
}

std::vector<PlanetC*> PlanetManagerC::getPlanets(uchar8_t playerID)
{
	std::vector<PlanetC*> planets;

	uint32_t color = 0;

	if (playerID == 0)
		color = PlayerManagerC::PLAYER_ONE_COLOR;
	else if (playerID == 1)
		color = PlayerManagerC::PLAYER_TWO_COLOR;

	for (size_t i = 0; i < mPlanetPtrs.size(); i++)
	{
		if (mPlanetPtrs.at(i)->getPlanetColor() == color)
		{
			planets.push_back(mPlanetPtrs.at(i));
		}
	}

	return planets;
}

PlanetC* PlanetManagerC::getPlanetPtr(int32_t index)
{
	return mPlanetPtrs.at(index);
}

void PlanetManagerC::initPlanetNeighbors()
{
	for (uint32_t i = 0; i < NUM_PLANETS; i++)
	{
		PlanetC* leftNeighbor = nullptr;
		PlanetC* rightNeighbor = nullptr;
		PlanetC* upNeighbor = nullptr;
		PlanetC* downNeighbor = nullptr;

		for (uint32_t j = 0; j < NUM_PLANETS; j++)
		{
			// Guards against setting planet as it's own neighbor
			if (i == j) continue;

			const Coord2D curPos = mPlanetPtrs.at(i)->getPosition();
			const Coord2D testPos = mPlanetPtrs.at(j)->getPosition();
			const Coord2D testDist = curPos - testPos;
			const Coord2D testDirUnit = testDist / testDist.magnitude();

			Coord2D dirUnit = { 0, 0 };
			float_t angle = 0;

			// LEFT NEIGHBOR CHECK

			dirUnit = { 1, 0 };
			angle = acosf(testDirUnit.dot(dirUnit));

			if (leftNeighbor != nullptr)
			{
				const Coord2D curLeftPos = leftNeighbor->getPosition();
				const Coord2D curDist = curPos - curLeftPos;

				if (angle < (PI / 4.0f) && curDist.magnitude() > testDist.magnitude())
				{ 
					leftNeighbor = mPlanetPtrs.at(j);
				}
			}
			else if (angle < (PI / 4.0f))
			{
				leftNeighbor = mPlanetPtrs.at(j);
			}

			
			// RIGHT NEIGHBOR CHECK

			dirUnit = { -1, 0 };
			angle = acosf(testDirUnit.dot(dirUnit));

			if (rightNeighbor != nullptr)
			{
				const Coord2D curRightPos = rightNeighbor->getPosition();
				const Coord2D curDist = curPos - curRightPos;

				if (angle < (PI / 4.0f) && curDist.magnitude() > testDist.magnitude())
				{
					rightNeighbor = mPlanetPtrs.at(j);
				}
			}
			else if (angle < (PI / 4.0f))
			{
				rightNeighbor = mPlanetPtrs.at(j);
			}


			// UP NEIGHBOR CHECK

			dirUnit = { 0, -1 };
			angle = acosf(testDirUnit.dot(dirUnit));
	
			if (upNeighbor != nullptr)
			{
				const Coord2D curUpPos = upNeighbor->getPosition();
				const Coord2D curDist = curPos - curUpPos;

				if (angle < (PI / 4.0f) && curDist.magnitude() > testDist.magnitude())
				{
					upNeighbor = mPlanetPtrs.at(j);
				}
			}
			else if (angle <= (PI / 4.0f))
			{
				upNeighbor = mPlanetPtrs.at(j);
			}


			// DOWN NEIGHBOR CHECK

			dirUnit = { 0, 1 };
			angle = acosf(testDirUnit.dot(dirUnit));

			if (downNeighbor != nullptr)
			{
				const Coord2D curDownPos = downNeighbor->getPosition();
				const Coord2D curDist = curPos - curDownPos;

				if (angle < (PI / 4.0f) && curDist.magnitude() > testDist.magnitude())
				{
					downNeighbor = mPlanetPtrs.at(j);
				}
			}
			else if (angle <= (PI / 4.0f))
			{
				downNeighbor = mPlanetPtrs.at(j);
			}
		}

		mPlanetPtrs.at(i)->setNeighbors(leftNeighbor, rightNeighbor, upNeighbor, downNeighbor);
	}
}

