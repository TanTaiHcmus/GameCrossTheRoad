#pragma once
#include "ANIMAL.h"
#include "PEOPLE.h"
#include "VEHICLE.h"
#include "console.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>
#include <thread>
#include <stdio.h>

const int maxLevel = 10;

enum TRANGTHAI { UP, DOWN, LEFT, RIGHT, ENTER, BACK, Null };

using namespace std;

TRANGTHAI key(int z);

void loading();

void Draw();

class CGAME{
private:
	CTRUCK axt[maxLevel];
	CCAR axh[maxLevel];
	CDINAUSOR akl[maxLevel];
	CBIRD ac[maxLevel];
	CPEOPLE cn;
	int sl;
public:
	void drawGame();  
	void Dead();
	CPEOPLE getPeople();
	CVEHICLE** getVehicle();
	CANIMAL** getAnimal(); 
	int getSl();
	void resetGame();
	void nextLevel();
	void exitGame(thread*, bool&);
	void startGame(bool&);
	void loadGame(); 
	void saveGame(); 
	void pauseGame(bool&);
	void resumeGame(bool&);
	bool setting();
	void updatePosPeople(char); 
	void updatePosVehicle(int, int, int); 
	void updatePosAnimal(int);
};
