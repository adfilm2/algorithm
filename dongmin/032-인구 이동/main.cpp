#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;

struct Pos { int r, c; };
int N, L, R;
vector<vector<int> > populations;
const int DIR[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};

void solve() {
    int total_moves = 0;
    int unit_moves = -1;

    while (unit_moves != 0) {
        unit_moves = 0;

        vector<vector<bool> > visited(N, vector<bool>(N, false));
        for (int i=0; i<N; i++) {
            for (int j=0; j<N; j++) {
                if (visited[i][j]) continue ;

                vector<Pos> country_union;
                queue<Pos> q;

                q.push({i,j});
                visited[i][j] = true;
                country_union.push_back({i,j});

                while (!q.empty()) {
                    Pos here = q.front();
                    q.pop();

                    for (int d=0; d<4; d++) {
                        int nr = here.r + DIR[d][0];
                        int nc = here.c + DIR[d][1];
                        if (nr<0 || nc<0 || nr>=N || nc>=N) continue;
                        if (visited[nr][nc]) continue;
                        int diff = abs(populations[here.r][here.c] - populations[nr][nc]);
                        if (diff<L || diff>R) continue ;
                        unit_moves += 1;
                        q.push({nr,nc});
                        visited[nr][nc] = true;
                        country_union.push_back({nr,nc});
                    }
                }

                if (country_union.size() == 1) continue ;
                int avg = 0;
                for (int n=0; n<country_union.size(); n++) {
                    Pos section = country_union[n];
                    avg += populations[section.r][section.c];
                }

                avg /= country_union.size();

                for (int n=0; n<country_union.size(); n++) {
                    Pos section = country_union[n];
                    populations[section.r][section.c] = avg;
                }
            }
        }

        total_moves += (unit_moves > 0);
    }

    cout << total_moves << endl;
}

int main() {
    cin >> N >> L >> R;
    populations.assign(N, vector<int>(N, 0));
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            cin >> populations[i][j];
        }
    }

    solve();
    return 0;
}