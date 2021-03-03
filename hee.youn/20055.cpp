#include<iostream>
using namespace std;

#define fi(i, a, b) for(register int i = a; i < b; i++)
#define mod(a, b) (((a) % (b) + (b)) % (b))
#define MAX_N 100
#define MAX_2_N 200
#define MAX_ROBOT 10000000

int N, _2N;

struct Robot;

struct Belt {
	int pos;
	int durability;
	Robot* robot;
	bool unable() {
		return robot || durability == 0;
	}
};

struct Robot {
	Belt* belt;
	bool arrived(int downArea) {
		if (belt->pos == downArea) return true;
		int next = mod(belt->pos + 1, _2N);
		return next == downArea;
	}
	int getPos() {
		return belt->pos;
	}
	int nextPos() {
		return mod(belt->pos + 1, _2N);
	}
	void move(Belt* nextBelt) {
		belt->robot = 0;
		nextBelt->robot = this;
		nextBelt->durability -= 1;
		belt = nextBelt;
	}
};

Robot robots[MAX_ROBOT];
int f, r;

void addRobot(Belt* belt) {
	robots[r].belt = belt;
	belt->durability -= 1;
	belt->robot = &robots[r];
	r++;
}

void popRobot() {
	robots[f].belt->robot = 0;
	f++;
}

struct ConveySystem {
	int upArea;
	int downArea;
	Belt belts[MAX_2_N];
	int broken = 0;

	bool isValid(int K) {
		return broken < K;
	}

	void action() {
		upArea = mod(upArea - 1, _2N);
		downArea = mod(downArea - 1, _2N);

		while (f < r && robots[f].arrived(downArea)) { popRobot(); }

		fi(i, f, r) {
			int next = robots[i].nextPos();
			if (belts[next].unable()) continue;
			robots[i].move(&belts[next]);
			if (robots[i].belt->durability > 0) continue;
			broken++;
		}
		if (belts[upArea].unable()) return;
		addRobot(&belts[upArea]);
		if (belts[upArea].durability > 0) return;
		broken++;
		return;
	}
};

int main() {
	int K;
	cin >> N >> K;
	_2N = N * 2;
	ConveySystem system{ 0, N };
	fi(i, 0, _2N) {
		int durability;
		cin >> durability;
		system.belts[i] = { i, durability, 0 };
	}
	f = r = 0;
	for (int step = 1; ; step++) {
		system.action();
		if (system.isValid(K)) continue;
		cout << step;
		return 0;
	}
	return 0;
}