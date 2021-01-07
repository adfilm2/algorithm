#include <iostream>
#include <deque>
#include <cstring>
using namespace std;

struct ball {
	int r;
	int c;
	int m;
	int s;
	int d;
	int exD=-1;
	int num = 1;

};
int N, M, K;
deque<ball> fireBall;
int Map[50][50]; //map 에담기는정보 -> 가장먼저 도달한 fireball
int dir[8][2] = { {-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1},{-1,-1} };
int Ans;
void casting()
{
	memset(Map, 0, sizeof(Map));
	int len = fireBall.size();
	for (int i = 0; i < len; i++)
	{
		int newA = fireBall[i].r + (dir[fireBall[i].d][0] * (fireBall[i].s%N));
		int newB = fireBall[i].c + (dir[fireBall[i].d][1] * (fireBall[i].s%N));
		if (newA < 0) { newA += N; }
		if (newB < 0) { newB += N; }
		if (newA >= N) { newA -= N; }
		if (newB >= N) { newB -= N; }
		if (Map[newA][newB] == 0)
		{
			fireBall[i].r = newA;
			fireBall[i].c = newB;
			Map[newA][newB] = i + 1;
		}
		else
		{
			int tar = Map[newA][newB] - 1; // 이 tar에 합친다. tar이먼저온 fireball
			fireBall[tar].s += fireBall[i].s;
			fireBall[tar].m += fireBall[i].m;
			fireBall[tar].num++;
			if (fireBall[tar].exD == -1) { fireBall[tar].exD = 0; }
			if (fireBall[tar].exD == 0)
			{
				if (fireBall[tar].d % 2 != fireBall[i].d % 2)
				{
					fireBall[tar].exD = 1;
				}
			}
			fireBall.erase(fireBall.begin() + i); //합쳐진 파이어볼은 삭제
			i--; len--;
		}
	}
}

void explode()
{
	int len = fireBall.size();
	for (int i = 0; i < len; i++)
	{
		if (fireBall[i].exD >= 0)
		{
			if (fireBall[i].m / 5 > 0)
			{
				
				for (int j = 0; j < 4; j++)
				{
					int Dir = fireBall[i].exD + 2 * j;
					ball temp;
					temp.r = fireBall[i].r;
					temp.c = fireBall[i].c;
					temp.m = fireBall[i].m / 5;
					temp.s = fireBall[i].s / fireBall[i].num;
					temp.d = Dir;
					fireBall.push_back(temp);
				}
			}
			fireBall.erase(fireBall.begin() + i);
			len--; i--;
		}
	}
}

int main()
{
	cin >> N >> M >> K;
	for (int i = 0; i < M; i++)
	{
		ball temp;
		cin >> temp.r >> temp.c >> temp.m >> temp.s >> temp.d;
		temp.r--; temp.c--;
		fireBall.push_back(temp);
	}
	for (int i = 0; i < K; i++)
	{
		casting();
		explode();
	}
	int len = fireBall.size();
	for (int i = 0; i < len; i++)
	{
		Ans += fireBall[i].m;
	}

	cout << Ans;
}