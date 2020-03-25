#include "ANIMAL.h"
#include "GAME.h"
#include "PEOPLE.h"
#include "VEHICLE.h"
#include "console.h"
#include <thread>
#include <conio.h>
#include <time.h>
#include <tchar.h>

#pragma comment(lib,"winmm")


char MOVING;
bool IS_RUNNING;
bool run;
bool sound;
CGAME *cg;
int dem = 1, kt1, kt2;
int ran1[5];
int ran2[5];

void SubThread()
{
	MCIERROR err = mciSendString(_T("open music.mp3 alias mp3"), NULL, 0, 0);
	while (IS_RUNNING) 
	{
		if (run)
		{
			if (sound) mciSendString(_T("play mp3 repeat"), NULL, 0, 0);
			if (!cg->getPeople().isDead())
			{
				cg->updatePosPeople(MOVING);
			}
			MOVING = ' ';
			cg->updatePosVehicle(dem, kt1, kt2);
			cg->updatePosAnimal(dem);
			cg->drawGame();
			if (cg->getPeople().isImpact(cg->getVehicle(), cg->getSl()) ||
			cg->getPeople().isImpact(cg->getAnimal(), cg->getSl()))
			{
				cg->Dead();
				cg->pauseGame(run);
				Sleep(1000);
				system("cls");
				SetColor(12);
				GotoXY(50, 10);
				cout << "END GAME!";
				GotoXY(45, 11);
				cout << "1. Nhan 'y' de choi lai.";
				GotoXY(45, 12);
				cout << "2. Nhan phim khac de thoat.";
			}
			kt1 = 0; kt2 = 0;
			for (int i = 0; i < 5; i++)
			{
				if (dem >= ran1[i] && dem <= ran1[i] + 30) kt1 = 1;
				if (dem >= ran2[i] && dem <= ran2[i] + 30) kt2 = 1;
			}
			if (kt1 == 1 && run == true)
			{
				char ch = 219;
				SetColor(12);
				GotoXY(endX + 1, 14);
				cout << ch;
			}
			if (kt1 == 0 && run == true)
			{
				char ch = 219;
				SetColor(10);
				GotoXY(endX + 1, 13);
				cout << ch;
			}
			if (kt2 == 1 && run == true)
			{
				char ch = 219;
				SetColor(12);
				GotoXY(startX - 1, 8);
				cout << ch;
			}
			if (kt2 == 0 && run == true)
			{
				char ch = 219;
				SetColor(10);
				GotoXY(startX - 1, 7);
				cout << ch;
			}
			if (cg->getPeople().isFinish())
			{
				system("cls");
				GotoXY(50, 12);
				SetColor(10);
				cout << "COMPLETE. NEXT LEVEL!!!";
				Sleep(1000);
				if (cg->getSl() != maxLevel)
					cg->nextLevel();
				else cg->resetGame();
			}
			Sleep(30);
			dem++;
			if (dem == 501)
			{
				dem = 1;
				ran1[0] = rand() % (50);
				ran2[0] = rand() % (50);
				for (int i = 1; i < 5; i++)
				{
					ran1[i] = ran1[i - 1] + 60 + rand() % (50);
					ran2[i] = ran2[i - 1] + 60 + rand() % (50);
				}
			}
		}
		else if (sound) mciSendString(_T("stop mp3"), NULL, 0, 0);
	}
	mciSendString(_T("close mp3"), NULL, 0, 0);
}

void main()
{
	cg = new CGAME();
	IS_RUNNING = true;
	sound = true;
	run = true;
	int temp;
	FixConsoleWindow();
	HideControl();
	srand(time(NULL));
	ran1[0] = rand() % (50);
	ran2[0] = rand() % (50);
	for (int i = 1; i < 5; i++)
	{
		ran1[i] = ran1[i - 1] + 60 + rand() % (50);
		ran2[i] = ran2[i - 1] + 60 + rand() % (50);
	}
	cg->startGame(sound);
	thread t1(SubThread);
	while (1)
		{
			temp = toupper(_getch());
			if (!cg->getPeople().isDead())
			{
				if (temp == 27) 
				{
					cg->exitGame(&t1, IS_RUNNING);
					return;
				}
				else if (temp == 'P') 
				{
					cg->pauseGame(run);
				}
				else if (temp == 'T')
				{
					cg->pauseGame(run);
					cg->loadGame();
					cg->resumeGame(run);
				}
				else if (temp == 'L')
				{
					cg->pauseGame(run);
					cg->saveGame();
					int k = 0;
					string bottom[2] = { "Yes", "No" };
					int mau[2];
					mau[0] = 10; mau[1] = 15;
					system("cls");
					while (1)
					{
						GotoXY(50, 10);
						SetColor(11);
						cout << "Ban co muon tiep tuc?" << endl;
						for (int i = 1; i <= 2; i++)
						{
							GotoXY(50, 12 + i);
							SetColor(mau[i - 1]);
							cout << i << ". " << bottom[i - 1];
						}
						int z = _getch();
						TRANGTHAI trangthai = key(z);
						if (trangthai == UP || trangthai == DOWN) k = (k + 1) % 2;
						if (trangthai == ENTER)
						{
							if (k == 0) cg->resumeGame(run);
							else
							{
								cg->exitGame(&t1, IS_RUNNING);
								return;
							}
							break;
						}
						for (int i = 0; i < 2; i++) mau[i] = 15;
						mau[k] = 10;
					}
				}
				else 
				{
					cg->resumeGame(run);
					MOVING = temp; 
				}
			}
			else
			{
				if (temp == 'Y')
				{
					cg->resetGame();
					run = true;
				}
				else 
				{
					cg->exitGame(&t1, IS_RUNNING);
					return;
				}
			}
		}
}
