#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct MoveInfo {
    int r,c,d,s,z;
    bool alive;
};
struct Shark {
    int id,z;
};

int R, C, M;
const int dir[4][2] = {{-1,0}, {1,0}, {0,1}, {0,-1}};
void capture(vector<vector<vector<Shark> > > &grid, vector<MoveInfo> &sharks, int king, int &z_sum) {

    for(int r=0; r<R; r++) {
        if(grid[r][king].size() != 0) {
            int captured_id = grid[r][king][0].id;
            int captured_z = grid[r][king][0].z;
            grid[r][king].pop_back();

            sharks[captured_id].alive = 0;
            z_sum += captured_z;
            return ;
        }
    }
}

void move(vector<vector<vector<Shark> > > &grid, vector<MoveInfo> &sharks) {

    vector<vector<vector<Shark> > > grid_cp(R, vector<vector<Shark> >(C, vector<Shark>()));
    for(int i=0; i<M; i++) {
        if(sharks[i].alive) {
            int r=sharks[i].r, c=sharks[i].c, d=sharks[i].d, s=sharks[i].s;
            int nr = r + (s % (2*(R-1)))*dir[d][0];
            int nc = c + (s % (2*(C-1)))*dir[d][1];

            if(nr<0) {
                int backward_move = abs(nr);
                if(backward_move>=R) {
                    int forward_move = backward_move - R+1;
                    nr = R-1 - forward_move;
                }
                else {
                    sharks[i].d = d+1;
                    nr = backward_move;
                }
            }
            else if(nc<0) {
                int backward_move = abs(nc);
                if(backward_move>=C) {
                    int forward_move = backward_move - C+1;
                    nc = C-1 - forward_move;
                }
                else {
                    sharks[i].d = d-1;
                    nc = backward_move;
                }
            }
            else if(nr>=R) {
                int backward_move = nr-R+1;
                if(backward_move >=R) {
                    int forward_move = backward_move - R+1;
                    nr = forward_move;
                }
                else {
                    sharks[i].d = d-1;
                    nr = R-1 - backward_move;
                }
            }
            else if(nc>=C) {
                int backward_move = nc-C+1;
                if(backward_move >= C) {
                    int forward_move = backward_move - C+1;
                    nc = forward_move;
                }
                else {
                    sharks[i].d = d+1;
                    nc = C-1 - backward_move;
                }
            }

            sharks[i].r = nr;
            sharks[i].c = nc;
            
            if(grid_cp[nr][nc].size() >= 1) {
                if(grid_cp[nr][nc].back().z < sharks[i].z) {
                    sharks[grid_cp[nr][nc].back().id].alive = 0;
                    grid_cp[nr][nc].pop_back();
                    grid_cp[nr][nc].push_back(Shark{i, sharks[i].z});
                }
                else {
                    sharks[i].alive = 0;
                }
            }
            else {
                grid_cp[nr][nc].push_back(Shark{i, sharks[i].z});
            }
        }
    }
    grid.assign(grid_cp.begin(), grid_cp.end());
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int answer = 0;

    cin >> R >> C >> M;
    vector<vector<vector<Shark> > > grid(R, vector<vector<Shark> >(C, vector<Shark>()));
    vector<MoveInfo> sharks;

    for(int i=0; i<M; i++) {
        int r,c,s,d,z;
        cin >> r >> c >> s >> d >> z;
        grid[r-1][c-1].push_back(Shark{i,z});
        sharks.push_back(MoveInfo{r-1,c-1,d-1,s,z,1});
    }

    for(int king_pos = 0; king_pos<C; king_pos++) {
        capture(grid, sharks, king_pos, answer);
        move(grid, sharks);
    }

    cout << answer;
    return 0;
}