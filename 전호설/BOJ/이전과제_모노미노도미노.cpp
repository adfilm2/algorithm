#include <iostream>
#include <cstring>
using namespace std;

int Map[2][6][4];
int N;
int score;

int Count()
{
	int n = 0;

	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (Map[1][i][j] == 1) { n++; }
			if (Map[0][i][j] == 1) { n++; }
		}
	}
	return n;
}


void Print()
{
	int n = 0;
	cout << endl;
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			cout << Map[0][i][j] << " ";
		}
		cout << "         ";
		for (int j = 0; j < 4; j++)
		{
			cout << Map[1][i][j] << " ";
		}cout << endl;
	}cout << endl;

}

void Clear(int idx) //연한 칸 연산
{
	int num = 0;
	for (int i = 0; i <= 1; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (Map[idx][i][j] == 0) { continue; }
			num++; break;
		}
	}
	for (int i = 5; i >= num; i--)
	{
		for (int j = 0; j < 4; j++)
		{
			Map[idx][i][j] = Map[idx][i - num][j];
		}
	}
	for (int i = 0; i < num; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Map[idx][i][j] = 0;
		}
	}
}

void Clear2(int idx) //합쳐진놈들
{
	bool chk = false;
	for (int i = 2; i < 6; i++)
	{
		if (!(Map[idx][i][0] == 1 && Map[idx][i][1] == 1 && Map[idx][i][2] == 1 && Map[idx][i][3] == 1))
		{
			continue;
		}
		chk = true; score++;
		for (int j = i; j > 0; j--)
		{
			for (int k = 0; k < 4; k++)
			{
				Map[idx][j][k] = Map[idx][j - 1][k];
			}
		}
		for (int j = 0; j < 4; j++)
		{
			Map[idx][0][j] = 0;
		}
	}
}

void Move(int t, int idx, int loc)
{
	if (t == 1)
	{
		int tar = 5;
		for (int i = 2; i < 6; i++)
		{
			if ((Map[idx][i][loc] == 0)) { continue; }
			tar = i - 1;
			break;
		}
		Map[idx][tar][loc] = 1;
		Clear2(idx); // 먼저 삭제되는놈 체크
		Clear(idx);
	}
	else if (t == 2)
	{
		int tar = 5;
		for (int i = 2; i < 6; i++)
		{
			if ((Map[idx][i][loc] == 0 && Map[idx][i][loc + 1] == 0)) { continue; }
			tar = i - 1;
			break;
		}
		Map[idx][tar][loc] = 1; Map[idx][tar][loc + 1] = 1;
		Clear2(idx); // 먼저 삭제되는놈 체크
		Clear(idx);
	}
	else
	{
		int tar = 4;
		for (int i = 2; i < 6; i++)
		{
			if ((Map[idx][i][loc] == 0)) { continue; }
			tar = i - 2;
			break;
		}
		Map[idx][tar][loc] = 1; Map[idx][tar + 1][loc] = 1;
		Clear2(idx); // 먼저 삭제되는놈 체크
		Clear(idx);

	}
	//Print();
}

int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		int t, a, b;
		cin >> t >> a >> b;
		Move(t, 0, b);
		if (t == 2) { t = 3; }
		else if (t == 3) { t = 2; }
		Move(t, 1, a);
	}
	cout << score << endl << Count();



}