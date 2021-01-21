#include <iostream>
#include <deque>
#include <algorithm>
#include <map>
#include <cstring>
using namespace std;
struct shark
{
	int a;
	int b;
	int pow;
	int nowDir;
	int dir[4][4];
	bool out = false;
};
struct field {
	int smell;
	int time=0;
};
bool cmp(shark a, shark b)
{

	return a.pow < b.pow;
}
field Map[50][50];
int N;
int M;
int K;
int D[4][2] = { {-1,0},{1,0},{0,-1},{0,1} };

deque<shark> BFS;
map<int, int> Hash;

void SmellPass()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (Map[i][j].smell > 0)
			{
				Map[i][j].time--;
			}
			if (Map[i][j].time == 0)
			{
				Map[i][j].smell = 0;
			}
		}

	}
}

void Move(int i,int newDir, int newA, int newB)
{
	BFS[i].a = newA;
	BFS[i].b = newB;
	BFS[i].nowDir = newDir;
	if (Hash[newA*N + newB] > 0 && Hash[newA*N + newB] < BFS[i].pow)
	{
		BFS[i].out = true;
	}
	else if (Hash[newA*N + newB] == 0 || BFS[i].pow < Hash[newA*N + newB])
	{
		Hash[newA*N + newB] = BFS[i].pow;
		Map[newA][newB].smell = BFS[i].pow;
		Map[newA][newB].time = K + 1;
	}
}


void MoveShark()
{
	Hash.clear();
	field Map_cp[50][50];
	memcpy(Map_cp, Map, sizeof(Map));
	for (int i = 0; i < M; i++)
	{
		if (BFS[i].out) { continue; }
		bool chk = false;
		for (int j = 0; j < 4; j++)
		{
			
			int newDir = BFS[i].dir[BFS[i].nowDir][j];
			int newA = BFS[i].a + D[newDir][0];
			int newB = BFS[i].b + D[newDir][1];
			if (newA >= 0 && newA < N&&newB >= 0 && newB < N&&Map_cp[newA][newB].smell == 0)
			{
				chk = true;
				Move(i,newDir, newA, newB);
				break;
			}
		}
		if (chk) { continue; }
		for (int j = 0; j < 4; j++)
		{
			int newDir = BFS[i].dir[BFS[i].nowDir][j];
			int newA = BFS[i].a + D[newDir][0];
			int newB = BFS[i].b + D[newDir][1];
			if (newA >= 0 && newA < N&&newB >= 0 && newB < N&&Map_cp[newA][newB].smell == BFS[i].pow)
			{
				Move(i, newDir,newA, newB);
				break;
			}
		}
	}
}

bool fin()
{
	int num = 0;
	for (int i = 0; i < M; i++)
	{
		if (BFS[i].out) { num++; }
	}
	if (num == M - 1)
	{
		return true;
	}
	return false;
}


int main()
{
	cin >> N >> M >> K;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> Map[i][j].smell;
			if (Map[i][j].smell > 0)
			{
				Map[i][j].time = K;
				shark temp;
				temp.a = i; temp.b = j; temp.pow = Map[i][j].smell;
				BFS.push_back(temp);
			}
		}
	}
	sort(BFS.begin(), BFS.end(),cmp);
	for (int i = 0; i < M; i++)
	{
		cin >> BFS[i].nowDir;
		BFS[i].nowDir--;
	}
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
			cin >> BFS[i].dir[j][k];
			BFS[i].dir[j][k]--;
			}
		}
	}
	

	for (int i = 1; i <= 1000; i++)
	{
		MoveShark();
		SmellPass();
		if(fin())
		{
			cout << i << endl;
			break;
		}
		if (i == 1000)
		{
			cout << -1 << endl;
		}
	}

}