#include <string>
#include <vector>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int lenW;
int lenD;
int ANS = -1;
int fix[15];
int N;
vector<int> W;
vector<int> D;

int Move(int from, int to)
{
	int rep = 0;
	for (int i = 0; i < lenW; i++)
	{
		if (fix[i] == 1)
			continue;
		if (!((W[i] >= from && W[i] <= to) || (W[i] + N >= from && W[i] + N <= to)))
			continue;
		rep++;
		fix[i] = 1;
	}
	return rep;
}

void DFS(int who, int f, int num)
{
	if (num >= ANS && ANS != -1) { return; }
	if (who < 0) { return; }
	int fix_cp[15];
	memcpy(fix_cp, fix, sizeof(fix));
	for (int i = 0; i < lenW; i++)
	{
		if (fix[i] == 1) { continue; }
		int from = W[i];
		int to = W[i] + D[who];
		int rep = f + Move(from, to);
		if (rep == lenW)
		{
			if (ANS == -1)
			{
				ANS = num; return;
			}
			else
			{
				ANS = min(ANS, num); return;
			}
		}
		DFS(who - 1, rep, num + 1);
		memcpy(fix, fix_cp, sizeof(fix));
	}

}

int solution(int n, vector<int> weak, vector<int> dist) {
	lenW = weak.size();
	lenD = dist.size();
	W = weak; D = dist;
	N = n;
	DFS(lenD - 1, 0, 1);
	return ANS;
}