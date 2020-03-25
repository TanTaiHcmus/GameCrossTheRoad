#include "VEHICLE.h"

void CVEHICLE::setX(int x)
{
	mX = x;
	if (mX > endX) mX = startX;
	if (mX < startX) mX = endX;
}

void CVEHICLE::setY(int y)
{
	mY = y;
}

int CVEHICLE::getX()
{
	return mX;
}

int CVEHICLE::getY()
{
	return mY;
}

bool CTRUCK::Impact(int x, int y)
{
	if (mX == x && mY == y) return true;
	if (mX - 1 == x && mY + 1 == y) return true;
	if (mX == x && mY + 1 == y) return true;
	if (mX + 1 == x && mY + 1 == y) return true;
	return false;
}

bool CCAR::Impact(int x, int y)
{
	if (mX == x && mY == y) return true;
	if (mX - 1 == x && mY + 1 == y) return true;
	if (mX == x && mY + 1 == y) return true;
	return false;
}

