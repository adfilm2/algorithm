#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
using namespace std;
struct food {
	int time;
	int idx;
};
deque<food> foods;
bool cmp(food a, food b)
{
	return a.time < b.time;
}
bool cmp2(food a, food b)
{
	return a.idx < b.idx;
}


int solution(vector<int> food_times, long long k) {
	int len = food_times.size();
	for (int i = 0; i < len; i++)
	{
		food t;
		t.idx = i; t.time = food_times[i];
		foods.push_back(t);
	}
	sort(foods.begin(), foods.end(), cmp);
	long t = len; long minus = 0;
	while (1)
	{
		if (k < (foods.front().time - minus)*t)
		{
			k %= t;
			sort(foods.begin(), foods.end(), cmp2);
			return foods[k].idx + 1;
		}
		else if (t > 0)
		{
			int temp = (foods.front().time - minus);
			foods.pop_front();
			k -= (temp*t);
			t--;
			while (1)
			{
				if (t > 0 && foods.front().time == (temp + minus))
				{
					foods.pop_front();  t--;
				}
				else { break; }
			}
			minus += temp;
		}
		else return -1;
	}
	int answer = 0;
	return answer;
}