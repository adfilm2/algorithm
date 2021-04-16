#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>
#include <iomanip>
using namespace std;

int N;
double percentage[4];
int d[4][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };
bool visited[30][30];


void dfs(int depth, int r, int c, double cur, double &total) {
    visited[r][c] = 1;

    if (depth == N) {
        total += cur;
        visited[r][c] = 0;
        return ;
    }

    for (int i=0; i<4; i++) {
        int nr = r + d[i][0];
        int nc = c + d[i][1];
        if (visited[nr][nc]) continue;
        dfs(depth+1, nr, nc, cur*percentage[i], total);
    }
    
    visited[r][c] = 0;
}

int main() {

    cin >> N;
    for (int i=0; i<4; i++) {
        double p;
        cin >> p;
        percentage[i] = p/100.0;
    }
    
    memset(visited, false, sizeof(visited));
    double total = 0;

    dfs(0, 14, 14, 1.0, total);
    
    cout.precision(11);
    cout << fixed << total << endl;
    return 0;
}