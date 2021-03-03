#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int N, M, T;
int Map[51][51];
int Ans;
void AnsCal()
{

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (Map[i][j] == -1) { continue; }
			Ans += Map[i][j];
		}
	}

}


void Input()
{
	cin >> N >> M >> T;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> Map[i][j];
		}
	}
}

void Rotate(int tar, int dir, int k) // tar ÇÏ³ª»¬°Í.
{
	int d;
	if (dir == 0) { d = 1; }
	else { d = -1; }
	int temp[51];
	int num = tar;
	while (num <= N)
	{
		for (int i = 0; i < M; i++)
		{
			int t = i + d * k;
			if (t >= M) { t -= M; }
			if (t < 0) { t += M; }
			temp[t] = Map[num - 1][i];
		}
		memcpy(Map[num - 1], temp, sizeof(temp));
		num += tar;
	}
}

void Action()
{
	bool chk = false;
	int Map_cp[51][51];
	memcpy(Map_cp, Map, sizeof(Map));
	float num = 0; float avg = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (Map[i][j] != -1)
			{
				avg += Map[i][j]; num++;
			}
			int nearby[2];
			nearby[0] = j + 1; if (nearby[0] == M) { nearby[0] = 0; }
			nearby[1] = j - 1; if (nearby[1] == -1) { nearby[1] = M - 1; }
			if (Map[i][j] == Map[i][nearby[0]] && Map[i][j] != -1)
			{
				Map_cp[i][j] = -1; Map_cp[i][nearby[0]] = -1;
				chk = true;
			}
			if (Map[i][j] == Map[i][nearby[1]] && Map[i][j] != -1)
			{
				Map_cp[i][j] = -1; Map_cp[i][nearby[1]] = -1;
				chk = true;
			}
			if (i + 1 < N&&Map[i][j] == Map[i + 1][j] && Map[i][j] != -1)
			{
				Map_cp[i][j] = -1; Map_cp[i + 1][j] = -1;
				chk = true;
			}
		}
	}
	memcpy(Map, Map_cp, sizeof(Map));
	if (chk) { return; }
	avg = (avg / num);
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (Map[i][j] == -1) { continue; }
			if (Map[i][j] > avg)
			{
				Map[i][j]--;
			}
			else if (Map[i][j] < avg)
			{
				Map[i][j]++;
			}
		}
	}

}



int main()
{
	Input();
	for (int i = 0; i < T; i++)
	{
		int x, d, k;
		cin >> x >> d >> k;
		Rotate(x, d, k);
		Action();
	}
	AnsCal();
	cout << Ans;
}