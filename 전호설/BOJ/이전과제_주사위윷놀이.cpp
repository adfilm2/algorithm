#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct horse
{
	int startPos = 0;;
	int wMap = 0;
};
int Map[4][50] = { { 0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,32,34,36,38,40,0,}, //22
 {0,2,4,6,8,10,13,16,19,25,30,35,40,0},//14
 { 0,2,4,6,8,10,12,14,16,18,20,22,24,25,30,35,40,0}, //18
 { 0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,30,28,27,26,25,30,35,40,0 } };//24

horse horses[4];
int yut[10];
int Ans;
int debug;


bool ChkGoal(int i)
{
	if (horses[i].wMap == 0 && horses[i].startPos >= 22) { return true; }
	if (horses[i].wMap == 1 && horses[i].startPos >= 14) { return true; }
	if (horses[i].wMap == 2 && horses[i].startPos >= 18) { return true; }
	if (horses[i].wMap == 3 && horses[i].startPos >= 24) { return true; }
	return false;
}


void DFS(int cnt, int num)
{
	if (cnt == 10)
	{
		Ans = max(Ans, num);
		return;
	}
	for (int i = 0; i < 4; i++)
	{
		bool isC = false;
		if (ChkGoal(i)) { continue; }
		if (horses[i].wMap == 0 && horses[i].startPos == 5) { horses[i].wMap = 1; isC = true; }
		if (horses[i].wMap == 0 && horses[i].startPos == 10) { horses[i].wMap = 2; isC = true; }
		if (horses[i].wMap == 0 && horses[i].startPos == 15) { horses[i].wMap = 3; isC = true; }
		bool chk = true;
		for (int j = 0; j < 4; j++)
		{
			if (i == j) { continue; }
			if (ChkGoal(j)) { continue; }
			if ((horses[i].wMap == horses[j].wMap) && horses[i].startPos + yut[cnt] == horses[j].startPos)
			{
				chk = false; break;
			} //같은라인.. 같은pos...
			if (Map[horses[i].wMap][horses[i].startPos + yut[cnt]] == Map[horses[j].wMap][horses[j].startPos]) //두개의 값이 같을때는
			{
				int num = Map[horses[j].wMap][horses[j].startPos];
				if (num == 30 && (horses[i].wMap == 0 || horses[j].wMap == 0)) { continue; } //30일때는 0번루트, 1,2,3루트인경우존재
				if (num == 40 || num == 25 || num == 35 || num == 30)
				{
					chk = false; break;
				}
			}
		}
		if (!chk) { if (isC) { horses[i].wMap = 0; } continue; }
		horses[i].startPos += yut[cnt];
		DFS(cnt + 1, num + Map[horses[i].wMap][horses[i].startPos]);
		if (isC) { horses[i].wMap = 0; }
		horses[i].startPos -= yut[cnt];
	}
}
//cout << i << "번째 -> " << horses[i].wMap << " : " << horses[i].startPos <<"..."<< num + Map[horses[i].wMap][horses[i].startPos] <<endl;

int main()
{
	for (int i = 0; i < 10; i++)
	{
		cin >> yut[i];
	}
	DFS(0, 0);
	cout << Ans;

}