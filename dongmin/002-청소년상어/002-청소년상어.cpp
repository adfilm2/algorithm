#include <iostream>
#include <vector>
using namespace std;

typedef struct Fish {
    int r,c,d;
    bool is_alive;
} Fish;
const int DIRECTION[8][2] = { {-1,0}, {-1,-1}, {0,-1}, {1,-1}, {1,0}, {1,1}, {0,1}, {-1,1} };

bool isValidPos(int r, int c) {
    return r>=0 && r<4 && c>=0 && c<4;
}

/**
 * dfs 탐색을 isValidPos로 미리 거르면 안됨. 탐색 후에 탐색 노드 내에서 먹은 물고기 합 계산하고 걸러야 함
 */
void dfs(vector<vector<int> > map, vector<Fish> fishes, int r, int c, int sum, int& max_fish_sum) {

    if (!isValidPos(r, c) || map[r][c] == 0) {
        if (sum > max_fish_sum) {
            max_fish_sum = sum;
        }
        return ;
    }
    else {
        int eaten_fish = map[r][c];
        int shark_dir = fishes[eaten_fish].d;
        map[r][c] = 0;
        fishes[eaten_fish].is_alive = 0;

        for (int fn=1; fn<=16; fn++) {

            if (fishes[fn].is_alive) {
                bool cant_move = false;
                int nd = fishes[fn].d;
                int nr = fishes[fn].r + DIRECTION[nd][0];
                int nc = fishes[fn].c + DIRECTION[nd][1];

                while ((nr==r && nc==c) || !isValidPos(nr,nc)) {
                    nd = (nd+1) % 8;
                    if (nd == fishes[fn].d){
                        cant_move = true;
                        break;
                    }

                    nr = fishes[fn].r + DIRECTION[nd][0];
                    nc = fishes[fn].c + DIRECTION[nd][1];
                }

                if (cant_move) continue;
                int next_number = map[nr][nc];
                
                map[fishes[fn].r][fishes[fn].c] = next_number;
                map[nr][nc] = fn;

                if (next_number > 0) {
                    fishes[next_number].r = fishes[fn].r;
                    fishes[next_number].c = fishes[fn].c;
                }

                fishes[fn] = {nr, nc, nd, 1};
            }
        }

        for (int mult = 1; mult < 4; mult++) {
            int nr = r + DIRECTION[shark_dir][0] * mult;
            int nc = c + DIRECTION[shark_dir][1] * mult;

            dfs(map, fishes, nr, nc, sum+eaten_fish, max_fish_sum);
            
        }
    }
}

int main() {
    
    vector<vector<int> > map;
    vector<Fish> fishes;
    map.assign(4, vector<int>(4, 0));
    fishes.assign(17, {0,0,0,1});

    for (int r=0; r<4; r++) {
        for (int c=0; c<4; c++) {
            int fish_num, direction;
            cin >> fish_num >> direction;
            fishes[fish_num] = {r, c, direction-1, 1};
            map[r][c] = fish_num;
        }
    }

    int max_fish_sum = 0;
    dfs(map, fishes, 0, 0, 0, max_fish_sum);

    printf("%d", max_fish_sum);
    return 0;

}