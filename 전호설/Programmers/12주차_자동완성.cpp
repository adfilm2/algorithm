#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;
map<string, string> Hash;
map<string, int>HashNum;

bool cmp(string a, string b)
{

	return a.size() < b.size();

}

int Learning(vector<string> words)
{
	int len = words.size();
	int num = 0;
	for (int i = 0; i < len; i++)
	{
		int wLen = words[i].size();
		string cmpStr = "";

		int siz;
		for (siz = 1; siz <= wLen; siz++)
		{
			cmpStr += words[i][siz - 1];
			if (Hash[cmpStr] != ""&&Hash[cmpStr] != "nope")
			{
				HashNum[Hash[cmpStr]]--;
				Hash[cmpStr] = "nope";
				continue;
			}
			if (Hash[cmpStr] == "nope") { continue; }
			Hash[cmpStr] = words[i];
			HashNum[words[i]]++;
			break;
		}
		for (int j = siz + 1; j <= wLen; j++)
		{
			cmpStr += words[i][j - 1];
			Hash[cmpStr] = words[i];
			HashNum[words[i]]++;
		}
	}

	for (int i = 0; i < len; i++)
	{
		int n = HashNum[words[i]] - 1;
		n = max(0, n);
		int wLen = words[i].size() - n;
		num += wLen;
	}
	return num;
}


int solution(vector<string> words) {
	sort(words.begin(), words.end(), cmp);
	int answer = Learning(words);
	return answer;
}