#include<iostream>
using namespace std;
#define MAXN 64
#define MAXQ 1000
#define fi(i, a, b) for(register int i = a; i < b; i++)

int N, Q;
int origin[MAXN][MAXN];

int dirX[4] = { -1, 0, 0, 1 };
int dirY[4] = { 0, -1, 1, 0 };

void rotate(int pivotR, int pivotC, int size);
void melting();

void fireTornado(int level) {
	int unit = 1 << level;
	int size = N / unit;

	fi(i, 0, size) {
		fi(j, 0, size) {
			int sR = i * unit;
			int sC = j * unit;
			rotate(sR, sC, unit);
		}
	}

	melting();
}
bool visit[MAXN][MAXN];

int q[MAXN * MAXN * 3];
int f, r;
int search(int sR, int sC, int* volume) {
	int area = 1;
	visit[sR][sC] = true;
	f = r = -1;
	q[++r] = sR; 
	q[++r] = sC;
	while (f < r) {
		int curR = q[++f];
		int curC = q[++f];
		fi(d, 0, 4) {
			int nextR = curR + dirX[d];
			int nextC = curC + dirY[d];
			if (nextR < 0 || nextC < 0 || nextR >= N || nextC >= N) continue;
			if (visit[nextR][nextC]) continue;
			q[++r] = nextR;
			q[++r] = nextC;
			visit[nextR][nextC] = true;
			*volume += origin[nextR][nextC]; 
			area++;
		}
	}
	return area;
}
int findMax() {
	int max = 0;
	fi(i, 0, N) {
		fi(j, 0, N) {
			visit[i][j] = origin[i][j] == 0;
		}
	}
	fi(i, 0, N) {
		fi(j, 0, N) {
			if (visit[i][j]) continue;
			int volume = origin[i][j];
			int v = search(i, j, &volume);
			max = max > v ? max : v;
		}
	}
	return max;
}
int sum;
int main() {
	register int _N;
	cin >> _N >> Q;
	N = 1 << _N;
	sum = 0;
	fi(i, 0, N) {
		fi(j, 0, N) {
			cin >> origin[i][j];
			sum += origin[i][j];
		}
	}
	register int level;
	fi(i, 0, Q) {
		cin >> level;
		fireTornado(level);
	}
	int max = findMax();
	cout << sum << endl << max;
	return 0;
}

int buf[MAXN][MAXN];
void rotate(int pivotR, int pivotC, int size) {
	fi(r, 0, size) {
		fi(c, 0, size) {
			int moveR = pivotR + c;
			int moveC = pivotC + size - 1 - r;
			buf[moveR][moveC] = origin[r + pivotR][c + pivotC];
		}
	}
	int toR = pivotR + size;
	int toC = pivotC + size;
	fi(i, pivotR, toR) {
		fi(j, pivotC, toC) {
			origin[i][j] = buf[i][j];
		}
	}
}

void melting() {
	fi(i, 0, N) {
		fi(j, 0, N) {
			buf[i][j] = origin[i][j];
		}
	}
	fi(i, 0, N) {
		fi(j, 0, N) {
			if (origin[i][j] == 0) continue;
			int neighbor = 0;
			fi(d, 0, 4) {
				int nextR = i + dirX[d];
				int nextC = j + dirY[d];
				if (nextR < 0 || nextC < 0 || nextR >= N || nextC >= N) continue;
				if (buf[nextR][nextC] > 0) {
					neighbor++;
				}
			}
			if (neighbor >= 3) continue;
			origin[i][j] -= 1;
			sum -= 1;
		}
	}
}