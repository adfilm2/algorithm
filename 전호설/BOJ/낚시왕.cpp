#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
int R, C, M;
int Map[101][101];
int Map_cp[101][101];
int dir[4][2] = { {-1,0},{1,0},{0,1},{0,-1} };
int Ans;
struct shark
{
	int a; int b; int s; int d; int z;
};

vector<shark> sharks;
void input()
{
	cin >> R >> C >> M;
	for (int i = 0; i < M; i++)
	{
		int r, c, s, d, z; //(r, c)는 상어의 위치, s는 속력, d는 이동 방향, z는 크기
		cin >> r >> c >> s >> d >> z;
		r--; c--; d--;
		Map[r][c] = z;
		shark temp; temp.a = r; temp.b = c; temp.s = s; temp.d = d; temp.z = z;
		sharks.push_back(temp);
	}
}

void moveShark(int idx)
{
	int newA = sharks[idx].a + (dir[sharks[idx].d][0] * sharks[idx].s);
	int newB = sharks[idx].b + (dir[sharks[idx].d][1] * sharks[idx].s);
	while (!(newA >= 0 && newA < R&&newB >= 0 && newB < C))
	{
		if (newA >= R)
		{
			int dc = newA - (R - 1);
			newA = (R - 1) - dc;
			sharks[idx].d = 0;
		}
		else if (newA < 0)
		{
			newA *= -1;
			sharks[idx].d = 1;
		}
		else if (newB >= C)
		{
			int dc = newB - (C - 1);
			newB = (C - 1) - dc;
			sharks[idx].d = 3;
		}
		else if (newB < 0)
		{
			newB *= -1;
			sharks[idx].d = 2;
		}
	}
	sharks[idx].a = newA; sharks[idx].b = newB;
	Map_cp[newA][newB] = max(Map_cp[newA][newB], sharks[idx].z);
	//cout << "sharks" << idx << "  :  " << newA << " , " << newB << " / " << sharks[idx].z << endl;
}


void getToDaze(int loc)
{
	for (int i = 0; i < R; i++)
	{
		if (Map[i][loc] > 0)
		{
			Ans += Map[i][loc];// 상어 겟또다제!
			Map[i][loc] = 0;
			break;
		}
	}
	//cout << "Ans: " << Ans << endl;
	memset(Map_cp, 0, sizeof(Map_cp));
	for (int i = 0; i < sharks.size(); i++)
	{
		if (Map[sharks[i].a][sharks[i].b] == 0)
		{
			sharks.erase(sharks.begin() + i);
			i--;
		}
		else
		{
			Map[sharks[i].a][sharks[i].b] = 0;
			moveShark(i);
		}
	}
	//cout << endl;
	for (int i = 0; i < sharks.size(); i++)
	{
		if (Map_cp[sharks[i].a][sharks[i].b] != sharks[i].z)
		{
			//cout << "sharks" << i << "  killed!  "<< endl;
			sharks.erase(sharks.begin() + i);
			i--;
		}
	}
	memcpy(Map, Map_cp, sizeof(Map));
}


int main()
{
	input();
	for (int t = 0; t < C; t++)
	{
		getToDaze(t);
	}
	cout << Ans;
}