#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

int Key[4][20][20];
int Map[60][60];
int Map_cp[60][60];
int lenK;
int lenL;
void RotateKey()
{
	for (int t = 0; t <= 2; t++)
		for (int i = 0; i < lenK; i++)
			for (int j = 0; j < lenK; j++)
				Key[t + 1][i][j] = Key[t][lenK - 1 - j][i];
}

void BuildMap(vector<vector<int>>k, vector<vector<int>> l)
{
	lenK = k.size();
	lenL = l.size();
	for (int i = 0; i < lenK; i++)
		for (int j = 0; j < lenK; j++)
			Key[0][i][j] = k[i][j];

	RotateKey();
	for (int i = 0; i < lenL; i++)
		for (int j = 0; j < lenL; j++)
		{
			Map[lenK - 1 + i][lenK - 1 + j] = l[i][j];
			Map_cp[lenK - 1 + i][lenK - 1 + j] = l[i][j];
		}
}

bool ChkAns()
{
	for (int i = 0; i < lenL; i++)
		for (int j = 0; j < lenL; j++)
			if (Map[lenK - 1 + i][lenK - 1 + j] == 0)
				return false;

	return true;
}

bool Combine(int a, int b, int r)
{
	bool chk = false;
	for (int i = 0; i < lenK; i++)
	{
		for (int j = 0; j < lenK; j++)
		{
			if (Map[a + i][b + j] == 0 && Key[r][i][j] == 1)
			{
				Map[a + i][b + j] = 1;
			}
			else if (Map[a + i][b + j] == 1 && Key[r][i][j] == 1)
			{
				return chk;
			}
		}
	}
	chk = ChkAns();
	return chk;
}

bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
	bool answer = true;
	BuildMap(key, lock);
	for (int r = 0; r < 4; r++)
	{
		for (int i = 0; i < lenK + lenL - 1; i++)
		{
			for (int j = 0; j < lenK + lenL - 1; j++)
			{
				if (Combine(i, j, r)) { return true; }
				memcpy(Map, Map_cp, sizeof(Map));
			}
		}
	}
	return false;
}