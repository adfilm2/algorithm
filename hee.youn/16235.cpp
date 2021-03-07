#include<iostream>
#define MAX 10
#define MAX_TREE 1000000
#define fi(i, a, b) for(int i = a; i < b; i++)
using namespace std;

int N, M, K;
int map[MAX][MAX];
int origin[MAX][MAX];

struct Pos {
	int x;
	int y;
	Pos operator+(Pos p) {
		return { x + p.x, y + p.y };
	}
};

struct Tree {
	Pos pos;
	int age;
	bool alive;
	int x() {
		return pos.x;
	}
	int y() {
		return pos.y;
	}
} trees[MAX_TREE];
int treeSize;

void grow() {
	for (int i = treeSize - 1; i >= 0; i--) {
		Tree* tree = &trees[i];
		if (map[tree->x()][tree->y()] < tree->age) {
			tree->alive = false;
			continue;
		}
		map[tree->x()][tree->y()] -= tree->age;
		tree->age += 1;
	}
}

void nourishment() {
	int h = 0;
	for (int i = 0; i < treeSize; i++) {
		Tree* tree = &trees[i];
		if (tree->alive) {
			trees[h++] = trees[i];
			continue;
		}
		map[tree->x()][tree->y()] += tree->age / 2;
	}
	treeSize = h;
}

bool isValid(Pos pos) {
	return pos.x >= 0 && pos.x < N && pos.y >= 0 && pos.y < N;
}
Pos dir[8]{ {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
void propagate() {
	int h = 0;
	for (int i = 0; i < treeSize; i++) {
		Tree* tree = &trees[i];
		if (tree->age % 5 != 0) continue;
		fi(d, 0, 8) {
			Pos nxt = tree->pos + dir[d];
			if (!isValid(nxt)) continue;
			trees[treeSize++] = { nxt, 1, true };
		}
	}
}

void supplement() {
	fi(i, 0, N) {
		fi(j, 0, N) {
			map[i][j] += origin[i][j];
		}
	}
}
int main() {
	cin >> N >> M >> K;
	fi(i, 0, N) {
		fi(j, 0, N) {
			cin >> origin[i][j];
			map[i][j] = 5;
		}
	}
	fi(i, 0, M) {
		int x, y, z;
		cin >> x >> y >> z;
		trees[i] = { {x - 1, y - 1}, z, true };
	}
	treeSize = M;
	fi(k, 0, K) {
		grow();
		nourishment();
		propagate();
		supplement();
	}
	cout << treeSize;
	return 0;
}