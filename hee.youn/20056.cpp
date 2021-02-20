#include<iostream>
#include<list>
using namespace std;
#define MAX_FIREBALL 10000
#define MAX_N 50
#define MAX_K 1000
#define fi(i, a, b) for(register int i = a; i < b; i++)
#define mod(a, b) ((a % b + b) % b)

struct Pos {
	int r;
	int c;
	Pos operator + (Pos pos) {
		return { r + pos.r, c + pos.c };
	}
	Pos operator * (int s) {
		return { r * s, c * s };
	}
	Pos operator % (int N) {
		return { mod(r, N), mod(c, N) };
	}
};

Pos dir[8]{ {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1} };

struct Fireball {
	Pos pos;
	int m;
	int s;
	int d;
	int cnt;
	bool same;
	int time;
	void merge(Fireball fireball) {
		m += fireball.m;
		s += fireball.s;
		cnt++;
		same = same && (d % 2 == fireball.d % 2);
	}
};

Fireball* add(int time, Fireball fireball, list<Fireball>& fireballs) {
	fireball.time = time;
	fireballs.push_back(fireball);
	list<Fireball>::iterator iter = fireballs.end();
	iter--;
	return &*iter;
}

int N, M, K;

Fireball* map[MAX_N][MAX_N];

Fireball moveFireball(Fireball& fireball) {
	Fireball ret = fireball;
	Pos pos = fireball.pos + dir[fireball.d] * fireball.s;
	ret.pos = pos % N;
	return ret;
}

int collision(Fireball& fireball, list<Fireball>& fireballs) {
	int origin = fireball.m;
	int mass = fireball.m / 5;
	int speed = fireball.s / fireball.cnt;
	if (mass == 0) {
		fireball.m = 0;
		return origin;
	}
	fireball.m = mass;
	fireball.s = speed;
	fireball.d = fireball.same ? 0 : 1;
	fireball.cnt = 1;
	fireball.same = true;
	for (int newDir = fireball.d + 2; newDir < 8; newDir += 2) {
		fireballs.push_back({ fireball.pos, mass, speed, newDir, 1, true });
	}
	return origin - mass * 4;
}
int main() {
	cin >> N >> M >> K;
	int sum = 0;
	list<Fireball> fireballs;
	fi(i, 0, M) {
		int r, c, m, s, d;
		cin >> r >> c >> m >> s >> d;
		sum += m;
		add(0, Fireball{ { r - 1, c - 1 }, m, s, d, 1, true }, fireballs);
	}
	fi(time, 1, K + 1) {
		list<Fireball> prev;
		fi(i, 0, N) {
			fi(j, 0, N) {
				map[i][j] = 0;
			}
		}
		for (list<Fireball>::iterator iter = fireballs.begin(); iter != fireballs.end(); iter++) {
			if ((*iter).m == 0) continue;
			prev.push_back(*iter);
		}
		fireballs.clear();
		for (list<Fireball>::iterator iter = prev.begin(); iter != prev.end(); iter++) {
			Fireball moved = moveFireball(*iter);
			if (map[moved.pos.r][moved.pos.c] != 0) {
				map[moved.pos.r][moved.pos.c]->merge(moved);
				continue;
			}
			map[moved.pos.r][moved.pos.c] = add(time, moved, fireballs);
		}
		for (list<Fireball>::iterator iter = fireballs.begin(); iter != fireballs.end(); iter++) {
			Fireball& cur = *iter;
			if (cur.cnt <= 1) continue;
			sum -= collision(cur, fireballs);
		}
	}
	cout << sum;
	return 0;
}