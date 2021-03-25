#include <iostream>
#include <map>
#include <vector>
#include <cstring>
#include <string>
using namespace std;

//0:윗 1:아래 2:앞 3:뒤 4:왼 5:오
char Cube[6][3][3];

//Hash, 
int Map[6][4][4] =
{
{{3,2,1,0},{5,2,1,0},{2,2,1,0},{4,2,1,0}}, // 위 시계 : 뒤 오 앞 왼
{{2,6,7,8},{5,6,7,8},{3,6,7,8},{4,6,7,8}}, // 아래 시계 : 앞 오 뒤 왼
{{0,6,7,8},{5,0,3,6},{1,2,1,0},{4,8,5,2}},
{{0,2,1,0},{4,0,3,6},{1,6,7,8},{5,8,5,2}},
{{0,0,3,6},{2,0,3,6},{1,0,3,6},{3,8,5,2}},
{{0,8,5,2},{3,0,3,6},{1,8,5,2},{2,8,5,2}}
};

map<char, int> Hash;

void CubeSet()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			Cube[0][i][j] = 'w';
			Cube[1][i][j] = 'y';
			Cube[2][i][j] = 'r';
			Cube[3][i][j] = 'o';
			Cube[4][i][j] = 'g';
			Cube[5][i][j] = 'b';
		}
	}
	Hash['U'] = 0;
	Hash['D'] = 1;
	Hash['F'] = 2;
	Hash['B'] = 3;
	Hash['L'] = 4;
	Hash['R'] = 5;
	Hash['+'] = 1;
	Hash['-'] = 3;
}

void Print()
{
	for (int j = 0; j < 3; j++)
	{
		for (int k = 0; k < 3; k++)
		{
			cout << Cube[0][j][k];
		}cout << endl;
	}
}

void CubeRot(char key, int t)
{
	for (int i = 0; i < t; i++)
	{
		char tCube[6][3][3];
		memcpy(tCube, Cube, sizeof(Cube));
		for (int j = 0; j < 3; j++)
		{
			for (int k = 0; k < 3; k++)
			{
				tCube[key][j][k] = Cube[key][2 - k][j];
			}
		}
		for (int j = 0; j < 4; j++)
		{
			int before; int after;
			before = Map[key][j][0];
			if (j + 1 < 4)
				after = Map[key][j + 1][0];
			else
				after = Map[key][0][0];

			for (int k = 1; k <= 3; k++)
			{
				int a = Map[key][j][k] / 3;
				int b = Map[key][j][k] % 3;
				int ta; int tb;
				if (j + 1 < 4)
				{
					ta = Map[key][j + 1][k] / 3;
					tb = Map[key][j + 1][k] % 3;
				}
				else
				{
					ta = Map[key][0][k] / 3;
					tb = Map[key][0][k] % 3;
				}
				tCube[after][ta][tb] = Cube[before][a][b];
			}
		}
		memcpy(Cube, tCube, sizeof(Cube));
	}
}

int main()
{
	int take;
	cin >> take;
	for (int i = 0; i < take; i++)
	{
		int attemp;
		cin >> attemp;
		CubeSet();
		for (int j = 0; j < attemp; j++)
		{
			string temp;
			cin >> temp;
			CubeRot(Hash[temp[0]], Hash[temp[1]]);
		}
		Print();
	}
}