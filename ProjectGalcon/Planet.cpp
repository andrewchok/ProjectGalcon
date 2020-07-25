#include "Planet.h"

#include <Windows.h>

#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library

#include <string>

#include "game.h"
#include "StateManager.h"
#include "ShapeDraw.h"
#include "random.h"


/* Constants */

const float_t PlanetC::BORDER_OFFSET = 120;
const float_t PlanetC::MIN_RADIUS = 15;
const float_t PlanetC::MAX_RADIUS = 70;
const uint32_t PlanetC::PLANET_DEFAULT_COLOR = 0x00505050;

const float_t PlanetC::PRODUCTION_MIN = 0.2f;
const float_t PlanetC::PRODUCTION_MAX = 1.5f;
const float_t PlanetC::MIN_DEFAULT_SHIPS = 1;
const float_t PlanetC::MAX_DEFAULT_SHIPS = 50;


/* Methods */

PlanetC::PlanetC()
{
	// init color is white
	mPlanetColor = PLANET_DEFAULT_COLOR;

	mPosition = { 0, 0 };

	// init radius is 10
	mRadius = 10;

	mEnabled = true;
	mCollInfo.shape = CollInfoC::SHAPE_CIRCLE;
}

PlanetC::PlanetC(float_t initPosX, float_t initPosY, int id, uint32_t color)
{
	mPosition.x = initPosX;
	mPosition.y = initPosY;

	// init color is white
	mPlanetColor = color;

	// is enabled
	mEnabled = true;

	// init radius is 50
	mRadius = 10;
}
;
PlanetC::~PlanetC()
{
}
void PlanetC::initRandom()
{
	const float_t maxX = CGame::SCREEN_WIDTH - BORDER_OFFSET;
	const float_t maxY = CGame::SCREEN_HEIGHT - BORDER_OFFSET;

	mPosition = { getRangedRandom(BORDER_OFFSET, maxX), getRangedRandom(BORDER_OFFSET, maxY) };
	mRadius = getRangedRandom(MIN_RADIUS, MAX_RADIUS);
	mProductionRate = (((mRadius - MIN_RADIUS) / (MAX_RADIUS - MIN_RADIUS)) * PRODUCTION_MAX) + PRODUCTION_MIN;

	const float_t random = getRangedRandom(0.0f, 1.0f);
	if (random < 0.3)
		mShipCount = getRangedRandom(MIN_DEFAULT_SHIPS, MAX_DEFAULT_SHIPS);
	else if (random < 0.6)
		mShipCount = getRangedRandom(MIN_DEFAULT_SHIPS, MAX_DEFAULT_SHIPS / 2);
	else
		mShipCount = getRangedRandom(MIN_DEFAULT_SHIPS, MAX_DEFAULT_SHIPS / 4);
}


void PlanetC::update(DWORD milliseconds)
{
	if (mPlanetColor != PLANET_DEFAULT_COLOR)
	{
		mShipCount += mProductionRate * (milliseconds / 1000.0f);
	}
}

void PlanetC::render()
{
	const uchar8_t red = static_cast<char8_t>((mPlanetColor >> 16) & 0xFF);
	const uchar8_t green = static_cast<char8_t>((mPlanetColor >> 8) & 0xFF);
	const uchar8_t blue = static_cast<char8_t>((mPlanetColor >> 0) & 0xFF);

	DrawCircle(mRadius, mPosition.x, mPosition.y, red, green, blue, 1);
	DrawString(std::to_string(static_cast<int>(mShipCount)), mPosition.x, mPosition.y, 0x00FFFFFF);

	if (StateManagerC::GetInstance()->getMode() != StateManagerC::Mode::DEBUG) return;

	if (mNeighbors.left)
	{
		constexpr uchar8_t maxColor = 255;
		const Coord2D neighborPos = mNeighbors.left->getPosition();
		DrawLine(mPosition.x, mPosition.y, neighborPos.x, neighborPos.y, maxColor, maxColor, maxColor);
	}
	
	if (mNeighbors.right)
	{
		constexpr uchar8_t maxColor = 255;
		const Coord2D neighborPos = mNeighbors.right->getPosition();
		DrawLine(mPosition.x, mPosition.y, neighborPos.x, neighborPos.y, maxColor, maxColor, maxColor);
	}
	
	if (mNeighbors.up)
	{
		constexpr uchar8_t maxColor = 255;
		const Coord2D neighborPos = mNeighbors.up->getPosition();
		DrawLine(mPosition.x, mPosition.y, neighborPos.x, neighborPos.y, maxColor, maxColor, maxColor);
	}
	
	if (mNeighbors.down)
	{
		constexpr uchar8_t maxColor = 255;
		const Coord2D neighborPos = mNeighbors.down->getPosition();
		DrawLine(mPosition.x, mPosition.y, neighborPos.x, neighborPos.y, maxColor, maxColor, maxColor);
	}
}

void PlanetC::setRandomColor()
{
	mPlanetColor = getRangedRandom(0, 256); // Blue
	mPlanetColor += getRangedRandom(0, 256) << 8; // Green
	mPlanetColor += getRangedRandom(0, 256) << 16; // Red
}

void PlanetC::setRadius(float radius) noexcept
{
	mRadius = radius;
	mProductionRate = (((mRadius - MIN_RADIUS) / (MAX_RADIUS - MIN_RADIUS)) * PRODUCTION_MAX) + PRODUCTION_MIN;
}

PlanetC* PlanetC::getNeighbor(Neighbor direction) noexcept
{
	PlanetC* neighbor = nullptr;

	switch (direction)
	{
	case Neighbor::LEFT:
		neighbor = mNeighbors.left;
		break;
	case Neighbor::RIGHT:
		neighbor = mNeighbors.right;
		break;
	case Neighbor::UP:
		neighbor = mNeighbors.up;
		break;
	case Neighbor::DOWN:
		neighbor = mNeighbors.down;
		break;

	default:
		break;
	}

	return neighbor;
}

void PlanetC::setNeighbors(PlanetC* left, PlanetC* right, PlanetC* up, PlanetC* down)
{
	mNeighbors.left = left;
	mNeighbors.right = right;
	mNeighbors.up = up;
	mNeighbors.down = down;
}

