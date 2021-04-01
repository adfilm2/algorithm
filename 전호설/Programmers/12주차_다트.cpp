#include <string>
#include <iostream>
#include <algorithm> 
#include <cstdlib>
#include <map>
#include <cmath>
using namespace std;
int Number[500];
int idx = 0;
map<char, int> Hash;

void HashSet()
{
	Hash['S'] = 1;
	Hash['D'] = 2;
	Hash['T'] = 3;

}

void Parse(string tar)
{
	for (int i = 0; i < tar.size(); i++)
	{
		string temp = "";
		temp += tar[i];
		if (tar[i] == '1'&&tar[i + 1] == '0') { temp += '0'; i++; }
		int num = pow(atoi(temp.c_str()), Hash[tar[i + 1]]);
		i++;
		Number[idx] = num;
		if (tar[i + 1] == '#') { Number[idx] *= -1; i++; }
		else if (tar[i + 1] == '*')
		{
			Number[idx] *= 2;  i++;
			if (idx != 0) { Number[idx - 1] *= 2; }
		}
		idx++;
	}
}

int solution(string dartResult) {
	int answer = 0;
	HashSet();
	Parse(dartResult);
	for (int i = 0; i <= idx; i++)
	{
		// cout<<Number[i]<< " ";
		answer += Number[i];
	}
	return answer;
}