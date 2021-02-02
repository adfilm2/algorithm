#include<iostream>
using namespace std;
#define MAXN 64
#define MAXQ 1000
#define fi(i, a, b) for(register int i = a; i < b; i++)

int N;

struct Pos {
	int r;
	int c;
	Pos operator+(Pos pos) const {
		return { r + pos.r, c + pos.c };
	}
};

void rotate(int map[][MAXN], int level);
int melting(int map[][MAXN]);
int findMax(int map[][MAXN]);

int fireTornado(int map[][MAXN], int level) {
	rotate(map, level);
	return melting(map);
}

int origin[MAXN][MAXN];
int main() {
	int _N, Q;
	cin >> _N >> Q;
	N = 1 << _N;
	int sum = 0;
	fi(i, 0, N) {
		fi(j, 0, N) {
			cin >> origin[i][j];
			sum += origin[i][j];
		}
	}
	register int level;
	fi(i, 0, Q) {
		cin >> level;
		sum -= fireTornado(origin, level);
	}
	int max = findMax(origin);
	cout << sum << endl << max;
	return 0;
}

Pos dir[4] = { {-1, 0}, {0, -1}, {0, 1}, {1, 0} };
bool isOutRange(int r, int c) {
	return (r < 0 || c < 0 || r >= N || c >= N);
}
bool isOutRange(Pos pos) {
	return isOutRange(pos.r, pos.c);
}

int buf[MAXN][MAXN];
void rotateUnit(int map[][MAXN], int pivotR, int pivotC, int size) {
	fi(r, 0, size) {
		fi(c, 0, size) {
			int moveR = pivotR + c;
			int moveC = pivotC + size - 1 - r;
			buf[moveR][moveC] = map[r + pivotR][c + pivotC];
		}
	}
	int toR = pivotR + size;
	int toC = pivotC + size;
	fi(i, pivotR, toR) {
		fi(j, pivotC, toC) {
			map[i][j] = buf[i][j];
		}
	}
}
void rotate(int map[][MAXN], int level) {
	int unit = 1 << level;
	int size = N / unit;
	for (int r = 0; r < N; r += unit) {
		for (int c = 0; c < N; c += unit) {
			rotateUnit(map, r, c, unit);
		}
	}
}

int melting(int map[][MAXN]) {
	int count = 0;
	fi(i, 0, N) {
		fi(j, 0, N) {
			buf[i][j] = map[i][j];
		}
	}
	fi(i, 0, N) {
		fi(j, 0, N) {
			if (map[i][j] == 0) continue;
			int neighbor = 0;
			fi(d, 0, 4) {
				int nextR = i + dir[d].r;
				int nextC = j + dir[d].c;
				if (isOutRange(nextR, nextC)) continue;
				if (buf[nextR][nextC] == 0) continue;
				neighbor++;
			}
			if (neighbor >= 3) continue;
			origin[i][j] -= 1;
			count++;
		}
	}
	return count;
}

Pos q[MAXN * MAXN * 3];
int f, r;
bool visit[MAXN][MAXN];
int search(int startR, int startC) {
	int area = 1;
	visit[startR][startC] = true;
	f = r = -1;
	q[++r] = { startR, startC };
	while (f < r) {
		Pos cur = q[++f];
		fi(d, 0, 4) {
			Pos next = cur + dir[d];
			if (isOutRange(next)) continue;
			if (visit[next.r][next.c]) continue;
			q[++r] = next;
			visit[next.r][next.c] = true;
			area++;
		}
	}
	return area;
}

int findMax(int map[][MAXN]) {
	int max = 0;
	fi(i, 0, N) {
		fi(j, 0, N) {
			visit[i][j] = map[i][j] == 0;
		}
	}
	fi(i, 0, N) {
		fi(j, 0, N) {
			if (visit[i][j]) continue;
			int v = search(i, j);
			max = max > v ? max : v;
		}
	}
	return max;
}