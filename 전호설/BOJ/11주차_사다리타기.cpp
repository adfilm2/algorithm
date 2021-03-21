#include <iostream>
using namespace std;
int N, M, H;

int Map[50][50];
int dir[2][2] = { {0,1},{0,-1} };
int ANS = -1;
int idx;

int LadderMove(int num)
{
	int A = 0; int B = num;
	while (1)
	{
		if (Map[A][B] == 0)
		{
			A++;
			if (A == H) { break; }
		}
		else if (Map[A][B] > 0)
		{
			for (int i = 0; i < 2; i++)
			{
				int newA = A; int newB = B + dir[i][1];
				if (!(newA >= 0 && newA < H&&newB >= 0 && newB < N)) { continue; }
				if (Map[newA][newB] != Map[A][B]) { continue; }
				A = newA + 1; B = newB; break;
			}
			if (A == H) { break; }
		}
	}
	return B;
}

void Input()
{
	cin >> N >> M >> H;
	for (int i = 1; i <= M; i++)
	{
		int from;  int loc;
		cin >> loc >> from;
		from--; loc--;
		Map[loc][from] = i;
		Map[loc][from + 1] = i;
	}
	idx = M + 1;
}

void Print()
{
	cout << endl;
	for (int i = 0; i < H; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cout << Map[i][j] << " ";
		}cout << endl;

	}cout << endl;

}


void DFS(int num, int tar, int id)
{
	if (ANS != -1) { return; }
	if (num == tar)
	{
		//Print();
		bool chk = true;
		for (int i = 0; i < N; i++)
		{
			if (i == LadderMove(i)) { continue; }
			chk = false; break;
		}
		if (chk) { ANS = tar; }
		return;
	}
	for (int i = id; i < (N*H - 1); i++)
	{
		int A = i / N; int B = i % N;
		if (Map[A][B] != 0) { continue; }
		if (!(B + 1 < N&&Map[A][B + 1] == 0)) { continue; }
		Map[A][B] = idx;
		Map[A][B + 1] = idx;
		idx++;
		DFS(num + 1, tar, id);
		idx--;
		Map[A][B] = 0;
		Map[A][B + 1] = 0;
	}
}


int main()
{
	Input();

	for (int i = 0; i <= 3; i++)
	{
		DFS(0, i, 0);
	}
	cout << ANS;

}