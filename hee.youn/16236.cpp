#include<iostream>
#define fi(i, a, b) for(int i = a; i < b; i++)
#define MAX_N 20
#define MAX_QUEUE 1000000

using namespace std;

struct Pos {
	int r;
	int c;
	Pos operator+(Pos p) {
		return { r + p.r, c + p.c };
	}
	bool operator>(Pos p) {
		return r > p.r;
	}
};

struct Shark {
	Pos pos;
	int size;
	int need;
	void eat(Pos target) {
		need--;
		if (need == 0) {
			size += 1;
			need = size;
		}
		pos = target;
	}
} shark;

int N;
int map[MAX_N][MAX_N];

bool isValid(Pos pos) {
	return pos.r >= 0 && pos.r < N && pos.c >= 0 && pos.c < N;
}

Pos dir[4]{ {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

Pos queue[MAX_QUEUE];
int f, r;
int visit[MAX_N][MAX_N];
int search(Pos* target) {
	fi(i, 0, N) {
		fi(j, 0, N) {
			visit[i][j] = 0;
		}
	}
	f = r = -1;
	queue[++r] = shark.pos;
	visit[shark.pos.r][shark.pos.c] = 1;
	int minDistance = -1;
	while (f < r) {
		Pos cur = queue[++f];
		if (visit[cur.r][cur.c] == minDistance) continue;
		fi(k, 0, 4) {
			Pos nxt = cur + dir[k];
			if (!isValid(nxt)) continue;
			if (map[nxt.r][nxt.c] > shark.size) continue;
			if (visit[nxt.r][nxt.c] > 0) continue;
			visit[nxt.r][nxt.c] = visit[cur.r][cur.c] + 1;
			queue[++r] = nxt;
			if (map[nxt.r][nxt.c] == shark.size) continue;
			if (map[nxt.r][nxt.c] == 0) continue;
			if (minDistance == -1) {
				minDistance = visit[nxt.r][nxt.c];
				*target = nxt;
				continue;
			}
			if (*target > nxt) *target = nxt;
		}
	}
	return minDistance - 1;
}

int main() {
	cin >> N;
	int total = 0;
	fi(i, 0, N) {
		fi(j, 0, N) {
			cin >> map[i][j];
			if (map[i][j] == 0) continue;
			if (map[i][j] == 9) {
				shark = { {i, j}, 2, 2 };
				map[i][j] = 0;
				continue;
			}
			total++;
		}
	}
	int time = 0;
	for (; total > 0; total--) {
		Pos target{};
		int distance = search(&target);
		if (distance < 0) break;
		time += distance;
		shark.eat(target);
		map[target.r][target.c] = 0;
	}
	cout << time;
}