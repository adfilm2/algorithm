#include<iostream>
#include<algorithm>
#include<functional>
using namespace std;
#define MAX 100
#define MAX_NODE 200
#define fi(i, a, b) for(register int i = a; i < b; i++)
#define R 0
#define C 1
int N, M;
int arr[MAX][MAX];

struct Node {
	int num;
	int count;
	bool operator <(Node node) {
		if (count == node.count) return num < node.num;
		return count < node.count;
	}
} nodes[MAX_NODE];

Node* cntArr[MAX + 1];
auto getFunc(int type) {
	return [type](int r, int c) -> int {
		return type == R ? arr[r][c] : arr[c][r];
	};
}
auto setFunc(int type) {
	return [type](int r, int c, int v) -> void {
		if (type == R) {
			arr[r][c] = v;
		}
		else {
			arr[c][r] = v;
		}
		return;
	};
}
void run() {
	int type = N >= M ? R : C;
	std::function<int(int r, int c)> get = getFunc(type);
	std::function<void(int r, int c, int v)> set = setFunc(type);
	int NM = type == R ? M : N;
	int maxLen = 3;
	fi(i, 0, N + M - NM) {
		int nodeSize = 0;
		fi(k, 0, 101) {
			cntArr[k] = 0;
		}
		fi(j, 0, NM) {
			int value = get(i, j);
			if (value == 0) continue;
			if (cntArr[value] == 0) {
				nodes[nodeSize] = { value, 0 };
				cntArr[value] = &nodes[nodeSize];
				nodeSize++;
			}
			cntArr[value]->count++;
		}
		sort(nodes, nodes + nodeSize);
		int len = 0;
		fi(j, 0, nodeSize) {
			Node cur = nodes[j];
			set(i, len, cur.num);
			set(i, len + 1, cur.count);
			len += 2;
			if (len == 100) break;
		}
		maxLen = maxLen > len ? maxLen : len;
		for (; len < NM; len++) {
			set(i, len, 0);
		}
	}
	if (type == R) {
		M = maxLen;
	}
	else {
		N = maxLen;
	}
	return;
}
int main() {
	freopen("input.txt", "r", stdin);
	int r, c, k;
	cin >> r >> c >> k;
	r -= 1;
	c -= 1;
	N = M = 3;
	fi(i, 0, N) {
		fi(j, 0, M) {
			cin >> arr[i][j];
		}
	}
	fi(cnt, 0, 101) {
		if (arr[r][c] == k) {
			cout << cnt;
			return 0;
		}
		run();
	}
	cout << -1;
	return 0;
}