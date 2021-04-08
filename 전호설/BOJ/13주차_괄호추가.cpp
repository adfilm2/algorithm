#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
#include <cstdlib>
using namespace std;
int strLen;
string inputString;
int visited[100];
int Answer = -99999;

int CalNum(string express, int id)
{
	string temp = "";
	if (express[id] == '-') { temp += '-'; id++; }
	for (int i = id; i < express.size(); i++)
	{
		if (!(express[i] >= '0'&&express[i] <= '9')) { break; }
		temp += express[i];
	}
	return atoi(temp.c_str());
}



int Calculate(string express)
{
	int len = express.size();
	int num = 0;
	for (int i = 0; i < len; i++)
	{
		if (express[i] == '+')
		{
			int t = CalNum(express, i + 1);
			num += t; i += to_string(t).size();
		}
		else if (express[i] == '*')
		{
			int t = CalNum(express, i + 1);
			num *= t; i += to_string(t).size();
		}
		else if (express[i] == '-')
		{
			int t = CalNum(express, i + 1);
			num -= t; i += to_string(t).size();
		}
		else
		{
			int t = CalNum(express, i);
			num += t; i += (to_string(t).size() - 1);
		}
	}
	return num;
}



string newExpression(deque<int>bracket)
{
	string newStr = "";
	int from = -1; int to = -1;
	for (int i = 0; i < strLen; i++)
	{
		if (i <= to) { continue; }
		from = -1; to = -1;
		if (bracket.size() == 0) { newStr += inputString[i]; continue; }
		if (bracket.front() != i) { newStr += inputString[i]; continue; }
		from = i; bracket.pop_front();
		to = bracket.front(); bracket.pop_front();
		string temp = inputString.substr(from, to - from + 1);
		newStr += to_string(Calculate(temp));
	}
	return newStr;
}

void DFS(int idx, deque<int> bracket, int siz)
{

	if (bracket.size() == siz)
	{
		string newOne = newExpression(bracket);
		//cout << newOne << endl;

		Answer = max(Answer, Calculate(newOne));
		return;
	}

	for (int i = idx; i < strLen - 2; i += 2)
	{
		if (visited[i] == 1) { continue; }
		bracket.push_back(i);
		bracket.push_back(i + 2);
		visited[i + 2] = 1;
		visited[i] = 1;
		DFS(i + 2, bracket, siz);
		visited[i] = 0;
		visited[i + 2] = 0;
		bracket.pop_back();
		bracket.pop_back();

	}
}




int main()
{
	cin >> strLen;
	cin >> inputString;
	deque<int> bracket;

	for (int siz = 2; siz <= strLen / 2; siz += 2)
	{
		for (int i = 0; i < strLen - 2; i += 2)
		{
			bracket.push_back(i);
			bracket.push_back(i + 2);
			visited[i] = 1;
			visited[i + 2] = 1;
			DFS(i + 2, bracket, siz);
			visited[i] = 0;
			visited[i + 2] = 0;
			bracket.pop_back();
			bracket.pop_back();
		}
	}
	if (inputString.size() <= 3)
	{
		Answer = Calculate(inputString);
	}

	cout << Answer;



}