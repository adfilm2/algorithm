#include<iostream>
#define fi(i, a, b) for(int i = a; i < b; i++)
#define mod(a, b) ((a + b) % b)
#define MAX 50

using namespace std;

struct Pos {
	int r;
	int c;
	Pos operator+(Pos p) {
		return { r + p.r, c + p.c };
	}
	bool operator==(Pos p) {
		return r == p.r && c == p.c;
	}
	bool operator!=(Pos p) {
		return !(r == p.r && c == p.c);
	}
};
Pos dir[4]{ {0, 1}, {-1, 0}, {0, -1}, {1, 0} };

Pos robots[2];
int robot_size;
int map[MAX][MAX];
int moved[MAX][MAX];
int R, C;

bool isValid(Pos pos) {
	return pos.r >= 0 && pos.r < R && pos.c >= 0 && pos.c < C;
}

void expand() {
	fi(i, 0, R) {
		fi(j, 0, C) {
			moved[i][j] = 0;
		}
	}
	fi(i, 0, R) {
		fi(j, 0, C) {
			if (map[i][j] <= 0) continue;
			int unit = map[i][j] / 5;
			fi(k, 0, 4) {
				Pos nxt = Pos{ i, j } + dir[k];
				if (!isValid(nxt)) continue;
				if (map[nxt.r][nxt.c] == -1) continue;
				moved[nxt.r][nxt.c] += unit;
				map[i][j] -= unit;
			}
		}
	}
	fi(i, 0, R) {
		fi(j, 0, C) {
			map[i][j] += moved[i][j];
		}
	}
}
int work() {
	int acc = -1;
	int ret = 0;
	for (int idx = 0; idx < 2; idx++) {
		Pos head = robots[idx] + dir[0];
		int d = 0;
		acc *= -1;
		int before = 0;
		while (head != robots[idx]) {
			if (!isValid(head + dir[d])) {
				d = mod(d + acc, 4);
			}
			int buf = map[head.r][head.c];
			map[head.r][head.c] = before;
			head = head + dir[d];
			before = buf;
		}
		ret += before;
	}
	return ret;
}

int main() {
	int T;
	cin >> R >> C >> T;
	int total = 2;
	robot_size = 0;
	fi(i, 0, R) {
		fi(j, 0, C) {
			cin >> map[i][j];
			if (map[i][j] == -1) {
				robots[robot_size++] = { i, j };
			}
			total += map[i][j];
		}
	}
	fi(t, 0, T) {
		expand();
		total -= work();
	}
	cout << total;
}