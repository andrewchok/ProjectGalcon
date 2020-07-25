#pragma once

#include "Object.h"

#include <windows.h>				// Header File For Windows

#include "baseTypes.h"

class PlanetC : public ObjectC
{
public:
	/* Constants */

	static const float_t BORDER_OFFSET;
	static const float_t MIN_RADIUS;
	static const float_t MAX_RADIUS;
	static const uint32_t PLANET_DEFAULT_COLOR;

	static const float_t PRODUCTION_MIN;
	static const float_t PRODUCTION_MAX;
	static const float_t MIN_DEFAULT_SHIPS;
	static const float_t MAX_DEFAULT_SHIPS;


	/* Structures */

	enum class Neighbor
	{
		INVAL_DIRECTION = -1,

		LEFT,
		RIGHT,
		UP,
		DOWN,

		MAX_DIRECTION
	};


public:
    PlanetC();
	PlanetC(float_t initPosX, float_t initPosY,int id, uint32_t color=PLANET_DEFAULT_COLOR);
    ~PlanetC();

	void initRandom();

	void update(DWORD milliseconds);
    void render() override;
    void disable() noexcept {mEnabled = false;}
    void enable() noexcept {mEnabled = true;}


    uint32_t getPlanetColor() noexcept {return mPlanetColor;}
	void setPlanetColor(uint32_t color) noexcept {mPlanetColor = color;}
	void setRandomColor();
	
	float_t getRadius() noexcept { return mRadius; }
	void setRadius(float radius) noexcept;
	
	PlanetC* getNeighbor(Neighbor direction) noexcept;
	void setNeighbors(PlanetC* left, PlanetC* right, PlanetC* up, PlanetC* down);

	float_t getShipCount() noexcept { return mShipCount; }
	void setShipCount(float_t shipCount) noexcept { mShipCount = shipCount; }

private:
	int32_t mPlanetColor;
    bool8_t mEnabled;
    float_t mRadius;

	struct
	{
		PlanetC* left = nullptr;
		PlanetC* right = nullptr;
		PlanetC* up = nullptr;
		PlanetC* down = nullptr;
	} mNeighbors;

	float_t mProductionRate = 0;
	float_t mShipCount = 0;
};

