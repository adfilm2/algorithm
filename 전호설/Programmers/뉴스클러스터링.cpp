#include <string>
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
string a;
string b;
int up;
int down;
map<string, int> Hash;
void strSet()
{
	int len = a.size();
	for (int i = 0; i < len - 1; i++)
	{
		string temp = "";
		if (!(a[i] >= 'A'&&a[i] <= 'Z')) { temp = ""; continue; }
		if (!(a[i + 1] >= 'A'&&a[i + 1] <= 'Z')) { temp = ""; continue; }
		temp += a[i]; temp += a[i + 1];
		cout << temp << " ";
		Hash[temp]++;
		down++;
	}cout << endl;
	len = b.size();
	for (int i = 0; i < len - 1; i++)
	{
		string temp = "";
		if (!(b[i] >= 'A'&&b[i] <= 'Z')) { temp = ""; continue; }
		if (!(b[i + 1] >= 'A'&&b[i + 1] <= 'Z')) { temp = ""; continue; }
		temp += b[i]; temp += b[i + 1];
		cout << temp << " ";
		if (Hash[temp] > 0)
		{
			up++; Hash[temp]--;
		}
		else
		{
			down++;
		}
	}
	cout << endl;
	cout << up << " " << down;
}


int solution(string str1, string str2) {
	a = str1;
	b = str2;
	transform(a.begin(), a.end(), a.begin(), ::toupper);
	transform(b.begin(), b.end(), b.begin(), ::toupper);
	if (a == b) { return 65536; }
	strSet();
	float temp = (float)up / down;
	float answer = temp * 65536;
	return (int)answer;
}