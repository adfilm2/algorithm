#include <iostream>
#include <cstring>
using namespace std;

int R, C, T;
int Map[100][100];
int Air[2];
int dir[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };

void Print()
{
	cout << endl;
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			cout << Map[i][j] << " ";
		}cout << endl;
	}cout << endl;
}

void Input()
{
	cin >> R >> C >> T;
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			cin >> Map[i][j];
			if (Map[i][j] != -1) { continue; }
			if (Air[0] == 0) { Air[0] = i; Air[1] = i + 1; }
		}
	}
}

void Spread()
{
	int Map_cp[100][100];
	memcpy(Map_cp, Map, sizeof(Map));
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			if (Map[i][j] == 0) { continue; }
			int num = (Map[i][j] / 5); int minus = 0;
			for (int k = 0; k < 4; k++)
			{
				int newA = i + dir[k][0]; int newB = j + dir[k][1];
				if (!(newA >= 0 && newA < R&&newB >= 0 && newB < C&&Map[newA][newB] != -1)) { continue; }
				minus += num;
				Map_cp[newA][newB] += num;
			}
			Map_cp[i][j] -= minus;
		}
	}
	memcpy(Map, Map_cp, sizeof(Map));
}

void WindBlow()
{
	int Map_cp[100][100];
	memcpy(Map_cp, Map, sizeof(Map));
	for (int i = 1; i < C - 1; i++)
	{
		Map_cp[Air[0]][i + 1] = Map[Air[0]][i];
		Map_cp[Air[1]][i + 1] = Map[Air[1]][i];
	}
	Map_cp[Air[0]][1] = 0; Map_cp[Air[1]][1] = 0;
	for (int j = Air[0]; j >= 1; j--)
	{
		Map_cp[j - 1][C - 1] = Map[j][C - 1];
	}
	for (int i = C - 1; i >= 1; i--)
	{
		Map_cp[0][i - 1] = Map[0][i];
		Map_cp[R - 1][i - 1] = Map[R - 1][i];
	}
	for (int j = 0; j < Air[0]; j++)
	{
		if (Map[j + 1][0] == -1) { continue; }
		Map_cp[j + 1][0] = Map[j][0];
	}
	for (int j = Air[1]; j < R - 1; j++)
	{
		Map_cp[j + 1][C - 1] = Map[j][C - 1];
	}
	for (int j = R - 1; j > Air[1]; j--)
	{
		if (Map[j - 1][0] == -1) { continue; }
		Map_cp[j - 1][0] = Map[j][0];
	}
	memcpy(Map, Map_cp, sizeof(Map));
}


int main()
{
	Input();
	for (int t = 0; t < T; t++)
	{
		Spread();
		WindBlow();
	}
	int Ans = 0;
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			if (Map[i][j] > 0)
			{
				Ans += Map[i][j];
			}
		}
	}
	cout << Ans;
}
