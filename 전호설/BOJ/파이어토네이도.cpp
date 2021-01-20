#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int N, Q;
int Map[100][100];
int visited[100][100];
int magicSiz;
int Ans1;
int len; // map 한번길이
int dir[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };
int Ans2 = 0; //가장큰 덩어리
int sizCmp = 1;

void storm(int a, int b, int siz)
{
	int temp[100][100];
	for (int i = 0; i < siz; i++)
	{
		for (int j = 0; j < siz; j++)
		{
			temp[i][j] = Map[a+siz - 1 - j][b+i];
		}
	}
	for (int i = 0; i <  siz; i++)
	{
		for (int j = 0; j <  siz; j++)
		{
			Map[a+i][b+j] = temp[i][j];
		}
	}
}
void melt()
{
	int Map_cp[100][100];
	memcpy(Map_cp, Map, sizeof(Map));
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len; j++)
		{
			int chk = 0;
			for (int k = 0; k < 4; k++)
			{
				int newA = i + dir[k][0]; int newB = j + dir[k][1];
				if (newA >= 0 && newA < len&&newB >= 0 && newB < len)
				{
					if (Map[newA][newB] > 0)
					{
						chk++;
					}
				}
			}
			if (chk < 3&&Map[i][j]>0)
			{
				Map_cp[i][j]--;
			}
		}
	}
	memcpy(Map, Map_cp, sizeof(Map));
}

void DFS(int a, int b)
{
	visited[a][b] = 1;
	for (int d = 0; d < 4; d++)
	{
		int newA = a + dir[d][0];
		int newB = b + dir[d][1];
		if (newA >= 0 && newA < len&&newB >= 0 && newB < len)
		{
			if (visited[newA][newB] == 0 && Map[newA][newB] > 0)
			{
				sizCmp++;
				DFS(newA, newB);
			}
		}

	}
}

int main()
{
	cin >> N >> Q;
	len = pow(2, N);
	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len; j++)
		{
			cin >> Map[i][j];
		}
	}
	for (int ord = 0; ord < Q; ord++)
	{
		cin >> magicSiz;
		magicSiz = pow(2, magicSiz);
		for (int i = 0; i < len; i += magicSiz)
		{
			for (int j = 0; j < len; j += magicSiz)
			{
				storm(i, j, magicSiz);
			}
		}
		melt();
	}

	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len; j++)
		{
			if (Map[i][j] > 0 && visited[i][j] == 0)
			{
				sizCmp = 1;
				DFS(i, j);
				Ans2 = max(Ans2, sizCmp);
			}

		}
	}



	for (int i = 0; i < len; i++)
	{
		for (int j = 0; j < len; j++)
		{
			Ans1 += Map[i][j];
		}
	}
	cout << Ans1<<endl;
	cout << Ans2;
}