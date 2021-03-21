#include <iostream>
#include <vector>
using namespace std;
int Map[101][101];
vector<vector<int>> dragonCurve;
int dir[4][2] = { {0,1},{-1,0},{0,-1},{1,0} };
int N;
int A; int B;

void SetDragonCurve(int num)
{
	for (int i = 1; i <= num; i++)
	{
		dragonCurve[i] = dragonCurve[i - 1];
		int idx = dragonCurve[i - 1].size() - 1;
		for (int j = idx; j >= 0; j--)
		{
			int newDir = dragonCurve[i - 1][j] + 1;
			if (newDir == 4) { newDir = 0; }
			dragonCurve[i].push_back(newDir);
		}
	}
}

void SetMap(int a, int b, int num)
{
	int A = a; int B = b;
	int len = dragonCurve[num].size();
	Map[A][B] = 1;
	for (int i = 0; i < len; i++)
	{
		A = A + dir[dragonCurve[num][i]][0];
		B = B + dir[dragonCurve[num][i]][1];
		Map[A][B] = 1;
	}
}

int CalAns()
{
	int ans = 0;
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			if (!(Map[i][j] == 1 && Map[i][j + 1] == 1 && Map[i + 1][j] == 1 && Map[i + 1][j + 1] == 1)) { continue; }
			ans++;

		}
	}
	return ans;

}




int main()
{
	cin >> N;

	for (int i = 0; i < N; i++)
	{
		dragonCurve.assign(20, vector<int>());
		int a, b, d, g;
		cin >> a >> b >> d >> g;
		dragonCurve[0].push_back(d);
		SetDragonCurve(g);
		SetMap(b, a, g);
	}
	cout << CalAns();


}