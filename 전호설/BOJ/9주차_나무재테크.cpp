#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;
int N, M, K;
deque<int> Map[11][11];
int Fuel[11][11];
int Ac[11][11];
int dir[8][2] = { {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1} };
int Ans;
void Input()
{
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			Fuel[i][j] = 5;
			cin >> Ac[i][j];
		}
	}
	for (int i = 0; i < M; i++)
	{
		int a, b, age;
		cin >> a >> b >> age;
		a--; b--;
		Map[a][b].push_back(age);
	}
}
void SpringSummer()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int siz = Map[i][j].size();
			if (siz == 0) { continue; }
			sort(Map[i][j].begin(), Map[i][j].end());
			int dead = 0;
			for (int k = 0; k < siz; k++)
			{
				int temp = Map[i][j].front();
				Map[i][j].pop_front();
				if (temp > Fuel[i][j]) { dead += (temp / 2); continue; }
				Fuel[i][j] -= temp;
				Map[i][j].push_back(temp + 1);
			}
			Fuel[i][j] += dead;
		}
	}
}

void FallWinter()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			Fuel[i][j] += Ac[i][j];
			int siz = Map[i][j].size();
			if (siz == 0) { continue; }
			for (int k = 0; k < siz; k++)
			{
				if (Map[i][j][k] % 5 != 0) { continue; }
				for (int d = 0; d < 8; d++)
				{
					int newA = i + dir[d][0];
					int newB = j + dir[d][1];
					if (!(newA >= 0 && newA < N&&newB >= 0 && newB < N)) { continue; }
					Map[newA][newB].push_back(1);
				}
			}
		}
	}
}

int FindAns()
{
	int ans = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			ans += Map[i][j].size();
		}
	}
	return ans;
}





int main()
{
	Input();
	for (int i = 0; i < K; i++)
	{
		SpringSummer();
		FallWinter();
	}
	cout << FindAns();

}