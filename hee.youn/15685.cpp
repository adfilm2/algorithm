#include<iostream>
#define fi(i, a, b) for(int i = a; i < b; i++)
#define fd(i, a, b) for(int i = a - 1; i >= b; i--)
#define SIZE 100
#define MAX 8196

using namespace std;

bool map[SIZE + 1][SIZE + 1];

int dir[4][2]{ {0, 1}, {-1, 0}, {0, -1}, {1, 0} };
int rotate(int dir) {
	return (dir + 1) % 4;
}

int buf[MAX];
int main() {
	int N;
	cin >> N;
	fi(i, 0, N) {
		int x, y, d, g;
		cin >> x >> y >> d >> g;
		int size = 0;
		buf[size++] = d;
		fi(j, 0, g) {
			fd(k, size, 0) {
				buf[size++] = rotate(buf[k]);
			}
		}
		map[y][x] = true;
		fi(j, 0, size) {
			int d = buf[j];
			y += dir[d][0];
			x += dir[d][1];
			map[y][x] = true;
		}
	}
	int ans = 0;
	fi(i, 0, SIZE) {
		fi(j, 0, SIZE){ 
			if (!map[i][j]) continue;
			if (!map[i + 1][j]) continue;
			if (!map[i][j + 1]) continue;
			if (!map[i + 1][j + 1]) continue;
			ans++;
		}
	}
	cout << ans;
	return 0;
}