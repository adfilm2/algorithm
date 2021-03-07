#include <iostream>
#include <string>
#include <vector>
#include <cstdio>
using namespace std;

struct Shark {
    int r,c,d;
    bool alive;
    int priority[4][4] = {0,};

    Shark(int r, int c, int d, bool alive) {
        this->r = r;
        this->c = c;
        this->d = d;
        this->alive = alive;
    }
};
struct Smell {
    int shark;
    int time;
};

const int DIR[4][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}};
int N, M, k;
vector<Shark> sharks;
vector<vector<Smell> > smell_map;
int remained;

void solve() {
    int time = 1001;
    for (int t=0; t<1000; t++) {
        for (int s=M; s>=1; s--) {
            bool is_blank = false;
            Shark& shark = sharks[s];
            if (!shark.alive) continue;

            for (int i=0; i<4; i++) {
                int nr = shark.r + DIR[shark.priority[shark.d][i]][0];
                int nc = shark.c + DIR[shark.priority[shark.d][i]][1];
                if (nr<0||nr>=N||nc<0||nc>=N) continue;

                if (smell_map[nr][nc].shark == 0 || (smell_map[nr][nc].shark > s && smell_map[nr][nc].time == 0)) {
                    is_blank = true;
                    if (smell_map[nr][nc].shark > 0) {
                        sharks[smell_map[nr][nc].shark].alive = false;
                        remained--;
                    }

                    smell_map[nr][nc].shark = s;
                    shark.d = shark.priority[shark.d][i];
                    shark.r = nr;
                    shark.c = nc;
                    break ;
                }
            }

            if (is_blank) continue;
            for (int i=0; i<4; i++) {
                int nr = shark.r + DIR[shark.priority[shark.d][i]][0];
                int nc = shark.c + DIR[shark.priority[shark.d][i]][1];
                if (nr<0||nr>=N||nc<0||nc>=N) continue;

                if (smell_map[nr][nc].shark == s) {
                    shark.d = shark.priority[shark.d][i];
                    shark.r = nr;
                    shark.c = nc;
                    break ;
                }
            }
        }

        for (int i=0; i<N; i++) {
            for (int j=0; j<N; j++) {
                if (smell_map[i][j].shark == 0) continue;
                smell_map[i][j].time -= 1;
                if (smell_map[i][j].time == 0) {
                    smell_map[i][j].shark = 0;
                } 
            }
        }

        for (int s=1; s<=M; s++) {
            if (!sharks[s].alive) continue;
            smell_map[sharks[s].r][sharks[s].c].shark = s;
            smell_map[sharks[s].r][sharks[s].c].time = k;
        }

        if (remained == 1) {
            time = t+1;
            break ;
        }
    }

    if (time == 1001) {
        time = -1;
    }
    cout << time;
}


int main() {

    cin >> N >> M >> k;
    smell_map.assign(N, vector<Smell>(N, {0, 0}));
    sharks.assign(M+1, Shark(0,0,0,true));
    remained = M;
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            cin >> smell_map[i][j].shark;
            if (smell_map[i][j].shark != 0) {
                int num = smell_map[i][j].shark;
                sharks[num].r = i;
                sharks[num].c = j;
                smell_map[i][j].time = k;
            }
        }
    }

    int d;
    for (int i=1; i<=M; i++) {
        cin >> d;
        sharks[i].d = d-1;
    }

    for (int s=1; s<=M; s++) {
        for (int i=0; i<4; i++) {
            for (int j=0; j<4; j++) {
                cin >> d;
                sharks[s].priority[i][j] = d-1;
            }
        }
    }

    solve();
    return 0;
}