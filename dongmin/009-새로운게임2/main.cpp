#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Board {
    int color;
    vector<int> units;

    vector<int> popUnitsAboveN(int n) {
        vector<int> ret;

        for (int i=0; i<units.size(); i++) {
            if (units[i] == n) {
                ret = vector<int>(units.begin()+i, units.end());

                if (i==0) {
                    units.clear();
                }
                else {
                    units = vector<int>(units.begin(), units.begin()+i);
                }
                break;
            } 
        }

        return ret;
    }
};

struct Unit {
    int r, c, d;
    Unit(int r, int c, int d) {
        this->r = r;
        this->c = c;
        this->d = d;
    }

    void flipDirection() {
        d = (d%2 == 0) ? d+1 : d-1;
    }
};

int N, K;
int dir[4][2] = { {0,1}, {0, -1}, {-1, 0}, {1, 0} };
vector<Unit> units;
vector<vector<Board> > board;

void init() {
    cin >> N >> K;
    board.assign(N, vector<Board>(N, Board{0,vector<int>()}));
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            int color;
            cin >> color;
            board[i][j].color = color;
        }
    }

    for (int i=0; i<K; i++) {
        int r, c, d;
        cin >> r >> c >> d;
        units.push_back(Unit(r-1, c-1, d-1));
        board[r-1][c-1].units.push_back(i);
    }
}

bool isValidPos(int r, int c) {
    return r>=0 && r<N && c>=0 && c<N;
}

void processWhite(int unitNum, int row, int col) {

    vector<int> aboveUnitNum = board[units[unitNum].r][units[unitNum].c].popUnitsAboveN(unitNum);
    for (int i=0; i<aboveUnitNum.size(); i++) {
        int unit = aboveUnitNum[i];
        board[row][col].units.push_back(unit);
        units[unit].r = row;
        units[unit].c = col;
    }
}

void processRed(int unitNum, int row, int col) {

    vector<int> aboveUnitNum = board[units[unitNum].r][units[unitNum].c].popUnitsAboveN(unitNum);
    for (int i=aboveUnitNum.size()-1; i>=0; i--) {
        int unit = aboveUnitNum[i];
        board[row][col].units.push_back(unit);
        units[unit].r = row;
        units[unit].c = col;
    }
}

void processBlue(int unitNum) {

    units[unitNum].flipDirection();
    int nr = units[unitNum].r + dir[units[unitNum].d][0];
    int nc = units[unitNum].c + dir[units[unitNum].d][1];

    if (isValidPos(nr, nc)) {
        if (board[nr][nc].color == 0) {
            processWhite(unitNum,nr,nc);
        }
        else if (board[nr][nc].color == 1) {
            processRed(unitNum,nr,nc);
        }
    }
}

int processTurn() {

    for (int i=0; i<K; i++) {
        int nr = units[i].r + dir[units[i].d][0];
        int nc = units[i].c + dir[units[i].d][1];

        if (isValidPos(nr, nc)) {
            if (board[nr][nc].color == 0) {
                processWhite(i, nr, nc);
            }
            else if (board[nr][nc].color == 1) {
                processRed(i,nr,nc);
            }
            else {
                processBlue(i);
            }
        }
        else {
            processBlue(i);
        }

        if (board[units[i].r][units[i].c].units.size() >= 4) {
            return 1;
        }
    }
    return 0;
}

void solve() {
    int turn = 0;

    while (true) {
        turn += 1;
        int overFour = processTurn();
        if (overFour) {
            break;
        }
        if (turn > 1000) { turn = -1; break;}
    }

    cout << turn;
}

int main() {
    init();
    solve();
    return 0;
}