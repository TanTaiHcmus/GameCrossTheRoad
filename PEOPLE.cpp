#include "PEOPLE.h"


void CPEOPLE::setState(bool x)
{
	mState = x;
}

void CPEOPLE::Up()
{
	if (mY > startY) mY--;
}

void CPEOPLE::Down()
{
	if (mY < endY) mY++;
}

void CPEOPLE::Left()
{
	if (mX > startX - 1) mX--;
	else mX = endX + 1;
}

void CPEOPLE::Right()
{
	if (mX < endX + 1) mX++;
	else mX = startX - 1;
}

bool CPEOPLE::isImpact(CVEHICLE **p, int sl)
{
	for (int i = 0; i < 2 * sl; i++)
	{
		if (p[i]->Impact(mX, mY))
		{
			GotoXY(mX, mY);
			SetColor(12);
			cout << "X";
			Beep(689, 500);
			Beep(689, 500);
			return true;
		}
	}
	return false;
}

bool CPEOPLE::isImpact(CANIMAL **p, int sl)
{
	for (int i = 0; i < 2 * sl; i++)
	{
		if (p[i]->Impact(mX, mY))
		{
			GotoXY(mX, mY);
			SetColor(12);
			cout << "X";
			Beep(689, 500);
			Beep(689, 500);
			return true;
		}
	}
	return false;
}

bool CPEOPLE::isFinish()
{
	return (mY == startY);
}

bool CPEOPLE::isDead()
{
	return (mState == false);
}

int CPEOPLE::getX()
{
	return mX;
}

int CPEOPLE::getY()
{
	return mY;
}

void CPEOPLE::setX(int x)
{
	mX = x;
}

void CPEOPLE::setY(int y)
{
	mY = y;
}