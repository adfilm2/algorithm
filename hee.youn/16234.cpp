#include<iostream>
#define fi(i, a, b) for(int i = a; i < b; i++)
#define MAX 50
using namespace std;

int N, L, R;
int map[MAX][MAX];
int visit[MAX][MAX];

struct Pos {
	int x;
	int y;
	Pos operator+(Pos pos) {
		return { x + pos.x, y + pos.y };
	}
};

struct Federal {
	int total;
	int cnt;
	int avg;
	void add(int v) {
		total += v;
		cnt++;
	}
	int getAvg() {
		if (avg > 0) return avg;
		avg = total / cnt;
		return avg;
	}
} federals[MAX*MAX];

Pos dir[4]{ {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
bool isValid(Pos pos) {
	return pos.x >= 0 && pos.x < N && pos.y >= 0 && pos.y < N;
}
void recursive(Pos cur, int federal) {
	fi(k, 0, 4) {
		Pos nxt = cur + dir[k];
		if (!isValid(nxt)) continue;
		if (visit[nxt.x][nxt.y] > 0) continue;
		int diff = abs(map[cur.x][cur.y] - map[nxt.x][nxt.y]);
		if (!(diff >= L && diff <= R)) continue;
		visit[nxt.x][nxt.y] = federal;
		federals[federal].add(map[nxt.x][nxt.y]);
		recursive(nxt, federal);
	}
}

bool job() {
	fi(i, 0, N) {
		fi(j, 0, N) {
			visit[i][j] = 0;
			federals[i * N + j] = { 0,0, -1 };
		}
	}
	int federal = 1;
	fi(i, 0, N) {
		fi(j, 0, N) {
			if (visit[i][j] > 0) continue;
			visit[i][j] = federal;
			federals[federal].add(map[i][j]);
			recursive({ i, j }, federal);
			federal++;
		}
	}
	bool valid = false;
	fi(i, 0, N) {
		fi(j, 0, N) {
			if (visit[i][j] == 0) continue;
			int fIdx = visit[i][j];
			if (federals[fIdx].cnt == 1) continue;
			valid = true;
			map[i][j] = federals[fIdx].getAvg();
		}
	}
	return valid;
}
int main() {
	cin >> N >> L >> R;
	fi(i, 0, N) {
		fi(j, 0, N) {
			cin >> map[i][j];
		}
	}
	int cnt = 0;
	for (; job(); cnt++) {
	}
	cout << cnt;
	return 0;
}