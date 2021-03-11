#include <iostream>
#include <cmath>
#include <algorithm>
#include <map>
using namespace std;
int N, L, R;
int Map[51][51];
int visited[51][51];
int dir[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };
bool chk = true;

void Print()
{
	cout << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << Map[i][j] << " ";
		}cout << endl;
	}cout << endl;

}

void Input()
{
	cin >> N >> L >> R;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> Map[i][j];
		}
	}
}

void WideOpen(int a, int b, int num)
{
	for (int i = 0; i < 4; i++)
	{
		int newA = a + dir[i][0];
		int newB = b + dir[i][1];
		if (!(newA >= 0 && newA < N&&newB >= 0 && newB < N)) { continue; }
		if (visited[newA][newB] != 0) { continue; }
		if (!(abs(Map[newA][newB] - Map[a][b]) >= L && abs(Map[newA][newB] - Map[a][b]) <= R)) { continue; }
		chk = true;
		visited[newA][newB] = num;
		WideOpen(newA, newB, num);
	}
}
void Update()
{
	int Avg[2510][2];
	memset(Avg, 0, sizeof(Avg));
	int siz = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			siz = max(siz, visited[i][j]);
			Avg[visited[i][j]][0] += Map[i][j];
			Avg[visited[i][j]][1]++;
		}
	}
	for (int i = 1; i <= siz; i++)
	{
		Avg[i][0] /= Avg[i][1];
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			Map[i][j] = Avg[visited[i][j]][0];
		}
	}
	memset(visited, 0, sizeof(visited));
}

int main()
{
	Input();
	int Ans = 0;
	while (chk)
	{
		chk = false;
		int area = 1;
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (!(visited[i][j] == 0)) { continue; }
				visited[i][j] = area;
				WideOpen(i, j, area);
				area++;
			}
		}
		Update();
		//Print();
		if (chk) { Ans++; }
	}
	cout << Ans;
}