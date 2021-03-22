#include<iostream>
#define fi(i, a, b) for(int i = a; i < b; i++)
#define abs(a) ((a) > 0 ? (a) : -(a))
#define MAX_N 50
#define MAX_M 13

#define CUSTOMER 1
#define STORE 2

using namespace std;

int N, M;
int map[MAX_N][MAX_N];

struct Pos {
	int x;
	int y;
};

int distance(Pos a, Pos b) {
	return abs(a.x - b.x) + abs(a.y - b.y);
}

Pos stores[MAX_N*MAX_N];
int storeSize;

Pos customers[MAX_N*MAX_N];
int customerSize;

Pos selected[MAX_M];

int calculate() {
	int ret = 0;
	fi(i, 0, customerSize) {
		Pos customer = customers[i];
		int minDistance = distance(customer, selected[0]);
		fi(j, 1, M) {
			int dis = distance(customer, selected[j]);
			if (minDistance <= dis) continue;
			minDistance = dis;
		}
		ret += minDistance;
	}
	return ret;
}

int recursive(int cur, int size) {
	if (size == M) {
		int ans = calculate();
		return ans;
	}
	int min = MAX_N * MAX_N;
	for (int i = cur; i < storeSize; i++) {
		selected[size] = stores[i];
		int ret = recursive(i + 1, size + 1);
		if (min <= ret) continue;
		min = ret;
	}
	return min;
}
int main() {
	storeSize = 0;

	cin >> N >> M;
	fi(i, 0, N) {
		fi(j, 0, N) {
			cin >> map[i][j];
			if (map[i][j] == STORE) {
				stores[storeSize++] = { i, j };
			}
			else if (map[i][j] == CUSTOMER) {
				customers[customerSize++] = { i, j };
			}
		}
	}
	cout << recursive(0, 0);
	return 0;
}