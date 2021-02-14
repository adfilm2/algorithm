#include<iostream>
#include<functional>
using namespace std;
#define fi(i, a, b) for(register int i = a; i <b; i++)
#define MAX 100000
#define MAX_N 50
#define MAX_M 10
#define WALL 1
#define VIRUS 2
#define EMPTY 0

int N, M;
int map[MAX_N][MAX_N];
struct Pos {
	int x, y;
	Pos operator +(Pos pos) {
		return { x + pos.x, y + pos.y };
	}
};
Pos dir[4]{ {-1, 0}, {0, -1}, {1, 0}, {0, 1} };

bool outRange(Pos pos) {
	return pos.x < 0 || pos.y < 0 || pos.x >= N || pos.y >= N;
}

Pos virus[MAX_M];
int virusSize;

int arr[MAX_M];
void permutation(int targetSize, int max, int cur, int size, std::function<void(int* arr, int size)> job) {
	if (size == targetSize) {
		job(arr, size);
		return;
	}
	fi(i, cur, max) {
		arr[size] = i;
		permutation(targetSize, max, i + 1, size + 1, job);
	}
}

int visit[MAX_N][MAX_N];
Pos queue[MAX];
int f, r;
int main() {
	cin >> N >> M;
	virusSize = 0;
	int goal = 0;
	fi(i, 0, N) {
		fi(j, 0, N) {
			cin >> map[i][j];
			if (map[i][j] == EMPTY) goal++;
			if (map[i][j] == VIRUS) {
				virus[virusSize++] = { i, j };
			}
		}
	}
	if (goal == 0) {
		cout << 0;
		return 0;
	}
	int min = -1;
	permutation(M, virusSize, 0, 0, [&min, goal](int* arr, int size) -> void {
		fi(i, 0, N) {
			fi(j, 0, N) {
				visit[i][j] = 0;
			}
		}
		f = r = -1;
		fi(i, 0, size) {
			Pos v = virus[arr[i]];
			queue[++r] = v;
			visit[v.x][v.y] = 1;
		}
		int cnt = 0;
		while (f < r) {
			Pos cur = queue[++f];
			fi(k, 0, 4) {
				Pos nxt = cur + dir[k];
				if (outRange(nxt)) continue;
				if (map[nxt.x][nxt.y] == WALL) continue;
				if (visit[nxt.x][nxt.y] > 0) continue;
				visit[nxt.x][nxt.y] = visit[cur.x][cur.y] + 1;
				cnt += map[nxt.x][nxt.y] == EMPTY ? 1 : 0;
				queue[++r] = nxt;
				if (cnt == goal) break;
			}
			if (cnt == goal) break;
		}
		if (cnt != goal) return;
		int last = visit[queue[r].x][queue[r].y] - 1;
		if (min == -1) min = last;
		else min = min > last ? last : min;
	});
	cout << min;
	return 0;
}