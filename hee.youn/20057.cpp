#include<iostream>
using namespace std;
#define MAXN 500
#define fi(i, a, b) for(register int i = a; i < b; i++)

struct Flyaway {
	int r;
	int c;
	int rate;
};
Flyaway flyaway[10]{ {-2, 0, 2}, {-1, -1, 10}, { -1, 0, 7}, {-1, 1, 1}, {0, -2, 5}, {1, -1, 10}, {1, 0, 7}, {1, 1, 1}, {2, 0, 2}, {0, -1, -1} };

int N;
int map[MAXN][MAXN];
int sandOutside;

short dirX[4]{ 0, 1, 0, -1 };
short dirY[4]{ -1,0, 1, 0 };

void blow(int r, int c, int dir);
void rotate(int* r, int* c, int count);
struct Tornado {
	int r;
	int c;
	int dir;
	int countOfRotate;
	int cnt;
	int limit;
	void init() {
		dir = 0;
		countOfRotate = 0;
		limit = 1;
		cnt = 0;
	}
	bool move() {
		if (r == 0 && c == 0) return false;
		register int nxtR = r + dirX[dir];
		register int nxtC = c + dirY[dir];
		blow(nxtR, nxtC, dir);
		map[nxtR][nxtC] = map[r][c];
		map[r][c] = 0;

		cnt++;
		if (cnt == limit) {
			cnt = 0;
			countOfRotate += 1;
			if (countOfRotate % 2 == 0) limit++;
			dir = (dir + 1) % 4;
		}
		r = nxtR;
		c = nxtC;
		return true;
	}
} tornado;

int buf[MAXN][MAXN];
int main() {
	cin >> N;
	fi(i, 0, N) {
		fi(j, 0, N) {
			cin >> map[i][j];
		}
	}
	tornado = { N / 2, N / 2 };
	tornado.init();
	sandOutside = 0;
	register int cnt = 0;
	while (tornado.move());
	cout << sandOutside;
	return 0;
}

void rotate(int* r, int* c, int count) {
	register int _r = *r;
	register int _c = *c;
	fi(i, 0, count) {
		register int bufR = _r;
		register int bufC = _c;
		_r = bufC * -1;
		_c = bufR;
	}
	*r = _r;
	*c = _c;
}
void blow(int pivotR, int pivotC, int dir) {
	if (map[pivotR][pivotC] == 0) return;
	register int remain = map[pivotR][pivotC];
	fi(i, 0, 10) {
		Flyaway cur = flyaway[i];
		register int r = cur.r;
		register int c = cur.c;
		rotate(&r, &c, dir);
		register int nxtR = pivotR + r;
		register int nxtC = pivotC + c;
		int target = cur.rate != -1 ? (int)(map[pivotR][pivotC] * cur.rate / 100) : remain;
		if (nxtR < 0 || nxtC < 0 || nxtR >= N || nxtC >= N) {
			sandOutside += target;
			if (cur.rate != -1) remain -= target;
			continue;
		}
		map[nxtR][nxtC] += target;
		if (cur.rate != -1) remain -= target;
	}
}
