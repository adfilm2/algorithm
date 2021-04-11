//6:08 -> 6:29
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int Map[50][50];
int N; int M;
int ANS = 99999;
struct point {
	int a;
	int b;
};
vector<point> chickenPos;
int visited[50];
void Input()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> Map[i][j];
			if (Map[i][j] != 2) { continue; }
			point t; t.a = i; t.b = j;
			chickenPos.push_back(t);
			Map[i][j] = 0;
		}
	}
}



int ChickDist(int a, int b, vector<point> chick)
{
	int dist = 100000;
	for (int i = 0; i < M; i++)
	{
		dist = min(dist, abs(a - chick[i].a) + abs(b - chick[i].b));
	}
	return dist;
}



void DFS(vector<point> livingChicken, int idx, int len)
{
	if (livingChicken.size() == M)
	{
		int Map_cp[50][50];
		int cmpNum = 0;
		memcpy(Map_cp, Map, sizeof(Map));
		for (int i = 0; i < M; i++)
		{
			Map[livingChicken[i].a][livingChicken[i].b] = 2;
		}
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (Map[i][j] == 0 || Map[i][j] == 2) { continue; }
				cmpNum += ChickDist(i, j, livingChicken);
			}
		}
		ANS = min(ANS, cmpNum);
		memcpy(Map, Map_cp, sizeof(Map));
		return;
	}

	for (int i = idx; i < len; i++)
	{
		if (visited[i] != 0) { continue; }
		livingChicken.push_back(chickenPos[i]);
		visited[i] = 1;
		DFS(livingChicken, i, len);
		visited[i] = 0;
		livingChicken.pop_back();
	}
}



int main()
{
	Input();
	vector<point> t;
	DFS(t, 0, chickenPos.size());
	cout << ANS;
}