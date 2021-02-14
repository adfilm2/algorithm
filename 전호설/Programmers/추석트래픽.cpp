#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
vector<string> L;
int ANS = -1;
struct trafic
{
	int f;
	int t;
};
vector<trafic> log;
void parshing(string t)
{
	string h = "";
	if (t[11] != '0') { h += t[11]; }
	h += t[12];
	string m = "";
	if (t[14] != '0') { m += t[14]; }
	m += t[15];
	string s = "";
	if (t[17] != '0') { s += t[17]; }
	for (int i = 18; i <= 22; i++)
	{
		s += t[i];
	}
	long long to = (atof(h.c_str()) * 3600 + atof(m.c_str()) * 60 + atof(s.c_str())) * 1000;
	int len = t.size() - 24;
	string t2 = t.substr(24, len);
	long long from = (to - (atof(t2.c_str()) * 1000) + 1);
	trafic T;
	T.f = from;
	T.t = to;
	log.push_back(T);
}

int solution(vector<string> lines) {
	int len = lines.size();
	L = lines;
	for (int i = 0; i < len; i++)
	{
		parshing(lines[i]);
	}
	len = log.size();
	for (int i = 0; i < len; i++)
	{
		int s = log[i].f;
		int e = s + 999;
		int num = 0;
		for (int j = 0; j < len; j++)
		{
			if (!((log[j].f <= e && log[j].f >= s) || (log[j].t <= e && log[j].t >= s) || (log[j].f <= s && log[j].t >= e))) { continue; }
			num++;
		}
		ANS = max(ANS, num);
		s = log[i].t;
		e = s + 999;
		num = 0;
		for (int j = 0; j < len; j++)
		{
			if (!((log[j].f <= e && log[j].f >= s) || (log[j].t <= e && log[j].t >= s) || (log[j].f <= s && log[j].t >= e))) { continue; }
			num++;
		}
		ANS = max(ANS, num);
	}
	int answer = 0;
	return ANS;
}