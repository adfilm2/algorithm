#include <string>
#include <vector>
#include <iostream>
#include <cstring>
using namespace std;
char MAP[30][30];
int M; int N;
int ANS;
char Map_cp[30][30];
void print()
{
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << MAP[i][j] << " ";
		}cout << endl;

	}cout << endl;
}

void Break(int a, int b)
{
	for (int i = a; i <= a + 1; i++)
	{
		for (int j = b; j <= b + 1; j++)
		{
			if (Map_cp[i][j] == 'd') { continue; }
			Map_cp[i][j] = 'd'; ANS++;
		}
	}
}

bool Destroy()
{
	bool chk = false;
	memcpy(Map_cp, MAP, sizeof(MAP));
	for (int i = 0; i < M - 1; i++)
	{
		for (int j = 0; j < N - 1; j++)
		{
			if (!(MAP[i][j] != 'd'&&MAP[i][j] == MAP[i][j + 1] && MAP[i][j] == MAP[i + 1][j] && MAP[i][j] == MAP[i + 1][j + 1]))
			{
				continue;
			}
			chk = true;
			Break(i, j);
		}
	}
	memcpy(MAP, Map_cp, sizeof(MAP));
	return chk;
}

void FallDown()
{
	for (int j = 0; j < N; j++)
	{
		int fallLoc = M - 1;
		for (int i = M - 1; i >= 0; i--)
		{
			if (MAP[i][j] != 'd'&&i == fallLoc)
			{
				fallLoc--;
			}
			else if (MAP[i][j] != 'd'&&i != fallLoc)
			{
				MAP[fallLoc][j] = MAP[i][j];
				MAP[i][j] = 'd';
				fallLoc--;
			}
		}
	}
}


int solution(int m, int n, vector<string> board) {
	int answer = 0;
	M = m; N = n;
	for (int i = 0; i < M; i++)
	{
		for (int j = 0; j < N; j++)
		{
			MAP[i][j] = board[i][j];
		}
	}
	while (1)
	{
		if (Destroy())
		{
			print();
			FallDown();
			print();
		}
		else { break; }
	}


	return ANS;
}