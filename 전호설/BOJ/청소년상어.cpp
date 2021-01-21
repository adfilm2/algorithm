#include <iostream>
#include <deque>
#include <map>
#include <cstring>
#include <algorithm>
using namespace std;

int dir[8][2] = { {-1,0},{-1,-1},{0,-1},{1,-1},{1,0},{1,1},{0,1},{-1,1} };
int ANS;

struct fish {
	int num=0;
	int dir=0;
};
fish Map[4][4];
map<int, int> Hash;


void FishMove()
{
	for (int n = 1; n <= 16; n++)
	{
		if (Hash[n] == -1) { continue; }
		int i = Hash[n] / 4; int j = Hash[n] % 4;
		//cout << n << "번 물고기 : [" << i << "," << j << "] 방향:" << Map[i][j].dir << endl;
		if (Map[i][j].num <= 0) { continue; }
		for (int k = 0; k < 8; k++)
		{
			if (Map[i][j].dir == 8) { Map[i][j].dir = 0; }
			int newA = i + dir[Map[i][j].dir][0];
			int newB = j + dir[Map[i][j].dir][1];
			if (newA >= 0 && newA < 4 && newB >= 0 && newB < 4 && Map[newA][newB].num >=0)
			{
				int t = Hash[n];
				Hash[n] = newA*4+newB;
				Hash[Map[newA][newB].num] = t;
				int D = Map[i][j].dir;
				fish temp = Map[i][j];
				Map[i][j] = Map[newA][newB];
				Map[newA][newB] = temp;
				break;
			}
			Map[i][j].dir++;
		}
	}
}
void DFS(int a, int b,int d, int n)
{	
	fish Map_cp[4][4];
	memcpy(Map_cp, Map, sizeof(Map));
	map<int, int>Hash_cp=Hash;
	int cnt=0;
	for (int i = 1; i <= 3; i++)
	{
		int newA = a + dir[d][0]*i;
		int newB = b + dir[d][1] * i;
		if (newA >= 0 && newA < 4 && newB >= 0 && newB < 4 && Map[newA][newB].num>0)
		{	
			Hash[Map[a][b].num] = -1;
			Map[a][b].num = 0;
			int food = n + Map[newA][newB].num;
			int newDir = Map[newA][newB].dir;
			Hash[Map[newA][newB].num] = -1;
			Map[newA][newB].num = -1;
			FishMove();
			DFS(newA, newB,newDir,food);
			memcpy(Map, Map_cp, sizeof(Map));
			Hash = Hash_cp;
			cnt++;
		}
	}
	if (cnt == 0)
	{
		ANS = max(ANS, n);
		return;
	}

}

int main()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			int fnum; int fdir; 
			cin >> fnum >> fdir; fdir--;
			Hash[fnum] = i * 4 + j;
			Map[i][j].num = fnum;
			Map[i][j].dir = fdir;
		}
	}
	//print();
	ANS = Map[0][0].num;
	Hash[Map[0][0].num] = -1;
	Map[0][0].num = -1;
	
	FishMove();
	DFS(0, 0, Map[0][0].dir,ANS);
	cout << ANS;


}