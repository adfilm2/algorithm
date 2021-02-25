#include<iostream>
#include<vector>
#include<functional>
#include<algorithm>
using namespace std;
#define MAX_N 20
#define MAX_AREA 5
#define fi(i, a, b) for(register int i = a; i < b; i++)
#define fie(i, a, b) for(register int i = a; i <= b; i++)
#define between(expr, start, end) (start <= expr && expr <= end)

int N;
int map[MAX_N + 1][MAX_N + 1];
std::function<bool(int r, int c)> area[MAX_AREA + 1];

auto isRange1(int x, int y, int d1, int d2) {
	return [x, y, d1, d2](int r, int c) -> bool{
		return between(r, 1, x + d1 - 1) && between(c, 1, y);
	};
}

auto isRange2(int x, int y, int d1, int d2) {
	return [x, y, d1, d2](int r, int c) -> bool {
		return between(r, 1, x + d2) && between(c, y + 1, N);
	};
}

auto isRange3(int x, int y, int d1, int d2) {
	return [x, y, d1, d2](int r, int c) -> bool {
		return between(r, x + d1, N) && between(c, 1, y - d1 + d2 - 1);
	};
}

auto isRange4(int x, int y, int d1, int d2) {
	return [x, y, d1, d2](int r, int c) -> bool {
		return between(r, x + d2 + 1, N) && between(c, y - d1 + d2, N);
	};
}

auto isRange5(int x, int y, int d1, int d2) {
	return [x, y, d1, d2](int r, int c) -> bool {
		if (!between(r, x, x + d1 + d2) || !between(c, y - d1, y + d2)) return false;
		int diff = r - x;
		int left = y;
		int right = y;
		for (int k = 1; k <= diff; k++) {
			left += k <= d1 ? -1 : 1;
		}
		for (int k = 1; k <= diff; k++) {
			right += k <= d2 ? +1 : -1;
		}
		return between(c, left, right);
	};
}

int run(int x, int y, int d1, int d2) {
	int count[6];
	fie(i, 1, 5) {
		count[i] = 0;
	}
	area[1] = isRange1(x, y, d1, d2);
	area[2] = isRange2(x, y, d1, d2);
	area[3] = isRange3(x, y, d1, d2);
	area[4] = isRange4(x, y, d1, d2);
	area[5] = isRange5(x, y, d1, d2);
	fie(r, 1, N) {
		fie(c, 1, N) {
			for(int k = 5; k >=1; k--) {
				if (area[k](r, c)) {
					count[k] += map[r][c];
					break;
				}
			}
		}
	}
	sort(count + 1, count + 6);
	return count[5] - count[1];
}
int main() {
	cin >> N;
	int total = 0;
	fie(i, 1, N) {
		fie(j, 1, N) {
			cin >> map[i][j];
			total += map[i][j];
		}
	}
	int min = total;
	fie(x, 1, N) {
		fie(y, 1, N) {
			fi(d1, 1, N) {
				fi(d2, 1, N) {
					if (x + d1 + d2 > N || y - d1 <= 0 || y + d2 > N) continue;
					int ret = run(x, y, d1, d2);
					min = min > ret ? ret : min;
				}
			}
		}
	}
	cout << min;
	return 0;
}