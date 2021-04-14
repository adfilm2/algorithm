#include <iostream>
#include <vector>
using namespace std;

const int MAX_PICK = 3;
const int d[4][2] = {{0,-1}, {0,1}, {1,0}, {-1,0}};

bool isDead(int n, int r, int c, vector<vector<bool> > &occupied) {
    return r<0 || r>=n || c<0 || c>=n || occupied[r][c];
}

void pick(int depth, int pr, int pc, int sum, int n, vector<vector<int> > &price, vector<vector<bool> > occupied, int &min_price) {
    if (depth == MAX_PICK) {
        min_price = min(sum, min_price);
        return ;
    }
    
    for (int r=pr; r<n-1; r++) {
        for (int c=1; c<n-1; c++) {
            if (r == pr && c==1) c = pc;
            int nr, nc;
            bool can_plant = true;
            if (isDead(n, r, c, occupied)) continue;
            for (int i=0; i<4; i++) {
                nr = r + d[i][0];
                nc = c + d[i][1];
                if (isDead(n, nr, nc, occupied)) {
                    can_plant = false;
                    break;
                }
            }

            if (!can_plant) continue ;
            vector<vector<bool> > cpy_occupied(occupied.begin(), occupied.end());
            int plant_price = price[r][c];
            for (int i=0; i<4; i++) {
                nr = r + d[i][0];
                nc = c + d[i][1];
                cpy_occupied[nr][nc] = true;
                plant_price += price[nr][nc];
            }
            cpy_occupied[r][c] = true;
            pick(depth+1, r, c, sum+plant_price, n, price, cpy_occupied, min_price);
        }
    }
}


void solve(int n, vector<vector<int> > &price) {
    int min_price = 987654321;
    vector<vector<bool> > occupied;
    occupied.assign(n, vector<bool>(n,false));

    pick(0, 1, 1, 0, n, price, occupied, min_price);
    cout << min_price << endl;
}

int main() {

    int N;
    vector<vector<int> > price;

    cin >> N;
    price.assign(N, vector<int>(N,0));
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            cin >> price[i][j];
        }
    } 

    solve(N, price);
    return 0;
}