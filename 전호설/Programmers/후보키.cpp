#include <string>
#include <vector>
#include <map>
#include <iostream>
using namespace std;
int answer = 0;
int attLen;
vector<int> comb;
vector<int> m_comb; // 주어진키로 다시 조합을만든다
vector<vector<string>> R;
int len;
bool isMin = true;
map<string, int> Ckey;
bool Uniqueness()
{
	map<string, int> Hash;
	int keyLen = comb.size();
	for (int i = 0; i < len; i++)
	{
		string t = "";
		for (int j = 0; j < keyLen; j++)
		{
			t += R[i][comb[j]];
		}
		if (Hash[t] == 1) { return false; }
		Hash[t] = 1;
	}
	return true;
}


void Minimal(int idx, int mxsiz)
{
	if (!isMin) { return; }
	if (m_comb.size() == mxsiz)
	{
		string t = "";
		for (int j = 0; j < m_comb.size(); j++)
		{
			t += to_string(m_comb[j]);
		}
		if (Ckey[t] == 1) { isMin = false; return; }
		if (m_comb.size() == comb.size() && isMin)
		{
			answer++; Ckey[t] = 1; return;
		}
		return;
	}
	for (int i = idx + 1; i < comb.size(); i++)
	{
		m_comb.push_back(comb[i]);
		Minimal(i, mxsiz);
		m_comb.pop_back();
	}
}

void Combination(int num, int siz)
{
	if (comb.size() == siz)
	{
		if (!Uniqueness()) { return; }

		for (int i = 1; i <= comb.size(); i++)
		{
			for (int j = 0; j < comb.size(); j++)
			{
				m_comb.push_back(comb[j]);
				Minimal(j, i);
				m_comb.pop_back();
			}
		}
		isMin = true;
		return;
	}
	for (int i = num + 1; i < attLen; i++)
	{
		comb.push_back(i);
		Combination(i, siz);
		comb.pop_back();
	}
}

int solution(vector<vector<string>> relation) {
	R = relation;
	attLen = relation[0].size();
	len = R.size();
	for (int siz = 1; siz <= len; siz++)
	{
		for (int i = 0; i < attLen; i++)
		{
			comb.push_back(i);
			Combination(i, siz);
			comb.pop_back();
		}
	}
	return answer;
}