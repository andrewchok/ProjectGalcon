#ifndef OBJECT_H
#define OBJECT_H

#include "CollInfo.h"

#include "baseTypes.h"

class ObjectC
{
public:
    ObjectC(float initPosX, float initPosY, float initVelX, float initVelY);
    ObjectC();
    ~ObjectC();
    void setPosition(const Coord2D& posToSet) noexcept { mPosition.x = posToSet.x; mPosition.y = posToSet.y; }
    Coord2D getPosition() const noexcept {return mPosition;}
    void setVelocity(const Coord2D& velToSet) noexcept { mVelocity.x = velToSet.x; mVelocity.y = velToSet.y; }
    void setVelocity(float x, float y) noexcept { mVelocity.x = x; mVelocity.y = y; }
    Coord2D *getVelocity() noexcept {return &mVelocity;};
    void setCollInfo(const CollInfoC& collInfoToSet) noexcept { mCollInfo = collInfoToSet; }
    CollInfoC *getCollInfo() noexcept { return &mCollInfo; }
	int32_t getID() noexcept {return mID;}
	void setID(int32_t id) noexcept { mID = id; }
	virtual void render()=0;

protected:
    Coord2D mPosition;
    Coord2D mVelocity;
    CollInfoC mCollInfo;
	int32_t mID;
};

#endif // !OBJECT_H