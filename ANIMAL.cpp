#include "ANIMAL.h"

void CBIRD::setX(int x)
{
	mX = x;
	if (mX < startX) mX = endX;
}

void CDINAUSOR::setX(int x)
{
	mX = x;
	if (mX > endX + 1) mX = startX + 1;
}

void CANIMAL::setY(int y)
{ 
	mY = y;
}

int CANIMAL::getX()
{
	return mX;
}

int CANIMAL::getY()
{
	return mY;
}

bool CDINAUSOR::Impact(int x, int y)
{
	if (mX == x && mY == y) return true;
	if (mX == x && mY + 1 == y) return true;
	if (mX - 1 == x && mY + 1 == y) return true;
	if (mX - 1 == x && mY + 2 == y) return true;
	if (mX - 2 == x && mY + 2 == y) return true;
	return false;
}

bool CBIRD::Impact(int x, int y)
{
	if (mX == x && mY == y) return true;
	if (mX - 1 == x && mY - 1 == y) return true;
	if (mX + 1 == x && mY - 1 == y) return true;
	return false;
}

