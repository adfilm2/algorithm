#include<iostream>
using namespace std;
#define WHITE 0
#define RED 1
#define BLUE 2
#define MAX_N 12
#define MAX_K 10
#define fi(i, a, b) for(register int i = a; i < b; i++)
#define fie(i, a, b) for(register int i = a; i <= b; i++)

int dir[4][2]{ {0, 1}, {0, -1}, {-1, 0}, {1, 0} };
int opposite[4] { 1, 0, 3, 2 };
int map[MAX_N + 2][MAX_N + 2];

int N, K;

struct Node {
	int no;
	int r;
	int c;
	int d;
	int h;
} nodes[MAX_K];

Node* arr[MAX_N +2][MAX_N+2][MAX_K];
int arrSize[MAX_N+2][MAX_N+2];
bool hit;

void put(int r, int c, Node* node) {
	int top = arrSize[r][c];
	arr[r][c][top] = node;
	node->r = r;
	node->c = c;
	node->h = top;
	arrSize[r][c]++;
	if (arrSize[r][c] >= 4)
		hit = true;
}

void transfer(int r, int c, int d, int h, bool reverse) {
	int nr = r + dir[d][0];
	int nc = c + dir[d][1];
	if (reverse) {
		int debue = 0;
	}
	int buf = arrSize[r][c] - 1 + h;
	fi(_i, h, arrSize[r][c]) {
		int i = reverse ? buf - _i : _i;
		put(nr, nc, arr[r][c][i]);
	}
	arrSize[r][c] = h;
}

void mv(Node* node, bool recursive) {
	int nr = node->r + dir[node->d][0];
	int nc = node->c + dir[node->d][1];
	switch (map[nr][nc]) {
	case WHITE:
		transfer(node->r, node->c, node->d, node->h, false);
		break;
	case RED:
		transfer(node->r, node->c, node->d, node->h, true);
		break;
	case BLUE:
		if (recursive) {
			node->d = opposite[node->d];
			mv(node, false);
		}
		break;
	}
}
bool simulate() {
	hit = false;
	fi(i, 0, K) {
		mv(&nodes[i], true);
	}
	return !hit;
}

int main() {
	cin >> N >> K;
	fie(i, 0, N + 1) {
		map[i][0] = map[0][i] = map[N + 1][i] = map[i][N + 1] = BLUE;
	}
	fie(i, 1, N) {
		fie(j, 1, N) {
			cin >> map[i][j];
		}
	}
	fi(i, 0, K) {
		int r, c, d;
		cin >> r >> c >> d;
		d -= 1;
		nodes[i] = { i+1, r, c, d, 0 };
		put(r, c, &nodes[i]);
	}
	int time = 0;
	do {
		time++;
		if (time > 1000) {
			cout << -1;
			return 0;
		}
	} while (simulate());
	cout << time;
	return 0;
}