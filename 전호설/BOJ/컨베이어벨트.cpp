#include <iostream>
using namespace std;

struct belt {

	int dur;
	bool isRobot = false;
};
belt conbey[200];
int N, K,ANS;

void fstep()
{
	belt conbey_cp[200];
	for (int i = 1; i < 2 * N; i++)
	{
		conbey_cp[i].dur = conbey[i - 1].dur;
		conbey_cp[i].isRobot = conbey[i - 1].isRobot;
	}
	conbey_cp[0].dur = conbey[2 * N - 1].dur;
	conbey_cp[0].isRobot = conbey[2 * N - 1].isRobot;

	for (int i = 0; i < 2 * N; i++)
	{
		conbey[i].dur = conbey_cp[i].dur;
		conbey[i].isRobot = conbey_cp[i].isRobot;
	}
	if (conbey[N - 1].isRobot == true) { conbey[N - 1].isRobot = false; }
	
}

void sstep()
{
	for (int i = N - 2; i >= 0; i--)
	{
		if ((conbey[i].isRobot) && (conbey[i + 1].dur > 0)&&(conbey[i+1].isRobot==false))
		{
			conbey[i + 1].dur--;
			if (i + 1 != N - 1)
			{
				conbey[i + 1].isRobot = true;
			}
			conbey[i].isRobot = false;
		}
	}
	if (conbey[0].isRobot == false && conbey[0].dur > 0)
	{
		conbey[0].isRobot = true;
		conbey[0].dur--;
	}
}
bool check()
{
	int chk = 0;
	for (int i = 0; i < 2 * N; i++)
	{
		if (conbey[i].dur == 0) { chk++; }
	}
	if (chk >= K) { return true; }
	else { return false; }
}

int main()
{
	cin >> N >> K;
	for (int i = 0; i < N * 2 ; i++)
	{
		cin >> conbey[i].dur;
	}
	while (1)
	{
		ANS++;
		fstep();
		sstep();
		if (check()) { break; }
	}
	cout << ANS;
}