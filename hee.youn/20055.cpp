#include<iostream>
using namespace std;

#define fi(i, a, b) for(register int i = a; i < b; i++)
#define MAX_N 100
#define MAX_2_N 200
#define MAX_ROBOT 10000000

struct Robot;

int durability[MAX_2_N];
Robot* belts[MAX_2_N];
int N, dN;
int step;
int upArea, downArea;
int broken;

struct Robot {
	int idx;
	int pos;
	bool move() {
		int nextPos = (pos + 1) % dN;
		if (nextPos == downArea) {
			pos = nextPos;
			return true;
		}
		if (belts[nextPos]) return false;
		if (durability[nextPos] == 0) return false;
		pos = nextPos;
		return true;
	}
} robots[MAX_ROBOT];
int f, r;
Robot* addRobot(int pos) {
	Robot* cur = &robots[r++];
	cur->pos = pos;
	cur->idx = r;
	durability[pos] -= 1;
	if (durability[pos] == 0) broken++;
	return cur;
}
void simulate() {
	if (belts[downArea] != 0) {
		f++;
		belts[downArea] = 0;
	}
	fi(i, f, r) {
		int prev = robots[i].pos;
		if (robots[i].move()) {
			int pos = robots[i].pos;
			belts[prev] = 0;
			belts[pos] = &robots[i];
			if (pos == downArea) {
				f++;
				belts[downArea] = 0;
				continue;
			}
			durability[pos] -= 1;
			if (durability[pos] == 0) broken++;
		}
	}
	if (belts[upArea] != 0) {
		cout << "Error" << endl;
	}
	if (durability[upArea] > 0) {
		belts[upArea] = addRobot(upArea);
	}
}
int main() {
	int K;
	cin >> N >> K;
	dN = N * 2;
	fi(i, 0, dN) {
		cin >> durability[i];
		belts[i] = 0;
	}
	f = r = 0;
	broken = 0;
	upArea = 0;
	downArea = N;
	step = 0;
	while (broken < K) {
		step++;
		upArea = (upArea - 1 + dN) % dN;
		downArea = (downArea - 1 + dN) % dN;
		simulate();
	}
	cout << step;
	return 0;
}