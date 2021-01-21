#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cstring>
#include <queue>
using namespace std;
int N, M, fuel, A, B;
int tarA, tarB, tarT;
map<int, int> dest;
int Map[250][250];
int visited[250][250];
int dir[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };
int CNT;
struct point {
	int a;
	int b;
	int time;
};

void input()
{
	cin >> N >> M >> fuel;
	CNT = M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> Map[i][j];
		}
	}
	cin >> A >> B;
	A--; B--;
	for (int i = 0; i < M; i++)
	{
		int fa, fb, da, db;
		cin >> fa >> fb >> da >> db;
		fa--; fb--; da--; db--;
		Map[fa][fb] = i + 2;
		dest[i + 2] = (da * N + db);
	}
}

void Routing1(int a, int b) //택시위치;
{
	memset(visited, 0, sizeof(visited));
	point t; t.a = a; t.b = b; t.time = 0;  visited[a][b] = 1;
	if (Map[a][b] > 1) { tarA = a; tarB = b; tarT = 0; return; }
	tarA = 1000; tarB = 1000; tarT = 1000;
	queue<point> BFS; BFS.push(t);
	while (!BFS.empty())
	{
		if (BFS.size() == 0) { tarT = 1000; return; }
		point temp = BFS.front();
		BFS.pop();
		if (tarT != 1000 && temp.time > tarT) { return; }
		for (int i = 0; i < 4; i++)
		{
			int newA = temp.a + dir[i][0]; int newB = temp.b + dir[i][1]; int newT = temp.time + 1;
			if (newA >= 0 && newA < N&&newB >= 0 && newB < N&&visited[newA][newB] == 0 && Map[newA][newB] != 1)
			{
				visited[newA][newB] = 1;
				point newOne; newOne.a = newA; newOne.b = newB; newOne.time = newT;
				BFS.push(newOne);
				if (Map[newA][newB] > 1 && newT < tarT)
				{
					tarA = newA; tarB = newB; tarT = newT;
				}
				else if (Map[newA][newB] > 1 && tarT == newT)
				{
					if (newA < tarA)
					{
						tarA = newA; tarB = newB; tarT = newT;
					}
					else if (newA == tarA && newB < tarB)
					{
						tarA = newA; tarB = newB; tarT = newT;
					}
				}
			}
		}
	}
}

int Routing2(int a, int b, int ta, int tb) //목적지로가자
{
	memset(visited, 0, sizeof(visited));
	point t; t.a = a; t.b = b; t.time = 0;  visited[a][b] = 1;
	queue<point> BFS; BFS.push(t);
	while (!BFS.empty())
	{
		if (BFS.size() == 0) { return -1; }
		point temp = BFS.front();
		BFS.pop();
		for (int i = 0; i < 4; i++)
		{
			int newA = temp.a + dir[i][0]; int newB = temp.b + dir[i][1]; int newT = temp.time + 1;
			if (newA >= 0 && newA < N&&newB >= 0 && newB < N&&visited[newA][newB] == 0 && Map[newA][newB] != 1)
			{
				if (newA == ta && newB == tb) { return newT; }
				visited[newA][newB] = 1;
				point newOne; newOne.a = newA; newOne.b = newB; newOne.time = newT;
				BFS.push(newOne);
			}
		}
	}
	return -1;
}



int main()
{
	input();
	while (1)
	{
		if (CNT == 0) { cout << fuel; break; }
		Routing1(A, B);
		if (tarT == 1000) { cout << -1; break; }
		if (fuel < tarT){cout << -1; break;	}
		else{fuel -= tarT;}
		A = tarA; B = tarB;
		int da = (dest[Map[tarA][tarB]] / N); int db = (dest[Map[tarA][tarB]] % N);
		Map[tarA][tarB] = 0;
		if (A != da || B != db) {
			int refill = Routing2(A, B, da, db);
			if (refill == -1) { cout << -1; break; }
			A = da; B = db;
			if (fuel < refill){	cout << -1; break;}
			else
			{
				fuel -= refill;
				fuel += (refill * 2);
				CNT--;
			}
		}
	}
}