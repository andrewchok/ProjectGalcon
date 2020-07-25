#ifndef SHIP_H
#define SHIP_H
#include <stdlib.h>
#include <vector>
#include <windows.h>
#include <math.h>
#include "Object.h"
#include "baseTypes.h"
#include "Planet.h"


class ShipC : public ObjectC
{
public:
	ShipC(Coord2D destPos, Coord2D startPos, int32_t numOfShipsPerShip, uint32_t color);
	~ShipC() {};

	bool checkCollisions(Coord2D position, float_t radius);
	void update(DWORD milliseconds);


	void render();
	void flock(std::vector<ShipC*> shipList);

	Coord2D flockSeparation(std::vector<ShipC*> shipList);
	Coord2D flockCohesion(std::vector<ShipC*> shipList);
	Coord2D steerTo(Coord2D target);
	Coord2D flockAlignment(std::vector<ShipC*> shipList);
	
	// negative number for clockwise, positive number for counter-clockwise
	float_t rotateShip(Coord2D destination, Coord2D source)
	{
		return ((source.x * destination.y) - (source.y * destination.x));
	};

	float_t toRadians(float_t angle)
	{
		angle /= 360;
		angle *= 2 * PI;
		return angle;
	};

	float_t toDegrees(float_t angle)
	{
		angle *= 360;
		angle /= 2 * PI;
		return angle;
	};

	int32_t getShipCount() { return mShipCount; };

private:
	Coord2D mFrontVertex;
	Coord2D mBackLeftVertex;
	Coord2D mBackRightVertex;

	Coord2D mDestination;
	uint32_t mColor;

	float_t mOrientationAngle;
	float_t mCollisionRadius = 10;
	float_t mNeighbourRadius = 100;
	float_t mSeparationRadius = 20;
	float_t mMaxSpeed = 2;
	float_t mMaxForce = 0.05f;

	int32_t mShipCount;

	const float_t separationWeight = 1;
	const float_t cohesionWeight = 1;
	const float_t alignmentWeight = 1;
	const float_t destinationWeight = 10;
};


#endif // !SHIP_H