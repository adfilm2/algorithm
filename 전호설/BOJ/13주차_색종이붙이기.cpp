#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
int Map[10][10];
vector<int>point;
int visited[10][10];
int placeLeft;
int Ans = 99999;
bool chk = false;

void Input()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cin >> Map[i][j];
			if (Map[i][j] == 1) {
				point.push_back(i * 10 + j);
				placeLeft++;
			}
		}
	}
}

void Print()
{
	cout << endl;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			cout << visited[i][j] << " ";
		}cout << endl;
	}cout << endl;
}


int PlacePaper(int a, int b, int id)
{
	int fill = 0;
	if (!(a + id <= 10 && b + id <= 10)) { return -2; }
	for (int i = a; i < a + id; i++)
	{
		for (int j = b; j < b + id; j++)
		{
			if (Map[i][j] == 1 && visited[i][j] == 0)
			{
				visited[i][j] = 1;
				fill++; continue;
			}
			return -1;
		}
	}
	return fill;
}




void DFS(int idx, int paperUsed, int cnt, vector<int> paper)
{
	if (cnt == placeLeft)
	{
		Ans = min(Ans, paperUsed);
		return;
	}

	for (int i = idx; i < 100; i++)
	{
		int a = i / 10; int b = i % 10;
		if (Map[a][b] == 0 || visited[a][b] == 1) { continue; }
		int v_cp[10][10];
		memcpy(v_cp, visited, sizeof(v_cp));
		bool setPaper = false;
		for (int siz = 5; siz >= 1; siz--)
		{
			if (paper[siz - 1] == 0) { continue; }
			int p_num = PlacePaper(a, b, siz);
			if (p_num == -2)
			{
				continue;
			}
			if (p_num == -1)
			{
				memcpy(visited, v_cp, sizeof(v_cp));
				continue;
			}
			setPaper = true;
			paper[siz - 1]--;
			DFS(i, paperUsed + 1, cnt + p_num, paper);
			memcpy(visited, v_cp, sizeof(v_cp));
			paper[siz - 1]++;
		}
		if (setPaper) { return; }
	}
}

int main()
{
	Input();
	vector<int> paper{ 5,5,5,5,5 };
	DFS(0, 0, 0, paper);
	if (Ans == 99999)
		Ans = -1;
	cout << Ans;

}