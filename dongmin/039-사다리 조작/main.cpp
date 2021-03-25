#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>
using namespace std;

struct Pos{int r, c; };
int N, M, H;
int board[32][12];

bool playImpl(int b[32][12], int selected) {
    int current = selected;
    for (int i=1; i<=H; i++) {
        if (b[i][current] == 1) {
            current += 1;
            continue ;
        }
        
        if (current-1 < 0) continue ;
        if (b[i][current-1] == 1) {
            current -= 1;
        }
    }
    return current == selected;
}

bool play(int b[32][12]) {
    for (int i=1; i<=N; i++) {
        if (!playImpl(b,i)) {
            return false; 
        }
    }
    return true;
}

bool searchImpl(vector<Pos>& added) {
    int cpy_board[32][12];
    memcpy(cpy_board, board, sizeof(board));
    for (int i=0; i<added.size(); i++) {
        int r = added[i].r, c = added[i].c;
        cpy_board[r][c] = 1;
    }
    return play(cpy_board);
}

void dfs(vector<bool> &checked, vector<vector<Pos> >& added, int size, int cur, int idx) {
    int len = checked.size();
    if (cur == size) {
        int cpy_board[32][12];
        memcpy(cpy_board, board, sizeof(board));
        vector<Pos> add_pos;
        for (int i=0; i<len; i++) {
            if (!checked[i]) continue ;
            int r = i / (N-1) + 1;
            int c = i % (N-1) + 1;
            if (cpy_board[r][c] == 1) return ;
            if (cpy_board[r][c-1] == 1) return ;
            if (cpy_board[r][c+1] == 1) return ;
            cpy_board[r][c] = 1;
            add_pos.push_back({r,c});
        }

        added.push_back(add_pos);
        return ;
    }
    for (int i = idx; i < len; i++) {
        if (checked[i] == true) continue ;
        int r = i / (N-1) + 1;
        int c = i % (N-1) + 1;
        if (board[r][c] == 1) continue ;
        if (board[r][c-1] == 1) continue ;
        if (board[r][c+1] == 1) continue ;

        checked[i] = true;
        dfs(checked, added, size, cur+1, i);
        checked[i] = false;
    }
}

bool search(int selected_size) {
    vector<bool> checked((N-1)*H, 0);
    vector<vector<Pos> > added;

    dfs(checked, added, selected_size, 0, 0);

    for (int i=0; i<added.size(); i++) {
        if (searchImpl(added[i])) {
            return true;
        }
    }
    return false;
}

int solve() {
    if (play(board)) return 0;

    for (int size = 1; size <=3; size++) {
        if (search(size)) {
            return size;
        }
    }

    return -1;
}

int main() {
    
    cin >> N >> M >> H;
    
    memset(board, -1, sizeof(board));
    for (int i=1; i<=H; i++) {
        for (int j=1; j<N; j++) {
            board[i][j] = 0;
        }
    }

    for (int i=0; i<M; i++) {
        int a,b;
        cin >> a >> b;
        board[a][b] = 1;
    }

    int answer = solve();
    cout << answer;
    return 0;
}
