#include<iostream>
using namespace std;
#define fi(i, a, b) for(register int i = a; i < b; i++)
#define N 10
#define M 4
#define NODE_SIZE 33

#define START 0
#define FINISH 32

struct Node {
	int no;
	int score;
	Node* nextRed;
	Node* nextBlue;
} nodes[NODE_SIZE];

void generateMap();

int pos[N + 1][M];
int dices[N];
bool stand[NODE_SIZE];

bool move(int* cur, int dice) {
	Node* node = &nodes[*cur];
	if (node->nextBlue) {
		node = node->nextBlue;
		dice -= 1;
	}
	while(dice > 0 && node->no != FINISH) {
		node = node->nextRed;
		dice -= 1;
	}
	if (node->no != FINISH && stand[node->no]) {
		return false;
	}
	stand[*cur] = false;
	stand[node->no] = true;
	*cur = node->no;
	return true;
}

int recursive(int level, int total) {
	if (level == N + 1) {
		return total;
	}
	int max = 0;
	fi(i, 0, 4) {
		pos[level][i] = pos[level - 1][i];
	}
	fi(i, 0, 4) {
		int* cur = &pos[level][i];
		if (*cur == FINISH) continue;
		if (!move(cur, dices[level - 1])) continue;
		int score = recursive(level + 1, total + nodes[*cur].score);
		if (max < score) max = score;
		stand[pos[level][i]] = false;
		stand[pos[level - 1][i]] = true;
		pos[level][i] = pos[level - 1][i];
	}
	return max;
}

void init() {
	generateMap();
	fi(i, 0, NODE_SIZE) stand[i] = 0;
	fi(i, 0, 4) pos[0][i] = START;
}
int main() {
	fi(i, 0, 10) {
		cin >> dices[i];
	}
	init();
	cout << recursive(1, 0);
	return 0;
}

void generateMap() {
	int idx = 1;
	for(; idx < 20; idx++) {
		nodes[idx] = { idx, idx * 2, &nodes[idx + 1], 0 };
	}
	nodes[START] = { START, 0, &nodes[1], 0 };
	nodes[FINISH] = { FINISH, 0, 0, 0 };
	nodes[20] = { 20, 40, &nodes[32], 0 };
	nodes[21] = { 21, 13, &nodes[22], 0 };
	nodes[22] = { 22, 16, &nodes[23], 0 };
	nodes[23] = { 23, 19, &nodes[24], 0 };
	nodes[24] = { 24, 25, &nodes[30], 0 };
	nodes[25] = { 25, 26, &nodes[24], 0 };
	nodes[26] = { 26, 27, &nodes[25], 0 };
	nodes[27] = { 27, 28, &nodes[26], 0 };
	nodes[28] = { 28, 22, &nodes[29], 0 };
	nodes[29] = { 29, 24, &nodes[24], 0 };
	nodes[30] = { 30, 30, &nodes[31], 0 };
	nodes[31] = { 31, 35, &nodes[20], 0 };
	nodes[5].nextBlue = &nodes[21];
	nodes[10].nextBlue = &nodes[28];
	nodes[15].nextBlue = &nodes[27];
}