#include<iostream>
using namespace std;
#define fi(i, a, b) for(register int i = a; i < b; i++)
#define MAX 50

int N, M;

struct Disk {
	int no;
	int head;
	int value[MAX];
} disks[MAX];

bool side(Disk* disk, Disk* sideDisk, int i, int* ret) {
	int diff = sideDisk->head - disk->head;
	*ret = (i + diff + M) % M;
	return true;
}

void remove(Disk* disk, int pos, int *cnt, int *sum) {
	*cnt -= 1;
	*sum -= disk->value[pos];
	disk->value[pos] = 0;
}
bool visit[MAX][MAX];
bool dfs(Disk* disk, int cur, int target, int *cnt, int *sum) {
	bool alone = true;
	int left = (cur - 1 + M) % M;
	if (target == disk->value[left]) {
		remove(disk, left, cnt, sum);
		dfs(disk, left, target, cnt, sum);
		alone = false;
	}
	int right = (cur + 1) % M;
	if (target == disk->value[right]) {
		remove(disk, right, cnt, sum);
		dfs(disk, right, target, cnt, sum);
		alone = false;
	}
	if (disk->no + 1 < N) {
		int pos;
		Disk* out = &disks[disk->no + 1];
		if (side(disk, out, cur, &pos)) {
			if (target == out->value[pos]) {
				remove(out, pos, cnt, sum);
				dfs(out, pos, target, cnt, sum);
				alone = false;
			}
		}
	}
	if (disk->no - 1 >= 0) {
		int pos;
		Disk* in = &disks[disk->no - 1];
		if (side(disk, in, cur, &pos)) {
			if (target == in->value[pos]) {
				remove(in, pos, cnt, sum);
				dfs(in, pos, target, cnt, sum);
				alone = false;
			}
		}
	}
	return alone;
}
void arrange(int* cnt, int *sum) {
	int _sum = *sum;
	fi(k, 0, M) {
		fi(i, 0, N) {
			int j = (k + disks[i].head) % M;
			if (disks[i].value[j] == 0) continue;
			bool alone = dfs(&disks[i], j, disks[i].value[j] , cnt, sum);
			if (alone) continue;
		}
	}
	if (*sum == _sum) {
		if (cnt == 0) return;
		float avg =(float)*sum / *cnt;
		fi(k, 0, M) {
			fi(i, 0, N) {
				int j = (k + disks[i].head) % M;
				if (disks[i].value[j] == 0) continue;
				if (disks[i].value[j] == avg) continue;
				int diff = disks[i].value[j] > avg ? -1 : 1;
				disks[i].value[j] += diff;
				*sum += diff;
			}
		}
	}
}

int dir[2]{ -1, 1 };
int main() {
	int sum = 0, cnt = 0;
	int T;
	cin >> N >> M >> T;
	fi(i, 0, N) {
		disks[i].no = i;
		disks[i].head = 0;
		fi(j, 0, M) {
			cin >> disks[i].value[j];
			sum += disks[i].value[j];
			cnt++;
		}
	}
	int x, d, k;
	fi(_t, 0, T) {
		cin >> x >> d >> k;
		int move = dir[d] * k;
		for (int i = x - 1; i < N; i += x) {
			disks[i].head = (disks[i].head + move + M) % M;
		}
		arrange(&cnt, &sum);
	}
	cout << sum;
	return 0;
}