#include <string>
#include <vector>
#include <iostream>
using namespace std;

int Time[1000];
string Title[1000];
string Music[1000];
string answer = "(None)";
int ansIdx = -1;

string MusicChange(string input)
{
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == '#')
		{
			input[i - 1] += 32;
			input.erase(input.begin() + i);
			i--;
		}
	}
	return input;
}


void Parsing(vector<string> info, string m)
{
	int len = info.size();
	for (int i = 0; i < len; i++)
	{
		//Time
		string t = "";
		t += info[i][0]; t += info[i][1];
		int from = atoi(t.c_str()) * 60; t = "";
		t += info[i][3]; t += info[i][4];
		from += atoi(t.c_str());
		t = "";
		t += info[i][6]; t += info[i][7];
		int to = atoi(t.c_str()) * 60; t = "";
		t += info[i][9]; t += info[i][10];
		to += atoi(t.c_str());
		Time[i] = to - from;

		//Title
		auto titleIdx = info[i].find(',', 12);
		string title = info[i].substr(12, titleIdx - 12);
		Title[i] = title;

		//Music
		string music = info[i].substr(titleIdx + 1);
		music = MusicChange(music);
		music = music.substr(0, Time[i]);
		int idx = 0; int initLen = music.size();
		while (music.size() < Time[i])
		{
			if (idx == initLen) { idx = 0; }
			music += music[idx];
			idx++;
		}
		Music[i] = music;

		if (music.size() < m.size()) { continue; }
		for (int j = 0; j <= music.size() - m.size(); j++)
		{
			if (m == music.substr(j, m.size()))
			{
				if (ansIdx == -1 || music.size() > Music[ansIdx].size())
				{
					answer = Title[i]; ansIdx = i;
				}
				break;
			}
		}
	}
}


string solution(string m, vector<string> musicinfos) {
	Parsing(musicinfos, MusicChange(m));
	return answer;
}