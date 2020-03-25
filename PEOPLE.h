#pragma once
#include "ANIMAL.h"
#include "VEHICLE.h"
#include "console.h"
#include <iostream>

using namespace std;

class CPEOPLE
{
private:
	int mX, mY;
	bool mState; 
public:
	void setState(bool x);
	int getX();
	int getY();
	void setX(int);
	void setY(int);
	void Up();
	void Left();
	void Right();
	void Down();
	bool isImpact(CVEHICLE**, int sl);
	bool isImpact(CANIMAL**, int sl);
	bool isFinish();
	bool isDead();
};

