#include<iostream>
using namespace std;
#define fi(i, a, b) for(register int i = a; i < b; i++)
#define MAX_N 20
#define MAX_M 400
#define WHO 0
#define UNTIL 1
#define MAX_TIME 1001

struct Shark;
int N, M, K, sharkCount;
#define isValid(r, c) (r >= 0 && c >= 0 && r < N && c < N)

Shark* map[MAX_N][MAX_N];

int smellsMap[MAX_TIME][MAX_N][MAX_N][2];
bool hasSmell(int r, int c, int time, int* who) {
	if(who) *who = 0;
	if (smellsMap[time - 1][r][c][WHO] == 0) return false;
	if (smellsMap[time - 1][r][c][UNTIL] < time) return false;
	if (smellsMap[time - 1][r][c][UNTIL] == time + K) return false;
	if (who) *who = smellsMap[time - 1][r][c][WHO];
	return true;
}

int dir[4][2]{ {-1, 0}, {1, 0}, {0, -1},{0, 1} };
struct Shark {
	int no;
	int r;
	int c;
	int d;
	int isAlive;
	int priority[4][4];
	bool move(int time) {
		// empty room
		fi(_k, 0, 4) {
			int k = priority[d][_k];
			int nr = r + dir[k][0];
			int nc = c + dir[k][1];
			if (!isValid(nr, nc)) continue;
			if (hasSmell(nr, nc, time, 0)) continue;
			go(nr, nc, k, time);
			return true;
		}

		// my smells
		fi(_k, 0, 4) {
			int k = priority[d][_k];
			int nr = r + dir[k][0];
			int nc = c + dir[k][1];
			if (!isValid(nr, nc)) continue;
			int who = 0;
			hasSmell(nr, nc, time, &who);
			if (who != no) continue;
			go(nr, nc, k, time);
			return true;
		}

		// other smells
		fi(_k, 0, 4) {
			int k = priority[d][_k];
			int nr = r + dir[k][0];
			int nc = c + dir[k][1];
			if (!isValid(nr, nc)) continue;
			go(nr, nc, k, time);
			return true;
		}
	}
private:
	bool go(int nr, int nc, int _d, int time) {
		map[r][c] = 0;
		if (map[nr][nc] != 0) {
			if (map[nr][nc]->no < no) {
				isAlive = false;
				sharkCount -= 1;
				return false;
			}
			map[nr][nc]->isAlive -= 1;
			sharkCount -= 1;
		}
		r = nr;
		c = nc;
		d = _d;
		map[nr][nc] = this;
		smellsMap[time][nr][nc][WHO] = no;
		smellsMap[time][nr][nc][UNTIL] = time + K;
		return true;
	}
} sharks[MAX_M + 1];

int simulate() {
	int time = 0;
	sharkCount = M;
	while (sharkCount > 1) {
		time++;
		if (time > 1000) {
			return -1;
		}

		fi(i, 0, N) {
			fi(j, 0, N) {
				if (smellsMap[time - 1][i][j][UNTIL] > time) smellsMap[time][i][j][WHO] = smellsMap[time - 1][i][j][WHO];
				smellsMap[time][i][j][UNTIL] = smellsMap[time - 1][i][j][UNTIL];
			}
		}

		fi(i, 1, M + 1) {
			if (!sharks[i].isAlive) continue;
			sharks[i].move(time);
		}
		{/*
		 cout << "-time" << time << "----" << "		" << "WHO----" << "		" << "UNTIL--" << "		" << endl;
		fi(i, 0, N) {
			fi(j, 0, N) {
				if (map[i][j] == 0) {
					cout << "- ";
					continue;
				}
				cout << map[i][j]->no << " ";
			}
			cout << "		";
			fi(j, 0, N) {
				cout << smellsMap[time][i][j][WHO]<< " ";
			}
			cout << "		";
			fi(j, 0, N) {
				if(smellsMap[time][i][j][UNTIL] - time <= 0) cout << "- ";
				else cout << smellsMap[time][i][j][UNTIL] - time << " ";
			}
			cout << endl;
		}
		cout << endl;
		 */}

	}
	return time;
}
int main() {
	cin >> N >> M >> K;
	fi(i, 0, N) {
		fi(j, 0, N) {
			int no;
			cin >> no;
			if (no == 0) {
				map[i][j] = 0;
				continue;
			}
			sharks[no] = { no, i, j, 0, true };
			map[i][j] = &sharks[no];
			smellsMap[0][i][j][WHO] = no;
			smellsMap[0][i][j][UNTIL] = K;
		}
	}
	fi(i, 1, M + 1) {
		int d;
		cin >> d;
		sharks[i].d = d - 1;
	}
	fi(i, 1, M + 1) {
		fi(j, 0, 4) {
			fi(k, 0, 4) {
				int data;
				cin >> data;
				sharks[i].priority[j][k] = data - 1;
			}
		}
	}
	cout << simulate();
	return 0;
}