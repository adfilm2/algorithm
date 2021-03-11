#include <deque>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int visited[16];
int Map[4][4];
int dir[4][2] = { {-1,0},{0,1},{1,0},{0,-1} };
vector<int> Target;
int cnt = 0;
int answer = 99999;
struct point
{
	int a;
	int b;
	int num = 0;
};


void MapSet(vector<vector<int>> board, int r, int c)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			Map[i][j] = board[i][j];
			if (i == r && j == c) { continue; }
			if (Map[i][j] == 0) { continue; }
			Target.push_back(4 * i + j);
		}
	}
}

int CtrlMove(int A, int B, int d) // 한칸은 움직여야함...딱 붙어서 
{
	int newLoc = -1;
	for (int i = 0; i < 4; i++)
	{
		int newA = A + dir[d][0];
		int newB = B + dir[d][1];
		if (!(newA >= 0 && newA < 4 && newB >= 0 && newB < 4)) { break; }
		if (Map[newA][newB] != 0) { A = newA; B = newB; break; }
		A = newA; B = newB;
	}
	newLoc = A * 4 + B;
	return newLoc;
}


int Move(int A, int B, int tarA, int tarB, vector<int> C)
{
	int option = 0; //-> 이동만할떄.둘다있을때 뒤집는다.
	int visited[4][4];
	memset(visited, 0, sizeof(visited));
	visited[A][B] = 1;
	point temp; temp.a = A; temp.b = B;
	if (Map[A][B] > 0) { option = 1; temp.num++; }//카드가있군요 뒤집자
	//cout <<option<<"! "<< A << "," << B << " -> " << tarA << "," << tarB << " : ";
	deque<point> BFS; BFS.push_back(temp);
	while (!BFS.empty())
	{
		point t = BFS.front();
		BFS.pop_front();
		for (int d = 0; d < 4; d++)
		{
			int newA = t.a + dir[d][0];
			int newB = t.b + dir[d][1];
			if (!(newA >= 0 && newA < 4 && newB >= 0 && newB < 4)) { continue; }
			if (visited[newA][newB] == 1) { continue; }
			if (newA == tarA && newB == tarB)
			{
				t.num++;
				if (option == 1) {
					Map[A][B] = 0; Map[tarA][tarB] = 0;
					t.num++;
				}
				return (t.num);
			}
			point temp; temp.a = newA; temp.b = newB; temp.num = t.num + 1;
			visited[temp.a][temp.b] = 1;
			BFS.push_back(temp);
		}
		for (int d = 0; d < 4; d++)
		{
			int newLoc = CtrlMove(t.a, t.b, d);
			int newA = newLoc / 4;
			int newB = newLoc % 4;
			if ((newA == t.a&&newB == t.b)) { continue; }
			if (visited[newA][newB] == 1) { continue; }
			if (newA == tarA && newB == tarB)
			{
				t.num++;
				if (option == 1)
				{
					Map[A][B] = 0; Map[tarA][tarB] = 0;
					t.num++;
				}
				return (t.num);
			}
			point temp; temp.a = newA; temp.b = newB; temp.num = t.num + 1;
			visited[temp.a][temp.b] = 1;
			BFS.push_back(temp);
		}
	}
}





void Comb(vector<int> C, int siz, int tarSiz)
{
	if (siz == tarSiz + 1)
	{
		int Map_cp[4][4];
		memcpy(Map_cp, Map, sizeof(Map));
		int Ans = 0;
		for (int i = 0; i < tarSiz; i++) //초기위치포함하면 한개더많다!
		{
			int num = Move(C[i] / 4, C[i] % 4, C[i + 1] / 4, C[i + 1] % 4, C);
			Ans += num;
		}
		answer = min(answer, Ans);
		memcpy(Map, Map_cp, sizeof(Map));
		return;
	}
	for (int i = 0; i < tarSiz; i++)
	{
		if (visited[i] == 1) { continue; }
		if (!(Map[C[siz - 1] / 4][C[siz - 1] % 4] == 0 ||
			Map[C[siz - 1] / 4][C[siz - 1] % 4] == Map[Target[i] / 4][Target[i] % 4] ||
			Map[C[siz - 1] / 4][C[siz - 1] % 4] == Map[C[siz - 2] / 4][C[siz - 2] % 4])) {
			continue;
		}
		visited[i] = 1;
		C.push_back(Target[i]);
		Comb(C, siz + 1, tarSiz);
		C.pop_back();
		visited[i] = 0;
	}
}


int solution(vector<vector<int>> board, int r, int c) {
	vector<int> temp;
	int start = r * 4 + c;
	temp.push_back(start);
	MapSet(board, r, c);
	Comb(temp, 1, Target.size());
	return answer;
}