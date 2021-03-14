#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
int N, K;
int dir[4][2] = { {0,1},{0,-1},{-1,0},{1,0} };
int Time = 0;
int Ans = -1;
int Map[13][13];

struct horse {
	int a;
	int b;
	int dir;
	vector<int> ride;
};
vector<horse> horses;


void Input()
{
	cin >> N >> K;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> Map[i][j];
		}
	}
	for (int i = 0; i < K; i++)
	{
		horse temp;
		cin >> temp.a >> temp.b >> temp.dir;
		temp.a--; temp.b--; temp.dir--; temp.ride.push_back(i);
		horses.push_back(temp);
	}
}


void RideSet(int newA, int newB, vector<int> family, int len)
{
	for (int i = 0; i < K; i++)
	{
		if (!(horses[i].a == newA && horses[i].b == newB)) { continue; }
		for (int j = 0; j < len; j++)
		{
			horses[i].ride.push_back(family[j]);
		}
		if (horses[i].ride.size() >= 4)
		{
			Ans = Time;
		}
	}
	for (int i = 0; i < len; i++)
	{
		horses[family[i]].a = newA;
		horses[family[i]].b = newB;
	}
}

vector<int> Swip(vector<int> family, int len)
{
	for (int i = len - 1; i >= 0; i--)
	{
		horses[family[i]].ride.clear();
		for (int j = i; j >= 0; j--)
		{
			horses[family[i]].ride.push_back(family[j]);
		}
	}
	reverse(family.begin(), family.end());
	return family;
}

void Action()
{
	for (int i = 0; i < K; i++)
	{
		int len = horses[i].ride.size();
		for (int j = 0; j < len; j++)
		{
			if (horses[i].a == horses[horses[i].ride[j]].a&&horses[i].b == horses[horses[i].ride[j]].b)
			{
				continue;
			}
			horses[i].ride.erase(horses[i].ride.begin() + j);
			j--; len--;
		}
		int newA = horses[i].a + dir[horses[i].dir][0];
		int newB = horses[i].b + dir[horses[i].dir][1];
		if (!(newA >= 0 && newA < N&&newB >= 0 && newB < N) || Map[newA][newB] == 2)
		{
			if (horses[i].dir % 2 == 0) { horses[i].dir++; }
			else { horses[i].dir--; }
			newA = horses[i].a + dir[horses[i].dir][0];
			newB = horses[i].b + dir[horses[i].dir][1];
		}
		if (!(newA >= 0 && newA < N&&newB >= 0 && newB < N) || Map[newA][newB] == 2) { continue; }
		if (Map[newA][newB] == 0)
		{
			RideSet(newA, newB, horses[i].ride, len);
			if (Ans != -1) { return; }
		}
		else if (Map[newA][newB] == 1)
		{
			RideSet(newA, newB, Swip(horses[i].ride, len), len);
			if (Ans != -1) { return; }
		}
	}
}



int main()
{
	Input();
	while (Ans == -1 && Time <= 1000)
	{
		Time++;
		Action();
	}
	cout << Ans;
}