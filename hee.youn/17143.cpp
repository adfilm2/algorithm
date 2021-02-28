#include<iostream>
using namespace std;
#define UP 0
#define DOWN 1
#define RIGHT 2
#define LEFT 3
#define fi(i, a, b) for(register int i = a; i < b; i++)
#define MAX_M 10000
#define MAX_N 100
#define vertical(dir) (dir == UP || dir == DOWN)
#define opposite(dir) (dir % 2 == 1 ? dir - 1 : dir + 1)
#define edge(r, c, d) ((d == UP && r == 0) || (d == DOWN && r == R - 1) || (d == LEFT && c == 0) || (d == RIGHT && c == C - 1))

int R, C, M;

struct Pos {
	int r;
	int c;
	Pos operator+(Pos pos) {
		return { r + pos.r, c + pos.c };
	}
};
Pos dir[4]{ {-1, 0}, {1, 0}, {0, 1}, {0, -1} };

struct Shark {
	Pos pos;
	int s;
	int d;
	int z;
	bool alive;
	bool move(Shark* map[MAX_N][MAX_N]) {
		fi(i, 0, s) {
			if (edge(pos.r, pos.c, d)) {
				d = opposite(d);
			}
			pos = pos + dir[d];
		}
		if (map[pos.r][pos.c] != 0) {
			if (map[pos.r][pos.c]->z > z) {
				alive = false;
				return false;
			}
			else {
				map[pos.r][pos.c]->alive = false;
			}

		}
		map[pos.r][pos.c] = this;
		return true;
	}
} sharks[MAX_M];

Shark* map[MAX_N][MAX_N][MAX_N];

int main() {
	cin >> R >> C >> M;
	fi(i, 0, M) {
		int r, c, s, d, z;
		cin >> r >> c >> s >> d >> z;
		r -= 1;
		c -= 1;
		d -= 1;
		s = s % (vertical(d) ? (R - 1) * 2 : (C - 1) * 2);
		sharks[i] = { {r, c}, s, d, z, true };
		map[0][r][c] = &sharks[i];
	}
	unsigned long long catchedFish = 0;
	fi(time, 0, C) {
		fi(r, 0, R) {
			if (map[time][r][time] == 0) continue;
			map[time][r][time]->alive = false;
			catchedFish += map[time][r][time]->z;
			break;
		}
		if (time == C - 1) break;
		fi(i, 0, M) {
			if (!sharks[i].alive) continue;
			sharks[i].move(map[time + 1]);
		}
	}
	cout << catchedFish;
	return 0;
}