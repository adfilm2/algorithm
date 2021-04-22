#include <iostream>
#include <vector>
using namespace std;
vector<int> plusStation;
int solution(int n, vector<int> stations, int w)
{
	int length = stations.size();
	int answer = 0;
	long long from = 1;
	long long to = 1;

	for (int i = 0; i < length; i++)
	{
		if (i == 0)
			from = 1;
		else
			from = stations[i - 1] + w + 1;
		to = stations[i] - w - 1;
		if (!(from > to)) {
			plusStation.push_back(to - from + 1);
		}
		if (i == length - 1 && n > stations[i] + w)
		{
			from = stations[i] + w + 1;
			to = n;
			if (from > to) { continue; }
			plusStation.push_back(to - from + 1);
		}
	}
	int len = plusStation.size();
	for (int i = 0; i < len; i++)
	{
		if (plusStation[i] <= 2 * w + 1)
		{
			answer++; continue;
		}
		int plus = plusStation[i] / (2 * w + 1);
		if (plusStation[i] % (2 * w + 1) != 0)
			plus++;
		answer += plus;
	}
	return answer;
}