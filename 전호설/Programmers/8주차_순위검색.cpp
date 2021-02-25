#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
map<string, vector<int>> Hash;
int len;
vector<vector<string>> Parsed;

void Parsing(vector<string> info)
{
	for (int i = 0; i < len; i++)
	{
		vector<string> temp;
		auto idx = info[i].find(' ');
		string t = info[i].substr(0, idx);
		temp.push_back(t);
		auto n_idx = info[i].find(' ', idx + 1);
		t = info[i].substr(idx + 1, (n_idx - idx - 1));
		temp.push_back(t);
		idx = n_idx;
		n_idx = info[i].find(' ', idx + 1);
		t = info[i].substr(idx + 1, (n_idx - idx - 1));
		temp.push_back(t);
		idx = n_idx;
		n_idx = info[i].find(' ', idx + 1);
		t = info[i].substr(idx + 1, (n_idx - idx - 1));
		temp.push_back(t);
		idx = n_idx;
		n_idx = info[i].find(' ', idx + 1);
		t = info[i].substr(idx + 1, (n_idx - idx - 1));
		temp.push_back(t);
		Parsed.push_back(temp);
	}
}

void DFS(int len, string str, int idx, int cnt, vector<string> target)
{
	if (cnt == len)
	{
		Hash[str].push_back(atoi(target[4].c_str()));
	}
	for (int i = idx + 1; i < 4; i++)
	{
		DFS(len, str + target[i], i, cnt + 1, target);
	}
}


vector<int> solution(vector<string> info, vector<string> query) {
	vector<int> answer;
	len = info.size();
	Parsing(info);
	for (int i = 0; i < len; i++)
	{
		Hash[""].push_back(atoi(Parsed[i][4].c_str()));
	}
	for (int i = 0; i < len; i++)
	{
		for (int j = 1; j <= 4; j++)
		{
			DFS(j, "", -1, 0, Parsed[i]);
		}
	}

	int len2 = query.size();
	for (int i = 0; i < len2; i++)
	{
		string tmp = "";
		string tmp2 = "";
		int strl = query[i].size();
		for (int j = 0; j < strl; j++)
		{
			if (query[i][j] == ' ' || query[i][j] == '-') { continue; }
			if (query[i][j] == 'a'&&query[i][j + 1] == 'n') { j += 3; continue; }
			if (query[i][j] >= '0'&&query[i][j] <= '9')
			{
				tmp2 += query[i][j];
			}
			else
			{
				tmp += query[i][j];
			}
		}
		int num = atoi(tmp2.c_str());
		int ans = 0;
		int l = Hash[tmp].size();
		for (int j = 0; j < l; j++)
		{
			if (Hash[tmp][j] >= num) { ans++; }
		}
		answer.push_back(ans);
	}
	return answer;
}