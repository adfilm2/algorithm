#include <iostream>
#include <queue>
#include <cstring>
using namespace std;
int N, M;
struct virus
{
	int a;
	int b;
};
deque<virus> viruses;
int Map[100][100];
int Map_cp[100][100];
int dir[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };
int Time = 999999;
bool chk()
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (Map_cp[i][j] == 0) { return false; }
		}
	}
	return true;
}
void print()
{
	cout << endl;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << Map_cp[i][j] << " ";
		}cout << endl;
	}cout << endl;

}


void spread(vector<int> pick)
{
	int len = pick.size();
	memcpy(Map_cp, Map, sizeof(Map));
	deque<virus> BFS;
	for (int i = 0; i < len; i++)
	{
		Map_cp[viruses[pick[i]].a][viruses[pick[i]].b] = 3;
		BFS.push_back(viruses[pick[i]]);
	}
	int ans = 0;
	if (chk()) { Time = 0; return; }
	//print();
	while (1)
	{
		int len = BFS.size();
		if (len == 0) { return; }
		for (int i = 0; i < len; i++)
		{
			virus t = BFS.front();
			BFS.pop_front();
			for (int j = 0; j < 4; j++)
			{
				int newA = t.a + dir[j][0]; int newB = t.b + dir[j][1];
				if (!(newA >= 0 && newA < N&&newB >= 0 && newB < N)) { continue; }
				if (!(Map_cp[newA][newB] == 0 || Map_cp[newA][newB] == 2)) { continue; }
				Map_cp[newA][newB] = 3;
				virus newT; newT.a = newA; newT.b = newB;
				BFS.push_back(newT);
			}
		}
		//print();

		ans++;
		if (chk())
		{
			Time = min(Time, ans);
			return;
		}
	}
}


void comb(vector<int> pick, int idx, int siz) //siz는 모든 초기바이러스놈들
{
	if (pick.size() == M)
	{
		spread(pick);
		return;
	}
	for (int i = idx + 1; i < siz; i++)
	{
		pick.push_back(i);
		comb(pick, i, siz);
		pick.pop_back();
	}
}

int main()
{
	cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> Map[i][j];
			if (Map[i][j] == 2)
			{
				virus temp;
				temp.a = i; temp.b = j;
				viruses.push_back(temp);
			}
		}
	}
	int len = viruses.size();
	vector<int> pick;
	for (int i = 0; i <= len - M; i++)
	{
		pick.push_back(i);
		comb(pick, i, len);
		pick.pop_back();
	}
	if (Time == 999999) { Time = -1; }
	cout << Time;


}