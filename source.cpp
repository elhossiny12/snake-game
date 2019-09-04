#include<iostream>
#include<string>
#include<conio.h>
#include<windows.h>
#include <stdlib.h> 
using namespace std;
void gotoxy(int x, int y);
class Coordinates
{
protected:
	int Ox;
	int Oy;
public:
	Coordinates()
	{
		Ox = 20;
		Oy = 10;
	}
	void Set_X(int x)
	{
		Ox = x;
	}
	void Set_Y(int y)
	{
		Oy = y;
	}
	int Get_Y()
	{
		return Oy;
	}
	int Get_X()
	{
		return Ox;
	}
	void Print(int x, int y)
	{
		gotoxy(x, y);
		cout << "*";
		gotoxy(0, 0);
	}
	void Clear(int x, int y)
	{
		gotoxy(x, y);
		cout << " ";
		gotoxy(0, 0);
	}
	void Delay(int s)
	{
		long long n = 100000 * s;
		for (int i = 0; i < n; i++) {}
	}
	void Move(char k)
	{
		switch (k)
		{
		case 'w':
			Clear(Ox, Oy);
			Oy--;
			Print(Ox, Oy);
			Delay(1);
			break;
		case 's':
			Clear(Ox, Oy);
			Oy++;
			Print(Ox, Oy);
			Delay(1);
			break;
		case 'd':
			Clear(Ox, Oy);
			Ox++;
			Print(Ox, Oy);
			Delay(1);
			break;
		case 'a':
			Clear(Ox, Oy);
			Ox--;
			Print(Ox, Oy);
			Delay(1);
			break;
		}

	}
	void GetInput(char &m)
	{
		if (_kbhit())
			m = _getch();
	}
	void Follow(Coordinates co)
	{
		if (Ox > co.Get_X()) Move('a');
		else if (Ox < co.Get_X()) Move('d');
		else if (Oy > co.Get_Y()) Move('w');
		else if (Oy <co.Get_Y()) Move('s');



	}

};
class Food :public Coordinates
{
	int rand_x;
	int rand_y;
public:
	Food()
	{
		rand_x = 10;
		rand_y = 20;
	}
	void Fruit(int &count)
	{

		if ((count == 100))
		{
			count = 1;
			Clear(rand_x, rand_y);
			rand_x = rand() % 100 + 1;
			rand_y = rand() % 20 + 1;
			Print(rand_x, rand_y);
			Delay(1);
		}
		count++;
	}
};
class Snake
{
	Coordinates CA[100];
	int Size;
public:
	Snake()
	{
		Size = 0;
	}
	void SetSize(int s)
	{
		Size = s;

	}
	int  GetSize()
	{
		return Size;
	}
	void AddCorrdinates()
	{
		Size++;
		if (Size > 1){
			CA[Size].Set_X(CA[Size - 1].Get_X() - 1);
		CA[Size].Set_Y(CA[Size - 1].Get_Y());
		
		}
	}
	bool IsEat(Food f, Coordinates co)
	{
		if ((f.Get_X() == co.Get_X()) && (f.Get_Y() == co.Get_Y()))return true;
		return false;
	
	}
	void Game() {
		char l = 'o';
		int n = 1;
		Food f1;
		while (1)
		{
			CA[0].GetInput(l);
			CA[0].Move(l);
			f1.Fruit(n);
			if (IsEat(f1, CA[0])) AddCorrdinates();
			for (int i = 0; i < Size-1; i++)
			{
				CA[i + 1].Follow(CA[i]);
			}
		}




	}


};
int main() {

	Snake s;
	s.Game();

	system("pause");
}

void gotoxy(int x, int y)           //definition of gotoxy function//                                               
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
