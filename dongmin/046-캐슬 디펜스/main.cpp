#include <iostream>
#include <vector>
#include <set>
using namespace std;

bool isValid(int r, int c, int n, int m) {
    return r>=0 && r<n && c>=0 && c<m;
}

int attack(int n, int m, int d, vector<int> &p, vector<vector<int> > &map) {
    struct Pos {
        int r,c;
        bool operator<(const Pos& a) const {
            if (this->r == a.r) return this->c < a.c;
            return this->r < a.r;
        }
    };

    set<Pos> eliminated;
    
    for (int i=0; i<3; i++) {
        int pos = p[i];
        bool find = false;
        int r = n, c = pos;
        for (int dist = 1; dist <= d; dist++) {
            for (int dc = -dist+1; dc <=dist-1; dc++) {
                int dr = -(dist - abs(dc));
                int pr = r + dr;
                int pc = c + dc;

                if (!isValid(pr, pc, n, m)) continue; 
                if (map[pr][pc]) {
                    eliminated.insert(Pos{pr, pc});
                    find = true;
                    break ;
                }
            }

            if (find) break ;
        }  
    }

    for (auto enemy: eliminated) {
        map[enemy.r][enemy.c] = 0;
    }

    return eliminated.size();
}

int move(int n, int m, vector<vector<int> > &map) {
    
    int sum = 0;
    vector<vector<int> > new_map(n, vector<int>(m, 0));

    for (int j=0; j<m; j++) {
        if (map[n-1][j]) sum ++;
    }

    for (int i=0; i<n-1; i++) {
        new_map[i+1].assign(map[i].begin(), map[i].end());
    }

    map.assign(new_map.begin(), new_map.end());
    return sum;
}

int startGame(int n, int m, int d, int e, vector<int> &p, vector<vector<int> > map) {
    
    int sum = 0;
    while (e > 0) {
        int eliminated = attack(n, m, d, p, map);
        int outside = move(n, m, map);
        int total = eliminated + outside;
        e -= total;
        sum += eliminated;
    }

    return sum;
}

void dfs(int depth, int pick, int n, int m, int d, int enemy, vector<int> &p, vector<vector<int> > &map, int &max) {

    if (depth == 3) {
        int eliminated = startGame(n, m, d, enemy, p, map);
        if (eliminated > max) {
            max = eliminated;
        }
        return ;
    }

    for (int i=pick+1; i<m; i++) {
        p.push_back(i);
        dfs(depth+1, i, n, m, d, enemy, p, map, max);
        p.pop_back();
    }
}

void solve(int n, int m, int d, int enemy, vector<vector<int> > map) {
    //궁수배치
    int max = 0;
    vector<int> pos;
    dfs(0, -1, n, m, d, enemy, pos, map, max);
    cout << max << endl;
}

int main() {
    int N, M, D;
    vector<vector<int> > map;
    int enemy = 0;

    cin >> N >> M >> D;
    map.assign(N, vector<int>(M, 0));
    for (int i=0; i<N; i++) {
        for (int j=0; j<M; j++) {
            cin >> map[i][j];
            if (map[i][j] == 1) enemy++;
        }
    }

    solve(N, M, D, enemy, map);
    return 0;
}