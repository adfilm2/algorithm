#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>
using namespace std;
vector<string> answer;
vector<string> O;
vector<int> C;
int favorite[10];
map<string, int> Hash;

void Comb(string origin, string temp, int idx, int tar)
{
	if (temp.size() == tar)
	{
		Hash[temp]++;
		favorite[tar] = max(favorite[tar], Hash[temp]);
		return;
	}
	int len = origin.size();
	for (int i = idx + 1; i < len; i++)
	{
		Comb(origin, temp + origin[i], i, tar);
	}
}


vector<string> solution(vector<string> orders, vector<int> course) {
	O = orders;
	C = course;
	int len = orders.size();
	int siz = C.size();
	for (int i = 0; i < len; i++)
	{
		sort(O[i].begin(), O[i].end());
	}
	for (int tar = 0; tar < siz; tar++) //코스길이
	{
		for (int i = 0; i < len; i++) // 사람들 주문한것
		{
			Comb(O[i], "", -1, C[tar]);//원래주문, 조합, 0부터, 코스길이     
		}
	}
	for (int tar = 0; tar < siz; tar++)
	{
		for (auto &x : Hash)
		{
			if (x.first.size() == C[tar] && x.second == favorite[C[tar]] && favorite[C[tar]] >= 2)
			{
				answer.push_back(x.first);
			}
		}
	}
	sort(answer.begin(), answer.end());
	return answer;
}