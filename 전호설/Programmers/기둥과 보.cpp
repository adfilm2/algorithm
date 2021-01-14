#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

int MapGi[101][101];
int MapBo[101][101];
vector<vector<int>> answer;
int N;
bool CheckGi(int a, int b) //열!행!
{
	if (b == 0 || MapGi[b - 1][a] == 1 || MapBo[b][a] == 1 || MapBo[b][a - 1] == 1)
	{
		return true;
	}
	return false;
}
bool CheckBo(int a, int b)
{
	if (MapGi[b - 1][a] == 1 || MapGi[b - 1][a + 1] == 1 || (MapBo[b][a - 1] == 1 && MapBo[b][a + 1] == 1))
	{
		return true;
	}
	return false;
}

void Build(int a, int b, int what) //가로, 세로!!!!
{
	if (what == 0)
	{
		if (!CheckGi(a, b)) { return; }
		MapGi[b][a] = 1;
	}
	else
	{
		if (!CheckBo(a, b)) { return; }
		MapBo[b][a] = 1;
	}

}

bool IsPossible()
{
	for (int i = 0; i <= N; i++)
	{
		for (int j = 0; j <= N; j++)
		{
			if (MapGi[i][j] == 1 && !CheckGi(j, i))
			{
				return false;
			}
			else if (MapBo[i][j] == 1 && !CheckBo(j, i))
			{
				return false;
			}
		}
	}
	return true;
}

void Destroy(int a, int b, int what)
{
	if (what == 0)
	{
		MapGi[b][a] = 0;
		if (IsPossible()) { return; }
		MapGi[b][a] = 1;
	}
	else
	{
		MapBo[b][a] = 0;
		if (IsPossible()) { return; }
		MapBo[b][a] = 1;
	}
}
void print(int n)
{
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			cout << MapGi[i][j] << " ";
		}cout << endl;
	}cout << endl;

	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			cout << MapBo[i][j] << " ";
		}cout << endl;
	}cout << endl;
}

vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
	int len = build_frame.size(); //열, 행, 기둥or보, 삭제or설치
	N = n;
	for (int i = 0; i < len; i++)
	{
		if (build_frame[i][3] == 1)
		{
			Build(build_frame[i][0], build_frame[i][1], build_frame[i][2]);
			// print(n);
		}
		else
		{
			Destroy(build_frame[i][0], build_frame[i][1], build_frame[i][2]);
			//print(n);
		}
	}
	for (int i = 0; i <= n; i++)
	{
		for (int j = 0; j <= n; j++)
		{
			if (MapGi[i][j] == 1)
			{
				vector<int> temp;
				temp.push_back(j);
				temp.push_back(i);
				temp.push_back(0);
				answer.push_back(temp);
			}
			if (MapBo[i][j] == 1)
			{
				vector<int> temp;
				temp.push_back(j);
				temp.push_back(i);
				temp.push_back(1);
				answer.push_back(temp);
			}
		}
	}
	//print(n);
	sort(answer.begin(), answer.end());

	return answer;
}