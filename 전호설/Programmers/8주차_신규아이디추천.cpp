#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

string Step1(string new_id)
{
	int len = new_id.size();
	for (int i = 0; i < len; i++)
	{
		if (new_id[i] >= 'A'&&new_id[i] <= 'Z')
		{
			new_id[i] += 32;
		}
	}
	return new_id;
}

string Step2(string new_id)
{
	string temp = "";
	int len = new_id.size();
	for (int i = 0; i < len; i++)
	{
		if (!((new_id[i] >= 'a'&&new_id[i] <= 'z') || new_id[i] == '-' || new_id[i] == '_' || new_id[i] == '.' || (new_id[i] >= '0'&&new_id[i] <= '9')))
		{
			continue;
		}
		temp += new_id[i];
	}
	return temp;
}

string Step345(string new_id)
{
	string temp = "";
	int len = new_id.size();
	bool isSpot = false;
	for (int i = 0; i < len; i++)
	{
		if (isSpot&&new_id[i] == '.') { continue; }
		if (isSpot&&new_id[i] != '.') { isSpot = false; }
		if (!isSpot&&new_id[i] == '.') { isSpot = true; }
		temp += new_id[i];
	}
	len = temp.size();
	if (len > 0)
	{
		if (temp[0] == '.')
		{
			temp.erase(0, 1);
		}
		if (temp[temp.size() - 1] == '.')
		{
			temp.erase(temp.size() - 1, 1);
		}
		//cout<<temp<<endl;
	}

	if (temp.size() == 0)
	{
		temp += 'a';
	}

	if (temp.size() >= 16)
	{
		temp = temp.substr(0, 15);
		if (temp[14] == '.')
		{
			temp.erase(14, 1);
		}
	}

	if (temp.size() <= 2)
	{
		char t = temp[temp.size() - 1];
		while (temp.size() < 3)
		{
			temp += t;
		}
	}
	return temp;
}



string solution(string new_id) {
	string answer = Step1(new_id);
	answer = Step2(answer);
	answer = Step345(answer);
	return answer;
}