#include <vector>
#include <cstring>
using namespace std;

int dp[100][201];

int solution(int n, int m, vector<vector<int>> edge_list, int k, vector<int> gps_log) {
    int INF = 987654321;
    vector<vector<int> > graph(n+1, vector<int>());
    
    for (int i=0; i<k; i++) {
        for (int j=0; j<=n; j++) {
            dp[i][j] = INF;
        }
    }
    
    for (int i=1; i<=n; i++) graph[i].push_back(i);
    for (auto edge: edge_list) {
        graph[edge[0]].push_back(edge[1]);
        graph[edge[1]].push_back(edge[0]);
    }
    
    dp[0][gps_log[0]] = 0;
    
    for (int i=0; i<k-1; i++) {
        for (int j=1; j<=n; j++) {
            if (dp[i][j] == INF) continue;
            int len = graph[j].size();
            for (int e=0; e<len; e++) {
                int to = graph[j][e];
                int updated = (gps_log[i+1] == to ? dp[i][j] : dp[i][j]+1);
                dp[i+1][to] = min(dp[i+1][to], updated);
            }
        }
    }
    
    int end = gps_log.back();
    return dp[k-1][end] == INF ? -1 : dp[k-1][end];
}