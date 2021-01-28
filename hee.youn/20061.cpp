#include<iostream>
using namespace std;
#define fi(i, a, b) for(register int i = a; i < b; i++)
#define row_filled(arr, i) (arr[i][0] & arr[i][1] & arr[i][2] & arr[i][3])
#define row_exist(arr, i) (arr[i][0] | arr[i][1] | arr[i][2] | arr[i][3])

int N;

bool blue[8][4];
bool green[8][4];


void getXY(int type, int x, int y, int*x1, int *x2, int *y1, int *y2) {
	switch (type) {
	case 1:
		*x1 = *x2 = x;
		*y1 = *y2 = y;
		break;
	case 2:
		*x1 = *x2 = x;
		*y1 = y;
		*y2 = y + 1;
		break;
	default:
		*x1 = x;
		*x2 = x + 1;
		*y1 = *y2 = y;
		break;
	}
}
bool moveable(bool arr[8][4], int x1,int y1, int x2, int y2) {
	if (x2 + 1 == 8) return false;
	return !arr[x2 + 1][y1] && (!arr[x1 + 1][y2] || x1 != x2);
}
void put(bool arr[8][4], int type, int x, int y) {
	int x1, x2, y1, y2;
	getXY(type, x, y, &x1, &x2, &y1, &y2);
	// green
	int gx1, gx2, gy1, gy2;
	gx1 = 0;
	gx2 = x2 - x1;
	gy1 = y1;
	gy2 = y2;
	while (moveable(arr, gx1,gy1,gx2,gy2)) {
		gx1 += 1;
		gx2 += 1;
	}
	arr[gx1][gy1] = true;
	arr[gx2][gy2] = true;
}
int arrange(bool arr[8][4]) {
	int score = 0;
	while (true) {
		// Row
		int row_hit = 0;
		fi(i, 4, 8) {
			if (row_filled(arr, i)) {
				score++;
				row_hit |= 1 << i;
			}
		}
		if (row_hit == 0) break;
		// clear Row and Move
		fi(i, 4, 8) {
			if ((row_hit & (1 << i)) == 0) continue;
			row_hit -= (1 << i);
			for (register int k = i; k > 0; k--) {
				fi(j, 0, 4) {
					arr[k][j] = arr[k - 1][j];
				}
			}
			fi(j, 0, 4) {
				arr[0][j] = 0;
			}
			i -= 1;
		}
	}
	return score;
}
void shift(bool arr[8][4]) {
	int shift_count = 0;
	if (row_exist(arr, 2)) shift_count++;
	if (row_exist(arr, 3)) shift_count++;
	for (register int i = 7; i >= 4; i--) {
		fi(j, 0, 4) {
			arr[i][j] = arr[i - shift_count][j];
		}
	}
	fi(j, 0, 4) {
		arr[0][j] = arr[1][j] = arr[2][j] = arr[3][j] = 0;
	}
}
void printmap() {
	return;
	fi(i, 0, 8) {
		fi(j, 0, 4) {
			cout << (green[i][j] ? "■" : "□")<< " ";
		}
		cout << "		";
		fi(j, 0, 4) {
			cout << (blue[i][j] ? "■" : "□")<< " ";
		}
		cout << endl;
	}
	cout << endl;
}
int main() {
	int N;
	cin >> N;
	int t, x, y;
	int score = 0;
	fi(i, 0, N) {
		cin >> t >> x >> y;
		put(green, t, x, y);
		if (t == 2 || t == 3) t = 5 - t;
		put(blue, t, y, x);
		score += arrange(green);
		score += arrange(blue);
		shift(green);
		shift(blue);
	}
	int count = 0;
	fi(i, 4, 8) {
		fi(j, 0, 4) {
			if (green[i][j]) count++;
			if (blue[i][j]) count++;
		}
	}
	cout << score << endl << count;
	return 0;
}