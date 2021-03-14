#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
vector<string> L;
int p_time;
int a_time;
int ad[360000];
void Parsing(string play, string adv)
{
	int h = atoi(play.substr(0, 2).c_str());
	int m = atoi(play.substr(3, 2).c_str());
	int s = atoi(play.substr(6, 2).c_str());
	int t = h * 3600 + m * 60 + s;
	p_time = t;
	h = atoi(adv.substr(0, 2).c_str());
	m = atoi(adv.substr(3, 2).c_str());
	s = atoi(adv.substr(6, 2).c_str());
	t = h * 3600 + m * 60 + s;
	a_time = t;
	int len = L.size();
	for (int i = 0; i < len; i++)
	{
		int h = atoi(L[i].substr(0, 2).c_str());
		int m = atoi(L[i].substr(3, 2).c_str());
		int s = atoi(L[i].substr(6, 2).c_str());
		int from = h * 3600 + m * 60 + s;
		h = atoi(L[i].substr(9, 2).c_str());
		m = atoi(L[i].substr(12, 2).c_str());
		s = atoi(L[i].substr(15, 2).c_str());
		int to = h * 3600 + m * 60 + s;
		for (int i = from; i < to; i++)
		{
			ad[i]++;
		}
	}
}

string findAns(int ANS)
{
	string answer = "";
	int h = ANS / 3600; ANS -= h * 3600;
	int s = ANS % 60; ANS -= s;
	int m = ANS / 60;
	if (h < 10) { answer += '0'; }
	answer += (to_string(h) + ':');
	if (m < 10) { answer += '0'; }
	answer += (to_string(m) + ':');
	if (s < 10) { answer += '0'; }
	answer += to_string(s);
	return answer;
}



string solution(string play_time, string adv_time, vector<string> logs) {
	L = logs;
	Parsing(play_time, adv_time);
	long long CMP = 0;
	long long MCMP = 0;
	int ANS = 0;
	int idx = 0;
	for (int i = 0; i < a_time; i++)
	{
		CMP += ad[i];
		MCMP = CMP;
	}
	int front = 0;
	int rear = a_time - 1;
	while (rear < p_time)
	{
		CMP -= ad[front];
		front++; rear++;
		CMP += ad[rear];
		if (CMP > MCMP)
		{
			MCMP = CMP;
			ANS = front;
		}
	}
	string answer = findAns(ANS);
	return answer;
}