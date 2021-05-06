#include <vector>
#include <cstring>
using namespace std;
struct Node {
    int up, left;
};

int MOD = 20170805;

Node dp[500][500];

int solution(int m, int n, vector<vector<int>> city_map) {
    memset(dp, 0, sizeof(dp));
    for (int i=0; i<m; i++) {
        if (city_map[i][0] == 1) break;
        dp[i][0] = Node{1,0};
    }   
    for (int i=0; i<n; i++) {
        if (city_map[0][i] == 1) break;
        dp[0][i] = Node{0,1};
    }
    
    for (int i=1; i<m; i++) {
        for (int j=1; j<n; j++) {
            if (city_map[i][j] == 1) {
                dp[i][j] = Node{0,0};
                continue;
            } 
            
            int up = (city_map[i-1][j] == 2 ? dp[i-1][j].up : dp[i-1][j].up + dp[i-1][j].left) % MOD;
            int left = (city_map[i][j-1] == 2 ? dp[i][j-1].left : dp[i][j-1].up + dp[i][j-1].left) % MOD;
            dp[i][j] = Node {up, left};
        }
    }
    
    return (dp[m-1][n-1].left + dp[m-1][n-1].up) % MOD;
}