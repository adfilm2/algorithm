#include <vector>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

struct Tree {
    int age;
    bool alive;
    Tree(int age) { this->age=age; alive=true; }
    bool operator<(Tree& right) {
        if (alive == right.alive) {
            return age < right.age; 
        }
        return alive > right.alive;
    }
};

int N, M, K;
vector<vector<int> > map;
vector<vector<int> > A;
vector<vector<Tree> > trees;
const int DIR[8][2] = {{-1, -1}, {-1,0}, {-1,1}, {0,-1}, {0,1}, {1,-1}, {1,0}, {1,1}};
int tree_num;

void solve() {

    for (int y=0; y<K; y++) {
        
        vector<vector<int> > add(A.begin(), A.end());
        for (int i=0; i<N*N; i++) {
            bool is_lack = false;
            for (int j=0; j<trees[i].size(); j++) {

                int r = i/N;
                int c = i%N;
                Tree& t = trees[i][j];
                if (!t.alive) continue;
                
                if (map[r][c] < t.age) {
                    is_lack = true;
                    t.alive = false;
                    add[r][c] += (t.age / 2);
                    continue;
                }

                map[r][c] -= t.age;
                t.age++;
            }

            if (is_lack) {
                while (trees[i].size() != 0 && !trees[i].back().alive) {
                    trees[i].pop_back();
                    tree_num--;
                }
            }
        }

        vector<vector<Tree> > cp(trees.begin(), trees.end());
        trees.assign(N*N, vector<Tree>());
        for (int i=0; i<N*N; i++) {
            for (int j=0; j<cp[i].size(); j++) {
                Tree t = cp[i][j];
                int r = i/N;
                int c = i%N;

                if (t.age % 5 != 0) continue ;

                for (int d=0; d<8; d++) {
                    int nr = r + DIR[d][0];
                    int nc = c + DIR[d][1];

                    if (nr<0||nc<0||nr>=N||nc>=N) continue;
                    int nidx = nr*N + nc;
                    trees[nidx].push_back(Tree(1));
                    tree_num++;
                }
            }
        }

        for (int i=0; i<N*N; i++) {
            for (int j=0; j<cp[i].size(); j++) {
                trees[i].push_back(cp[i][j]);
            }
        }

        for (int r=0; r<N; r++) {
            for (int c=0; c<N; c++) {
                map[r][c] += add[r][c];
            }
        }
    }

    std::cout << tree_num;
}

int main() {
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);

    cin >> N >> M >> K;
    map.assign(N, vector<int>(N, 5));
    A.assign(N, vector<int>(N, 0));
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            cin >> A[i][j];
        }
    }

    trees.assign(N*N, vector<Tree>());
    for (int i=0; i<M; i++) {
        int r, c, age;
        cin >> r >> c >> age;
        trees[(r-1)*N+(c-1)].push_back(Tree(age));
    }

    for (int i=0; i<N*N; i++) {
        if (trees[i].size() > 0) {
            std::sort(trees[i].begin(), trees[i].end());
        }
    }

    tree_num = M;
    solve();
    
    return 0;
}