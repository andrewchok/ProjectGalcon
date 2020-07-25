#include "Fleet.h"

FleetC::FleetC(int32_t numOfShips, PlanetC* destination, PlanetC* source, uint32_t color)
{
	// if we want to scale the ships on screen to represent more than just one ship
	const int32_t capOfShipsToSpawn = 100;
	const int32_t numOfShipsPerShip = 1 + (int32_t)(numOfShips/capOfShipsToSpawn);

	mNumOfShips = numOfShips;
	mDestination = destination;
	mSource = source;
	mColor = color;

	for (int i = 0; i < (mNumOfShips / numOfShipsPerShip); i++)
	{
		mShipList.push_back(new ShipC(destination->getPosition(), source->getPosition(), numOfShipsPerShip, mColor));
	}

	// any remainder is added
	if (mNumOfShips % numOfShipsPerShip > 0)
	{
		mShipList.push_back(new ShipC(destination->getPosition(), source->getPosition(), mNumOfShips % numOfShipsPerShip, mColor));
	}
}



void FleetC::update(DWORD milliseconds)
{
	// deletes one ship each update that is colliding
	for (size_t i = 0; i < mShipList.size(); i++)
	{
		if (mShipList.at(i)->checkCollisions(mDestination->getPosition(), mDestination->getRadius()))
		{
			if (mDestination->getPlanetColor() == mColor)
			{
				mDestination->setShipCount(mDestination->getShipCount() + mShipList.at(i)->getShipCount());
			}
			else
			{
				for (int j = 0; j < mShipList.at(i)->getShipCount(); j++)
				{
					if (mDestination->getPlanetColor() == mColor)
					{
						mDestination->setShipCount(mDestination->getShipCount() + mShipList.at(i)->getShipCount());
					}
					else if (mDestination->getShipCount() < 0)
					{
						mDestination->setPlanetColor(mColor);
						mDestination->setShipCount(1);
					}
					else mDestination->setShipCount(mDestination->getShipCount() - 1 );
				}
			}

			mNumOfShips -= mShipList.at(i)->getShipCount();
			delete(mShipList.at(i));
			mShipList.erase(mShipList.begin() + i);
			break;
		}
	}

	flockFleet();
	for (size_t i = 0; i < mShipList.size(); i++)
	{
		mShipList.at(i)->update(milliseconds);
	}
}

void FleetC::render()
{
	for (size_t i = 0; i < mShipList.size(); i++)
	{
		mShipList.at(i)->render();
	}
}

void FleetC::shutdown()
{
	for (int i = mShipList.size()-1; i >= 0; i--)
	{
		delete(mShipList.at(i));
		mShipList.erase(mShipList.begin() + i);
	}
	mShipList.clear();
}

int32_t FleetC::getNumberOfShipsInFleet()
{
	return mNumOfShips;
}

void FleetC::flockFleet()
{
	for (size_t i = 0; i < mShipList.size(); i++)
	{
		mShipList.at(i)->flock(mShipList);
	}
}
