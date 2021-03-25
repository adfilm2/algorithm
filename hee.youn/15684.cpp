#include<iostream>
#define fi(i,a,b) for(int i = a; i < b; i++)
using namespace std;
#define MAX_BEAM 300
#define MAX_N 10
#define MAX_H 30

int map[MAX_H][MAX_N];
int N, H;
bool simulate() {
	fi(i, 0, N) {
		int head = i;
		fi(j, 0, H) {
			head += map[j][head];
		}
		if (head == i) continue;
		return false;
	}
	return true;
}
int ans;
void recursive(int cur, int size) {
	if (size >= ans) { return; }
	if (simulate()) {
		ans = ans > size ? size : ans;
		return;
	}
	fi(k, cur, N*H) {
		int x = k / N;
		int y = k % N;
		if (y + 1 < N && map[x][y] == 0 && map[x][y + 1] == 0) {
			map[x][y] = +1;
			map[x][y + 1] = -1;
			recursive(k + 1, size + 1);
			map[x][y] = 0;
			map[x][y + 1] = 0;
		}
	}
}

int main() {
	int M;
	cin >> N >> M >> H;
	fi(i, 0, M) {
		int x, y;
		cin >> x >> y;
		x -= 1;
		y -= 1;
		map[x][y] = +1;
		map[x][y+1] = -1;
	}
	ans = 4;
	recursive(0, 0);
	if (ans == 4) cout << -1;
	else cout << ans;
	return 0;
}