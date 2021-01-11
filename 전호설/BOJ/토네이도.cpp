#include <iostream>
using namespace std;
int N;
int Map[500][500];
int a, b;
int lev = 0;
int dir[4][2] = { {0,-1},{1,0},{0,1},{-1,0} };
int nowDir = 0;
int amount = 0;
int send[6];
int ANS;
void send_fill(int num)
{
	send[0] = (int)(num*0.01);
	send[1] = (int)(num*0.02);
	send[2] = (int)(num*0.05);
	send[3] = (int)(num*0.07);
	send[4] = (int)(num*0.1);
	send[5] = num - (send[0] * 2 + send[1] * 2 +send[2]+ send[3]*2 + send[4] * 2);
}

void push(int a, int b, int p)
{
	if (a >= 0 && a < N&&b >= 0 && b < N)
	{
		Map[a][b] += send[p];
	}
	else
	{
		ANS += send[p];
	}

}


void action(int a, int b)
{
	if (nowDir == 0)
	{
		push(a, b - 1, 5);
		push(a, b - 2, 2);
		push(a - 1, b - 1, 4);
		push(a - 1, b, 3);
		push(a - 1, b + 1, 0);
		push(a + 1, b - 1, 4);
		push(a + 1, b, 3);
		push(a + 1, b + 1, 0);
		push(a - 2, b, 1);
		push(a + 2, b, 1);
	}
	else if (nowDir == 1)
	{
		push(a + 1, b, 5);
		push(a + 2, b, 2);
		push(a - 1, b - 1, 0);
		push(a, b - 1, 3);
		push(a + 1, b - 1, 4);
		push(a - 1, b + 1, 0);
		push(a, b + 1, 3);
		push(a + 1, b + 1, 4);
		push(a, b - 2, 1);
		push(a, b + 2, 1);
	}
	else if (nowDir == 2)
	{
		push(a, b + 1, 5);
		push(a, b + 2, 2);
		push(a - 1, b - 1, 0);
		push(a - 1, b, 3);
		push(a - 1, b + 1, 4);
		push(a + 1, b - 1, 0);
		push(a + 1, b, 3);
		push(a + 1, b + 1, 4);
		push(a - 2, b, 1);
		push(a + 2, b, 1);
	}
	else if (nowDir == 3)
	{
		push(a - 1, b, 5);
		push(a - 2, b, 2);
		push(a + 1, b - 1, 0);
		push(a, b - 1, 3);
		push(a - 1, b - 1, 4);
		push(a + 1, b + 1, 0);
		push(a, b + 1, 3);
		push(a - 1, b + 1, 4);
		push(a, b - 2, 1);
		push(a, b + 2, 1);

	}


}


int main()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			cin >> Map[i][j];
		}
	}
	int a = N / 2; int b = N / 2;
	while (1)
	{
		lev ++;
		for(int twice = 0; twice < 2; twice++)
		{
			for (int i = 0; i < lev; i++)
			{
				a = a + dir[nowDir][0]; b = b + dir[nowDir][1];
				amount = Map[a][b];
				if (amount > 0)
				{
					send_fill(amount);
					action(a, b);
					Map[a][b] = 0;
				}
			}
			nowDir++; if (nowDir == 4) { nowDir = 0; }
			
		}

		if (lev==N-1)
		{
			for (int i = 0; i < lev; i++)
			{
				a = a + dir[nowDir][0]; b = b + dir[nowDir][1];
				amount = Map[a][b];
				if (amount > 0)
				{
					send_fill(amount);
					action(a, b);
					Map[a][b] = 0;
				}
			}
			if (a == 0 && b == 0)
			{
				break;
			}
		}
	}
	cout << ANS;

}