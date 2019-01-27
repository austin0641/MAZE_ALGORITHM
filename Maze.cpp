#include <vector>
#include <iostream>
#include <windows.h>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <time.h>
using namespace std;
class coor//coordinates, made for Animation function only
{
public:
	int x, y;//coordinates
	char c;//the char that's in that coordinates
	coor(int a, int b) { x = a; y = b; c = ' '; }
	coor(int a, int b, char h){ x = a, y = b, c = h; }
	coor(){ x = 0; y = 0; c = ' '; }
};
void gotoxy(int x, int y)//given, move cursor to a location
{
	COORD pos = { x, y };
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(output, pos);
}
class node//a node that the linked list is based on
{
public:
	char c;
	node *next, *prev;
};
class stack//stack thats base on a linked list
{
public:
	node *p;
	stack()
	{
		p = new node;
		p->c = ' ';
		p->prev = nullptr;
	}
	void push(char c)
	{
		p->next = new node;
		p->next->prev = p;
		p = p->next;
		p->c = c;
	}
	char pop()
	{
		if (p->prev != nullptr)
		{

			char t;
			t = p->c;
			p = p->prev;
			delete p->next;
			return t;
		}
		return 'n';
	}
};
class maze
{
public:
	bool readMaze(string);//read maze from file
	void displayMaze();//display maze on screen
	void dyingAnimation(int);//display animation after maze is soved
	int findExit();//the mouse will try to find exit
	void moveMouse(char);//mouse move one coornate at a time
	char map[30][100];
	int x, y;
	stack path;
	vector<coor> temp;// for animation only
};
void maze::moveMouse(char t)//wdas represent direction that the mouse is going
{
	gotoxy(x, y);
	cout << " ";
	switch (t)
	{
	case 'w': gotoxy(x, --y); break;
	case 'd': gotoxy(++x, y); break;
	case 's': gotoxy(x, ++y); break;
	case 'a': gotoxy(--x, y); break;
	}
	cout << "*";
	gotoxy(x, y);
}
bool maze::readMaze(string fileName)//return true if map exist, false if not
{
	string s;
	fileName += ".txt";
	ifstream getMaze(fileName);
	if (getMaze.is_open())
	{
		for (int i = 0; i < 30; i++)
		{
			getline(getMaze, s);
			for (int j = 0; j < 100; j++)
				map[i][j] = s[j];
		}
		return true;
	}
	return false;
}
void maze::displayMaze()//display maze on screen
{
	system("cls");
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			switch (map[i][j])
			{
			case '1': cout << char(219); break;
			case '0': cout << " "; break;
			case '2': cout << "@"; break;
			case '3': cout << "$"; break;
			default: cout << "?";
			}
		}
		cout << endl;
	}
	gotoxy(x = 0, y = 1);
	cout << "*";
}
int maze::findExit()
{
	while (true)
	{
		if (map[y][x] == '3')//exit if exit is found
			return 3;
		if (map[y][x] == '2')//exit if found bomb
			return 2;
		map[y][x] = 'p';
		if (map[y - 1][x] != '1' && map[y - 1][x] != 'p' && y != 0)//check up
		{
			path.push('s');
			moveMouse('w');
		}
		else if (map[y][x + 1] != '1' && map[y][x + 1] != 'p' && x != 99)//check right
		{
			path.push('a');
			moveMouse('d');
		}
		else if (map[y + 1][x] != '1' && map[y + 1][x] != 'p' && y != 29)//check down
		{
			path.push('w');
			moveMouse('s');
		}
		else if (map[y][x - 1] != '1' && map[y][x - 1] != 'p' && x != 0)//check left
		{
			path.push('d');
			moveMouse('a');
		}
		else
			moveMouse(path.pop());//go back
		if (x == 0 && y == 1)
			return 1;//exit if there is no solution
		Sleep(30);
	}
}
void maze::dyingAnimation(int r)//display different animation depending on the result
{
	string s = "", a = "", k = "", n = "", f = "";
	s += "                  #####     #    #     # #######   ####### #     # ####### ######                   ";
	s += "                 #     #   # #   ##   ## #         #     # #     # #       #     #                  ";
	s += "                 #        #   #  # # # # #         #     # #     # #       #     #                  ";
	s += "                 #  #### #     # #  #  # #####     #     # #     # #####   ######                   ";
	s += "                 #     # ####### #     # #         #     #  #   #  #       #   #                    ";
	s += "                 #     # #     # #     # #         #     #   # #   #       #    #                   ";
	s += "                  #####  #     # #     # #######   #######    #    ####### #     #                  ";
	a += "                ####### #     # ### #######   ####### ####### #     # #     # ######                ";
	a += "                #        #   #   #     #      #       #     # #     # ##    # #     #               ";
	a += "                #         # #    #     #      #       #     # #     # # #   # #     #               ";
	a += "                #####      #     #     #      #####   #     # #     # #  #  # #     #               ";
	a += "                #         # #    #     #      #       #     # #     # #   # # #     #               ";
	a += "                #        #   #   #     #      #       #     # #     # #    ## #     #               ";
	a += "                ####### #     # ###    #      #       #######  #####  #     # ######                ";
	k += "   #    # ### #       #       ####### ######    ######  #     #   ######  ####### #     # ######    ";
	k += "   #   #   #  #       #       #       #     #   #     #  #   #    #     # #     # ##   ## #     #   ";
	k += "   #  #    #  #       #       #       #     #   #     #   # #     #     # #     # # # # # #     #   ";
	k += "   ###     #  #       #       #####   #     #   ######     #      ######  #     # #  #  # ######    ";
	k += "   #  #    #  #       #       #       #     #   #     #    #      #     # #     # #     # #     #   ";
	k += "   #   #   #  #       #       #       #     #   #     #    #      #     # #     # #     # #     #   ";
	k += "   #    # ### ####### ####### ####### ######    ######     #      ######  ####### #     # ######    ";
	n += "                           #     # #######   ####### #     # ### #######                            ";
	n += "                           ##    # #     #   #        #   #   #     #                               ";
	n += "                           # #   # #     #   #         # #    #     #                               ";
	n += "                           #  #  # #     #   #####      #     #     #                               ";
	n += "                           #   # # #     #   #         # #    #     #                               ";
	n += "                           #    ## #     #   #        #   #   #     #                               ";
	n += "                           #     # #######   ####### #     # ###    #                               ";

	for (int i = 0; i < 5; i++)
	{
		gotoxy(x, y);
		cout << " ";
		gotoxy(x, y);
		Sleep(350);
		cout << "*";
		gotoxy(x, y);
		Sleep(350);
	}
	for (int i = 0; i < 30; i++)
		for (int j = 0; j < 100; j++)
		{
		coor n(i, j); temp.push_back(n);
		}
	for (int i = 0; i < 700; i++)
	{
		temp[i + 500].c = s[i];
	}
	if (r == 3)
		f = a;
	else if (r == 2)
		f = k;
	else f = n;
	for (int i = 0; i < 700; i++)
	{
		temp[i + 1800].c = f[i];
	}
	int i, t = temp.size();
	if (r == 1 || r == 2)// do the dissparring animation if mouse lose
	{
		while (true)
		{
			i = rand() % t--;
			gotoxy(temp[i].y, temp[i].x);
			cout << temp[i].c;
			temp.erase(temp.begin() + i);
			Sleep(t / 1700);
			if (t == 0)
				break;
		}
	}
	else//do the other one if mouse win
	{
		coor arr[4];
		for (int i = 0; i < 4; i++)
		{
			arr[i].x = i*-5;
			arr[i].y = i*-2;
		}
		arr[0].c = '+';
		arr[1].c = '-';
		arr[2].c = '+';
		while (true)
		{
			for (coor &d : arr)
			{
				if (arr[3].x >= 0 && arr[3].x < 100 && arr[3].y >= 0 && arr[3].y < 30)
					arr[3].c = temp[arr[3].y * 100 + arr[3].x].c;
				if (d.x >= 0 && d.x < 100 && d.y >= 0 && d.y < 30)
				{
					gotoxy(d.x, d.y);
					cout << d.c;
				}
				d.x++;
				if (d.x == 100){ d.x = 0; d.y++; }
			}
			if (arr[3].x == 100 && arr[3].y == 30)
				break;
			Sleep(1);
		}
	}
}
int main()
{
	maze m;
	string s;
	cout << "(enter either 'example_maze1' or 'example_maze2' as file name if you don't have one)\n";
	while (true)
	{
		cout << "enter file name(don't include .txt)\n";
		cin >> s;
		if (m.readMaze(s))
			break;
		else cout << "couldn't find file, please try again\n";
	}
	m.displayMaze();
	int result = m.findExit();
	m.dyingAnimation(result);
	gotoxy(0, 31);
	return 0;
}
