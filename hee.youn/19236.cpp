#include<iostream>
#include<string>
using namespace std;
#define fi(i, a, b) for(register int i = a; i < b; i++)
#define N 4
#define M 16

string direction[]{ "↑", "↖", "←", "↙", "↓", "↘", "→", "↗" };
short dir[8][2]{ {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1} };

struct Fish;

void swap(Fish* map[N][N], short r1, short c1, short r2, short c2);

struct Shark {
	short r;
	short c;
	short d;
	Shark move(short distance) {
		short nr = r + dir[d][0] * distance;
		short nc = c + dir[d][1] * distance;
		return { nr, nc, d };
	}
};
#define noShark(a,b, shark) !(shark->r == a && shark->c == b)
#define isValid(r, c) (r >= 0 && c>=0 && r < N && c < N)

struct Fish {
	short no;
	short r;
	short c;
	short d;
	bool isAlive;
	void move(Shark* shark, Fish* map[N][N]) {
		fi(k, 0, 8) {
			short nr = r + dir[d][0];
			short nc = c + dir[d][1];
			if (isValid(nr, nc) && noShark(nr, nc, shark)) {
				swap(map, r, c, nr, nc);
				break;
			}
			d = (d + 1) % 8;
		}
	}
};

Fish mFish[1000][16];
Fish mFish2[1000][16];
Shark mShark[1000];

void printMemory(int level) {
	Shark* shark = &mShark[level];
	cout << "shark :" << shark->r << ", " << shark->c << endl;

	Fish* _map[N][N];
	fi(i, 0, N) {
		fi(j, 0, N) {
			_map[i][j] = 0;
		}
	}
	fi(k, 0, 16) {
		Fish* fish = &mFish[level][k];
		if (!fish->isAlive) 	continue;

		_map[fish->r][fish->c] = fish;
	}

	fi(i, 0, N) {
		fi(j, 0, N) {
			if (shark && i == shark->r && j == shark->c) {
				cout << "S " << direction[shark->d] << "	";
				continue;
			}
			if (_map[i][j] == 0) {
				cout << "-	";
				continue;
			}
			cout << _map[i][j]->no + 1 << " " << direction[_map[i][j]->d] << "	";
		}
		cout << endl;
	}
	cout << endl;
}

void dfs(int sum, int level, int* max) {
	if (sum > *max) {
		*max = sum;
	}
	Fish* map[N][N];
	// prerequisite
	fi(i, 0, N) {
		fi(j, 0, N) {
			map[i][j] = 0;
		}
	}
	fi(k, 0, 16) {
		mFish[level + 1][k] = mFish[level][k];
		Fish* fish = &mFish[level + 1][k];
		if (!fish->isAlive) continue;
		map[fish->r][fish->c] = fish;
	}
	Shark* shark = &mShark[level];

	// move fish
	fi(i, 0, 16) {
		if (!mFish[level + 1][i].isAlive) continue;
		mFish[level + 1][i].move(shark, map);
	}
	// move shark
	fi(distance, 1, M) {
		mShark[level + 1] = shark->move(distance);
		Shark* nxt = &mShark[level + 1];
		if (!isValid(nxt->r, nxt->c)) break;
		if (map[nxt->r][nxt->c] == 0) continue;
		Fish* feed = map[nxt->r][nxt->c];
		nxt->d = feed->d;
		feed->isAlive = false;
		dfs(sum + feed->no + 1, level + 1, max);
		feed->isAlive = true;
	}
}
int main() {
	short num, dir;
	Fish* start;
	fi(i, 0, N) {
		fi(j, 0, N) {
			cin >> num >> dir;
			num -= 1;
			dir -= 1;
			mFish[0][num] = { num, (short)i, (short)j, dir, true };
			if (i == 0 && j == 0) {
				start = &mFish[0][num];
			}
		}
	}
	int ans = 0;

	mShark[0] = { 0,0, start->d };
	start->isAlive = false;
	dfs(start->no + 1, 0, &ans);
	cout << ans;
	return 0;
}

void swap(Fish* map[N][N], short r1, short c1, short r2, short c2) {
	Fish* tmp = map[r1][c1];
	map[r1][c1] = map[r2][c2];
	map[r2][c2] = tmp;
	if (map[r1][c1]) {
		map[r1][c1]->r = r1;
		map[r1][c1]->c = c1;
	}
	if (map[r2][c2]) {
		map[r2][c2]->r = r2;
		map[r2][c2]->c = c2;
	}
}