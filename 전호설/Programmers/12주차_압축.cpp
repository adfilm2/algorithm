#include <string>
#include <vector>
#include <iostream>
#include <map>
using namespace std;

map<string, int> Hash;
int idx = 27;
vector<int> answer;
void SetHash()
{
	for (int i = 'A'; i <= 'Z'; i++)
	{
		string t = "";
		t += (char)i;
		Hash[t] = i - 64;
	}
}

void LZW(string msg)
{
	int len = msg.size();
	int ptrPlus = 0;
	for (int i = 0; i < len; i += ptrPlus)
	{
		ptrPlus = 0;
		int size = 1;
		int num;
		string newKey;
		while (i + size <= len)
		{
			string cmpStr = msg.substr(i, size);
			if (Hash[cmpStr] == 0)
			{
				newKey = cmpStr;
				break;
			}
			num = Hash[cmpStr];
			size++;
			ptrPlus++;
		}
		answer.push_back(num);
		Hash[newKey] = idx;
		idx++;
	}
}



vector<int> solution(string msg) {

	SetHash();
	LZW(msg);
	return answer;
}