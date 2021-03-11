#include <iostream>
#include <deque>
#include <map>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
int N;
int Map[21][21];
int visited[21][21];
int A, B;
int tarA = 99; int tarB = 99; int tarT = -1; // target위치, 거기까지시간 T
int s_size = 2;
int EXP = 2;
int Ans;
int dir[4][2] = { {-1,0},{0,-1} ,{0,1},{1,0}, };

struct point {
	int a;
	int b;
	int time;
};



void input()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> Map[i][j];
			if (Map[i][j] != 9) { continue; }
			A = i; B = j;
			Map[i][j] = 0;	
		}
	}
}


void Routing(int a, int b)
{
	memset(visited, 0, sizeof(visited));
	tarA = 99; tarB = 99; tarT = 1000;
	point t; t.a = a; t.b = b; t.time = 0; visited[a][b] = 1;
	queue<point> BFS; BFS.push(t);
	int limit = 0;
	while (!BFS.empty())
	{
		point temp = BFS.front();
		BFS.pop();
		for (int j = 0; j < 4; j++)
		{
			int newA = temp.a + dir[j][0]; int newB = temp.b + dir[j][1]; int newT = temp.time + 1;
			if (!(newA >= 0 && newA < N&&newB >= 0 && newB < N&& visited[newA][newB] == 0 && Map[newA][newB] <= s_size))
			{
				continue;
			}
			if (Map[newA][newB] < s_size&&Map[newA][newB]>0 && newT <= tarT)
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
			else 
			{
				point newOne; newOne.a = newA; newOne.b = newB; newOne.time = newT;
				visited[newA][newB] = 1;
				BFS.push(newOne);
			}
		}
		//}
		limit++;
	}
}


int main()
{
	input();
	while (1)
	{
		Routing(A, B);
		if (tarA == 99 && tarB == 99)
		{
			cout << Ans; break;
		}
		else
		{
			Map[tarA][tarB] = 0;
			A = tarA; B = tarB;
			Ans += tarT;
			EXP--;
			if (EXP == 0)
			{
				s_size++;
				EXP = s_size;
			}
		}
	}

}