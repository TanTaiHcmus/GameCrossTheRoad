#include "GAME.h"

TRANGTHAI key(int z)
{
	if (z == 224) {
		char c = _getch();
		if (c == 72) return UP;
		if (c == 80) return DOWN;
		if (c == 75) return LEFT;
		if (c == 77) return RIGHT;
	}
	else if (z == 13) return ENTER;
	else if (z == 8) return BACK;

	return Null;
}

void loading()
{
	system("cls");
	GotoXY(50, endY - 3);
	SetColor(11);
	cout << "LOADING";
	SetColor(15);
	for (int i = startX - 1; i <= endX + 1; i++)
	{
		GotoXY(i, endY);
		Sleep(20);
		cout << "|";
	}
	Sleep(100);
}

void Draw()
{
	SetColor(10);
	for (int i = startX - 2; i <= endX + 2; i++)
	{
		GotoXY(i, startY - 1);
		cout << "_";
		GotoXY(i, endY);
		cout << "_";
	}
	for (int i = startY; i <= endY; i++)
	{
		GotoXY(startX - 2, i);
		cout << "|";
		GotoXY(endX + 2, i);
		cout << "|";
	}
}

void CGAME::drawGame()
{
	system("cls");
	Draw();
	SetColor(15);
	GotoXY(40, 26);
	cout << "Nhan phim 'W', 'A', 'S', 'D' de di chuyen";
	GotoXY(40, 27);
	cout << "Nhan phim 'P' de tam dung tro choi";
	GotoXY(40, 28);
	cout << "Nhan phim 'T' de load game hoac 'L' de save game";
	SetColor(12);
	GotoXY(60, 0);
	cout << "LEVEL " << sl - 5;
	GotoXY(cn.getX(), cn.getY());
	SetColor(10);
	cout << "Y";
	char kt = 219;
	char kt1 = 220;
	for (int i = 0; i < sl; i++)
	{
		SetColor(14);
		int x = axt[i].getX();
		int y = axt[i].getY();
		GotoXY(x, y);
		cout << kt;
		GotoXY(x + 1, y + 1);
		cout << kt;
		GotoXY(x - 1, y + 1);
		cout << kt;
		GotoXY(x, y + 1);
		cout << kt;
		SetColor(11);
		x = axh[i].getX();
		y = axh[i].getY();
		GotoXY(x, y);
		cout << kt;
		GotoXY(x - 1, y + 1);
		cout << kt;
		GotoXY(x, y + 1);
		cout << kt;
		SetColor(13);
		x = akl[i].getX();
		y = akl[i].getY();
		GotoXY(x, y);
		cout << kt;
		GotoXY(x - 1, y + 1);
		cout << kt;
		GotoXY(x, y + 1);
		cout << kt;
		GotoXY(x - 1, y + 2);
		cout << kt;
		GotoXY(x - 2, y + 2);
		cout << kt;
		SetColor(9);
		x = ac[i].getX();
		y = ac[i].getY();
		GotoXY(x, y);
		cout << kt;
		GotoXY(x - 1, y - 1);
		cout << kt1;
		GotoXY(x + 1, y - 1);
		cout << kt1;
	}
}

CPEOPLE CGAME::getPeople()
{
	return cn;
}

CVEHICLE** CGAME::getVehicle()
{
	CVEHICLE **p = new CVEHICLE*[2 * sl];
	for (int i = 0; i < sl; i++)
	{
		p[i] = &axt[i];
		p[sl + i] = &axh[i];
	}
	return p;
}

CANIMAL** CGAME::getAnimal()
{
	CANIMAL **p = new CANIMAL*[2 * sl];
	for (int i = 0; i < sl; i++)
	{
		p[i] = &akl[i];
		p[sl + i] = &ac[i];
	}
	return p;
}

int CGAME::getSl()
{
	return sl;
}

void CGAME::resetGame()
{
	sl = 6;
	for (int i = 1; i <= sl; i++)
	{
		axt[i - 1].setX(10 * i);
		axt[i - 1].setY(16);
		axh[i - 1].setX(endX - 10 * (i - 1));
		axh[i - 1].setY(10);
		akl[i - 1].setX(10 * i); 
		akl[i - 1].setY(3);
		ac[i - 1].setX(endX - 10 * (i - 1));
		ac[i - 1].setY(22);
	}
	cn.setX(45); cn.setY(24);
	cn.setState(true);
	loading();
}

void CGAME::exitGame(thread *t, bool &IS_RUNNING)
{
	system("cls");
	IS_RUNNING = false;
	t->join();
}

void CGAME::startGame(bool &sound)
{
	string menu[3] = { "New game", "Load game", "Settings" };
	int mau[3];
	mau[0] = 10;
	for (int i = 1; i < 3; i++) mau[i] = 15;
	int k = 1;
	while (1)
	{
		system("cls");
		GotoXY(50, 10);
		SetColor(11);
		cout << "CROSS THE ROAD" << endl;
		for (int i = 1; i <= 3; i++) 
		{
			GotoXY(50, 13 + i);
			SetColor(mau[i - 1]);
			cout << i << ". " << menu[i - 1];
		}
		int z = _getch();
		TRANGTHAI trangthai = key(z);
		switch (trangthai)
		{
		case UP: 
			if (k == 1) k = 3;
			else --k;
			break;
		case DOWN: 
			if (k == 3) k = 1;
			else k++;
			break;
		case ENTER:
			if (k == 1)
			{
				this->resetGame();
				return;
			}
			if (k == 2)
			{
				this->loadGame();
				return;
			}
			if (k == 3) sound = this->setting();
			break;
		}
		for (int i = 0; i < 3; i++) mau[i] = 15;
		mau[k - 1] = 10; 
	}
}

void CGAME::loadGame()
{ 
	Sleep(300);
	FILE *f;
	while (1)
	{
		system("cls");
		char dword[100];
		GotoXY(50, 10);
		SetColor(10);
		cout << "Nhap ten file: ";
		SetColor(15);
		gets(dword);
		f = fopen(dword, "rb");
		if (f != NULL)
		{
			break;
		}
		else
		{
			GotoXY(50, 13);
			SetColor(12);
			cout << "File da nhap khong ton tai!";
			Sleep(1000);
		}
	}
	int x, y;
	fread(&sl, 1, sizeof(int), f);
	for (int i = 0; i < sl; i++)
	{
		fread(&x, 1, sizeof(int), f);
		fread(&y, 1, sizeof(int), f);
		axt[i].setX(x);
		axt[i].setY(y);
		fread(&x, 1, sizeof(int), f);
		fread(&y, 1, sizeof(int), f);
		axh[i].setX(x);
		axh[i].setY(y);
		fread(&x, 1, sizeof(int), f);
		fread(&y, 1, sizeof(int), f);
		akl[i].setX(x);
		akl[i].setY(y);
		fread(&x, 1, sizeof(int), f);
		fread(&y, 1, sizeof(int), f);
		ac[i].setX(x);
		ac[i].setY(y);
	}
	fread(&x, 1, sizeof(int), f);
	fread(&y, 1, sizeof(int), f);
	cn.setX(x);
	cn.setY(y);
	cn.setState(true);
	fclose(f);
	loading();
}

void CGAME::saveGame()
{
	FILE *f;
	Sleep(300);
	system("cls");
	char dword[100];
	GotoXY(50, 10);
	SetColor(10);
	cout << "Nhap ten file: ";
	SetColor(15);
	gets(dword);
	f = fopen(dword, "wb");
	int x, y;
	fwrite(&sl, 1, sizeof(int), f);
	for (int i = 0; i < sl; i++)
	{
		x = axt[i].getX();
		y = axt[i].getY();
		fwrite(&x, 1, sizeof(int), f);
		fwrite(&y, 1, sizeof(int), f);
		x = axh[i].getX();
		y = axh[i].getY();
		fwrite(&x, 1, sizeof(int), f);
		fwrite(&y, 1, sizeof(int), f);
		x = akl[i].getX();
		y = akl[i].getY();
		fwrite(&x, 1, sizeof(int), f);
		fwrite(&y, 1, sizeof(int), f);
		x = ac[i].getX();
		y = ac[i].getY();
		fwrite(&x, 1, sizeof(int), f);
		fwrite(&y, 1, sizeof(int), f);
	}
	x = cn.getX();
	y = cn.getY();
	fwrite(&x, 1, sizeof(int), f);
	fwrite(&y, 1, sizeof(int), f);
	fclose(f);
}

void CGAME::pauseGame(bool &run)
{
	run = false;
}

void CGAME::resumeGame(bool &run)
{
	run = true;
}

bool CGAME::setting()
{
	string menu[2] = { "Yes", "No"};
	int mau[2];
	mau[0] = 10; mau[1] = 12;
	int k = 1;
	system("cls");
	while (1)
	{
		GotoXY(50, 10);
		SetColor(11);
		cout << "Setting" << endl;
		SetColor(13);
		GotoXY(43, 12);
		cout << "Ban co muon bat am thanh? ";
		for (int i = 1; i <= 2; i++)
		{
			GotoXY(50, 13 + i);
			SetColor(mau[i - 1]);
			cout << i << ". " << menu[i - 1];
		}
		int z = _getch();
		TRANGTHAI trangthai = key(z);
		switch (trangthai)
		{
		case UP :
			k = 2 - (k + 1) % 2;
			break;
		case DOWN:
			k = 2 - (k + 1) % 2;
			break;
		case ENTER:
			if (k == 1) return true;
			if (k == 2) return false;
		}
		for (int i = 0; i < 2; i++) mau[i] = 12;
		mau[k - 1] = 10;
	}
}

void CGAME::nextLevel()
{
	sl += 1;
	for (int i = 1; i <= sl; i++)
	{
		axt[i - 1].setX(10 * i);
		axt[i - 1].setY(16);
		axh[i - 1].setX(endX - 10 * (i - 1));
		axh[i - 1].setY(10);
		akl[i - 1].setX(10 * i);
		akl[i - 1].setY(3);
		ac[i - 1].setX(endX - 10 * (i - 1));
		ac[i - 1].setY(22);
	}
	cn.setX(45); cn.setY(24);
	cn.setState(true);
}

void CGAME::updatePosPeople(char kt)
{
	switch (kt)
	{
	case 'W':
		cn.Up();
		break;
	case 'S':
		cn.Down();
		break;
	case 'A':
		cn.Left();
		break;
	case 'D':
		cn.Right();
		break;
	default:
		break;
	}
}

void CGAME::updatePosVehicle(int dem, int kt1, int kt2)
{
	for (int i = 0; i < sl; i++)
	{
		if (dem % 2 == 0 && kt1 == 0) axt[i].setX(axt[i].getX() + 1);
		if (dem % 3 == 0 && kt2 == 0) axh[i].setX(axh[i].getX() - 1);
	}
}

void CGAME::updatePosAnimal(int dem)
{
	for (int i = 0; i < sl; i++)
	{
		if (dem % 1 == 0) akl[i].setX(akl[i].getX() + 1);
		if (dem % 4 == 0) ac[i].setX(ac[i].getX() - 1);
	}
}

void CGAME::Dead()
{
	cn.setState(false);
}


