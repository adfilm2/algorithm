#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

struct Pos {
    int r, c;
};
int DIR[4][2] = {{0, 1}, {-1, 0}, {0, -1}, {1, 0}};
int board[101][101];

void rotate(vector<Pos> &pos_set, int curve_num) {
    Pos end = pos_set.back();

    vector<Pos> new_pos_set;
    int except_end_size = pos_set.size() - 1;
    for (int i=0; i<except_end_size; i++) {
        Pos rotated = pos_set[i];
        int row_diff = rotated.r - end.r;
        int col_diff = rotated.c - end.c;
        Pos new_pos = { end.r + col_diff, end.c - row_diff };
        board[new_pos.r][new_pos.c] = curve_num;
        new_pos_set.push_back(new_pos);
    }

    int size = new_pos_set.size();
    for (int i=0; i<size; i++) {
        pos_set.push_back(new_pos_set.back());
        new_pos_set.pop_back();
    }
}

int main() {

    int N;
    cin >> N;
    memset(board, 0, sizeof(board));

    int sx, sy, d, g;
    for (int n = 1; n <= N; n++) {
        cin >> sx >> sy >> d >> g;
        Pos start = {sy, sx};
        Pos end = {sy + DIR[d][0], sx + DIR[d][1]};
        vector<Pos> pos_set = {start, end};
        board[start.r][start.c] = n;
        board[end.r][end.c] = n;

        for (int i = 0; i < g; i++) {
            rotate(pos_set, n);
        }
    }

    int cnt = 0;
    for (int r = 0; r < 100; r++) {
        for (int c = 0; c < 100; c++) {
            if (board[r][c] && board[r + 1][c] && board[r][c + 1] && board[r + 1][c + 1]) {
                cnt++;
            }
        }
    }
    cout << cnt;

    return 0;
}