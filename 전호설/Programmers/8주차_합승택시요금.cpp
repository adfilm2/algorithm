#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int Map[200][200];

void Print(int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << Map[i][j] << " ";
		}cout << endl;
	}cout << endl;
}

void MapSet(int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			Map[i][j] = 9999999;
			if (i == j) { Map[i][j] = 0; }
		}
	}
}

void Floyd(int n)
{
	for (int k = 0; k < n; k++)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (Map[i][k] + Map[k][j] < Map[i][j])
				{
					Map[i][j] = Map[i][k] + Map[k][j];
				}
			}
		}
	}
}


int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
	int answer = 0;
	s--; a--; b--;
	MapSet(n);
	int len = fares.size();
	for (int i = 0; i < len; i++)
	{
		Map[fares[i][0] - 1][fares[i][1] - 1] = fares[i][2];
		Map[fares[i][1] - 1][fares[i][0] - 1] = fares[i][2];
	}
	Floyd(n);
	//Print(n);
	answer = Map[s][a] + Map[s][b];
	for (int i = 0; i < n; i++)
	{
		if (i == s) { continue; }
		int tmp = Map[s][i] + Map[i][a] + Map[i][b];
		answer = min(answer, tmp);
	}

	return answer;
}