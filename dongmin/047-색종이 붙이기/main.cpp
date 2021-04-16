#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

const int PAPER = 10;
int color_paper[6] = {0, 5, 5, 5, 5, 5};

bool isValid(int r, int c) {
    return r>=0 && r<PAPER && c>=0 && c<PAPER;
}

bool canCover(int r, int c, int size, vector<vector<int> > &paper) {
    for (int i=r; i<r+size; i++) {
        for (int j=c; j<c+size; j++) {
            if (!isValid(i, j)) return false;
            if (paper[i][j] == 0) return false;
        }
    }
    return true;
}

void mark(int r, int c, int size, vector<vector<int> > &paper) {
    for (int i=r; i<r+size; i++) {
        for (int j=c; j<c+size; j++) {
            paper[i][j] = 0;
        }
    }
}

void unmark(int r, int c, int size, vector<vector<int> > &paper) {
    for (int i=r; i<r+size; i++) {
        for (int j=c; j<c+size; j++) {
            paper[i][j] = 1;
        }
    }
}

void dfs(int depth, int r, int c, int total, vector<vector<int> > paper, int &min) {
    if (total == 0) {
        if (min > depth) {
            min = depth;
        }
        return ;
    }

    for (int i=r; i<PAPER; i++) {
        for (int j=0; j<PAPER; j++) {
            if (paper[i][j]) {
                for (int s=1; s<=5; s++) {
                    if (!canCover(i, j, s, paper)) break;
                    if (color_paper[s] == 0) continue;
                    color_paper[s]--;
                    mark(i, j, s, paper);
                    dfs(depth+1, i, j, total-s*s, paper, min);
                    unmark(i, j, s, paper);
                    color_paper[s]++;
                }
                return ;
            }
        }
    }
}

void solve(int total, vector<vector<int> > paper) {
    int min = 25;
    dfs(0, 0, 0, total, paper, min);
    if (min == 25) {
        cout << "-1\n";
        return;
    }
    cout << min << endl;
}

int main() {
    vector<vector<int> > paper(PAPER, vector<int>(PAPER, 0));
    int total = 0;

    for (int i=0; i<PAPER; i++) {
        for (int j=0; j<PAPER; j++) {
            cin >> paper[i][j];
            if (paper[i][j]) total++;
        }
    }

    solve(total, paper);
    return 0;
}