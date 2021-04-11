#include <iostream>
#include <vector>
using namespace std;

enum ROT{ HOR=0, VER, DIA };

int go[3][2] = {{0,1}, {1,0}, {1,1}};
vector<vector<vector<int> > > must_empty = { { {0,1} }, { {1,0} }, { {0,1}, {1,0}, {1,1} }};

struct Pos {int r,c;};
struct State {
    Pos p;
    ROT r;
};

int ans = 0;

bool canGo(Pos p, vector<vector<int> >& house, int N) {
    return p.r >= 0 && p.r < N && p.c >= 0 && p.c < N && house[p.r][p.c] == 0;
} 

void recursive(ROT rot, State s, int N, vector<vector<int> >& house) {

    int dir = rot;
    int len = must_empty[dir].size();
    for (int i=0; i<len; i++) {
        if (!canGo(Pos {s.p.r + must_empty[dir][i][0], s.p.c + must_empty[dir][i][1]}, house, N)) {
            return ;
        }
    }

    State new_state = State{Pos{ s.p.r + go[dir][0], s.p.c + go[dir][1] }, rot};
    if (new_state.p.r == N-1 && new_state.p.c == N-1) {
        ans++;
        return ;
    }

    if (rot == ROT::HOR) {
        recursive(ROT::HOR, new_state, N, house);
        recursive(ROT::DIA, new_state, N, house);
    } else if (rot == ROT::VER) {
        recursive(ROT::VER, new_state, N, house);
        recursive(ROT::DIA, new_state, N, house);
    } else {
        recursive(ROT::HOR, new_state, N, house);
        recursive(ROT::VER, new_state, N, house);
        recursive(ROT::DIA, new_state, N, house);
    }
}

void solve(int N, vector<vector<int> >& house) {
    State init = { Pos{0,1}, ROT::HOR };
    recursive(ROT::HOR, init, N, house);
    recursive(ROT::DIA, init, N, house);
    cout << ans << endl;
}

int main() {
    int N;
    cin >> N;
    vector<vector<int> > house(N, vector<int>(N, 0));
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            cin >> house[i][j];
        }
    }

    solve(N, house);
    return 0;
}