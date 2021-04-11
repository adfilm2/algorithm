//16:05
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
int N, M, D;
int Map[15][15];
int visited[15];
int enemyNum;
int Kill;
int Answer;


void Print()
{
	cout << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cout << Map[i][j] << " ";
		}cout << endl;
	}
}



void DropEnemy()
{
	int MapCp[15][15];
	memset(MapCp, 0, sizeof(Map));
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			if (Map[i][j] == 0) { continue; }
			if (i == N - 1) { enemyNum--; continue; }
			MapCp[i + 1][j] = 1;
		}
	}
	memcpy(Map, MapCp, sizeof(Map));
}


void Shot(vector<int> arcLoc)
{
	int MapCp[15][15];
	memcpy(MapCp, Map, sizeof(Map));
	for (int i = 0; i < 3; i++)
	{
		int minDist = 99999;
		int shotA = -1; int shotB = -1;
		for (int a = N - D; a < N; a++)
		{
			for (int b = arcLoc[i] - D; b <= arcLoc[i] + D; b++)
			{
				if (Map[a][b] == 0) { continue; }
				int newDist = abs(N - a) + abs(arcLoc[i] - b);
				if (newDist > D) { continue; }
				if (minDist > newDist || (minDist == newDist && b < shotB))
				{
					minDist = newDist;
					shotA = a; shotB = b;
				}
			}
		}
		if (shotA == -1) { continue; }
		if (MapCp[shotA][shotB] == 0) { continue; }
		MapCp[shotA][shotB] = 0;
		Kill++;
		enemyNum--;
	}
	memcpy(Map, MapCp, sizeof(Map));
}


void PlayGame(vector<int> arcLoc)
{
	int MapCp[15][15];
	memcpy(MapCp, Map, sizeof(Map));
	int tEnemyNum = enemyNum;

	while (enemyNum > 0)
	{
		Shot(arcLoc);
		DropEnemy();
	}
	memcpy(Map, MapCp, sizeof(Map));
	enemyNum = tEnemyNum;
	Answer = max(Answer, Kill);
	Kill = 0;
}




void DFS(vector<int> arcLoc, int idx)
{
	if (arcLoc.size() == 3)
	{
		PlayGame(arcLoc);
		return;
	}

	for (int i = idx; i < M; i++)
	{
		if (visited[i] == 1) { continue; }
		visited[i] = 1;
		arcLoc.push_back(i);
		DFS(arcLoc, i);
		arcLoc.pop_back();
		visited[i] = 0;
	}

}

int main()
{
	cin >> N >> M >> D;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			cin >> Map[i][j];
			if (Map[i][j] == 1)
				enemyNum++;
		}
	}
	vector<int> loc;
	DFS(loc, 0);
	cout << Answer;

}