#pragma once
#include "console.h"


class CANIMAL
{
protected:
	int mX, mY;
public:
	void virtual setX(int x) = 0;
	void setY(int y);
	virtual bool Impact(int, int) = 0;
	int getX();
	int getY();
};

class CDINAUSOR : public CANIMAL{
public:
	bool Impact(int, int);
	void setX(int x);
};

class CBIRD : public CANIMAL{
public:
	bool Impact(int, int);
	void setX(int x);
};