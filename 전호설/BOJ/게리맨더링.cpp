#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int N;
int Map[50][50];
int dM[50][50];
int d1; int d2; int x; int y;
int Ans = 9999999;
void input()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> Map[i][j];
		}
	}
}

void divideF(int x, int y, int d1, int d2)
{
	for (int i = 0; i <= d1; i++)
	{
		dM[x + i][y - i] = 5;
	}
	for (int i = 0; i <= d2; i++)
	{
		dM[x + i][y + i] = 5;
	}
	for (int i = 0; i <= d2; i++)
	{
		dM[x + d1 + i][y - d1 + i] = 5;
	}
	for (int i = 0; i <= d1; i++)
	{
		dM[x + d2 + i][y + d2 - i] = 5;
	}
	for (int i = 0; i < N; i++)
	{
		bool check = false;
		for (int j = 0; j < N; j++)
		{
			if (i == x && j == y) { continue; }
			if (i == x + d1 + d2 && j == y - d1 + d2) { continue; }
			if (dM[i][j] == 5 && check == false)
			{
				check = true;
			}
			else if (check&&dM[i][j] != 5)
			{
				dM[i][j] = 5;
			}
			else if (check&&dM[i][j] == 5)
			{
				check = false;
			}
		}

	}

}

void divideA(int x, int y, int d1, int d2)
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (dM[i][j] == 5) { continue; }
			if ((i >= 0 && i < x + d1) && (j >= 0 && j <= y))
			{
				dM[i][j] = 1;
			}
			else if ((i >= 0 && i <= x + d2) && (j > y&&j < N))
			{
				dM[i][j] = 2;
			}
			else if ((i >= x + d1 && i < N) && (j >= 0 && j < y - d1 + d2))
			{
				dM[i][j] = 3;
			}
			else if ((i > x + d2 && i < N) && (j >= y - d1 + d2 && j < N))
			{
				dM[i][j] = 4;
			}
		}
	}
}



void makeNum()
{
	for (int d1 = 1; d1 < N; d1++)
	{
		for (int d2 = 1; d2 < N; d2++)
		{
			for (int x = 0; x < N; x++)
			{
				for (int y = 0; y < N; y++)
				{
					if (x + d1 + d2 >= N) { continue; }
					if (!((0 <= y - d1) && (y + d2 < N))) { continue; }
					memset(dM, 0, sizeof(dM));
					divideF(x, y, d1, d2);
					divideA(x, y, d1, d2);
					int MAX = -1; int MIN = 999999;
					int goo[5]; memset(goo, 0, sizeof(goo));
					for (int i = 0; i < N; i++)
					{
						for (int j = 0; j < N; j++)
						{
							goo[dM[i][j] - 1] += Map[i][j];
						}
					}

					for (int i = 0; i < 5; i++)
					{
						MAX = max(MAX, goo[i]);
						MIN = min(MIN, goo[i]);
					}
					Ans = min(Ans, MAX - MIN);

				}
			}
		}
	}
}

int main()
{
	input();
	makeNum();
	cout << Ans;
	/*divideF(1, 4, 3, 2);
	divideA(1, 4, 3, 2);*/

}