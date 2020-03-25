#pragma once
#include "console.h"
#include <iostream>

using namespace std;

class CVEHICLE
{
protected:
	int mX, mY;
public:
	void setX(int x);
	void setY(int y);
	virtual bool Impact(int, int) = 0;
	int getX();
	int getY();
};

class CTRUCK : public CVEHICLE{
public:
	bool Impact(int, int);
};

class CCAR : public CVEHICLE{
public:
	bool Impact(int, int);
};