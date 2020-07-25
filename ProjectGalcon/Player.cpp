#include "Player.h"

#include "ShapeDraw.h"


/* Constants */
const float_t PlayerC::HIGHLIGHT_OFFSET = 5;


/* Methods */

PlayerC::PlayerC(const char8_t playerID) 
{
	mPlayerID = playerID;
	mPercentageSelection = 50;
}

int32_t PlayerC::getNumberOfTravellingShips()
{
	int32_t numOfShips = 0;
	

	// linker error
	for (int i = 0; i < mFleetList.GetSize(); i++)
	{
		numOfShips += mFleetList.Get(i)->getNumberOfShipsInFleet();
	}

	return numOfShips;
}

void PlayerC::sendFleet(int32_t numOfShips)
{
	mFleetList.Append(new FleetC(numOfShips, mHighlightedPlanet, mSelectedPlanet, mColor));
}

const char8_t PlayerC::getPlayerID()
{
	return mPlayerID;
}

void PlayerC::setColor(uint32_t xxRRGGBB)
{
	mColor = xxRRGGBB;
}

void PlayerC::setHighlightedPlanet(PlanetC* planet)
{
	mHighlightedPlanet = planet;
}

void PlayerC::setHighlightedPlanet(PlanetC::Neighbor neighbor)
{
	PlanetC* tmp = mHighlightedPlanet->getNeighbor(neighbor);
	if (tmp) mHighlightedPlanet = tmp;
}

void PlayerC::selectPlanet()
{
	if (!mSelectedPlanet && mHighlightedPlanet && mHighlightedPlanet->getPlanetColor() == mColor)
	{
		mSelectedPlanet = mHighlightedPlanet;
	}
	else if (mSelectedPlanet && mSelectedPlanet == mHighlightedPlanet)
	{
		mSelectedPlanet = nullptr;
	}
	else if (mSelectedPlanet && mHighlightedPlanet)
	{
		int32_t shipsToSend = (int32_t)(mSelectedPlanet->getShipCount() * (((float_t)mPercentageSelection)/100.0f));
		sendFleet(shipsToSend);
		mSelectedPlanet->setShipCount(mSelectedPlanet->getShipCount() - shipsToSend);
		mSelectedPlanet = nullptr;
	}
}

int32_t PlayerC::GetPecentageSelection()
{
	return mPercentageSelection;
}

void PlayerC::changePercentageSelection()
{
	mPercentageSelection += 25;
	if (mPercentageSelection > 100) mPercentageSelection = 25;
}

void PlayerC::update(DWORD milliseconds)
{
	if (mSelectedPlanet != nullptr)
	{
		if (mSelectedPlanet->getPlanetColor() != mColor) mSelectedPlanet = nullptr;
	}

	for (int i = 0; i < mFleetList.GetSize(); i++)
	{
		mFleetList.Get(i)->getNumberOfShipsInFleet();
		break;
	}

	for (int i = 0; i < mFleetList.GetSize(); i++)
	{
		mFleetList.Get(i)->update(milliseconds);
	}
}

void PlayerC::render()
{
	if (mHighlightedPlanet)
	{
		const float_t highlightRadius = mHighlightedPlanet->getRadius();
		const Coord2D highlightPos = mHighlightedPlanet->getPosition();

		const char8_t red = static_cast<char8_t>((mColor >> 16) & 0xFF);
		const char8_t green = static_cast<char8_t>((mColor >> 8) & 0xFF);
		const char8_t blue = static_cast<char8_t>((mColor >> 0) & 0xFF);

		if (mSelectedPlanet && mSelectedPlanet != mHighlightedPlanet)
		{
			const float_t selectRadius = mSelectedPlanet->getRadius();
			const Coord2D selectPos = mSelectedPlanet->getPosition();

			DrawLine(selectPos.x, selectPos.y, highlightPos.x, highlightPos.y, red, green, blue, 2.0f);
			DrawCircle(selectRadius + HIGHLIGHT_OFFSET, selectPos.x, selectPos.y, red, green, blue, false, 4.0f);
		}
		
		DrawCircle(highlightRadius + HIGHLIGHT_OFFSET, highlightPos.x, highlightPos.y, red, green, blue, false, 4.0f);
	}

	for (int i = 0; i < mFleetList.GetSize(); i++)
	{
		mFleetList.Get(i)->render();
	}
}

void PlayerC::shutdown()
{

	for (int i = mFleetList.GetSize()-1; i >= 0; i--)
	{
		mFleetList.Get(i)->shutdown();
		delete(mFleetList.Get(i));
		mFleetList.Remove(mFleetList.Get(i));
	} 
}
