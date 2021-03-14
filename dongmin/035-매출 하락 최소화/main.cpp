#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <iostream>

using namespace std;

const int MAX_EMPLOYEE = 300001;

unordered_map<int, vector<int> > teams;
int dp[MAX_EMPLOYEE][2];

int dfs(int node, bool is_included, vector<int>& sales) {
    if (teams[node].size() == 0) {
        if (is_included) {
            return sales[node];
        }
        return 0;
    }
    
    int child_sum_min = 0;
    int min_diff = 2100000000;
    int sum = 0;
    for (int i=0; i<teams[node].size(); i++) {
        int child_node = teams[node][i];
        if (dp[child_node][0] == -1) {
            dp[child_node][0] = dfs(child_node, false, sales);
        }
        if (dp[child_node][1] == -1) {
            dp[child_node][1] = dfs(child_node, true, sales);
        }
        sum += dp[child_node][0];
        child_sum_min += min(dp[child_node][0], dp[child_node][1]);
        min_diff = min(min_diff, dp[child_node][1] - dp[child_node][0]);
    }
    
    if (is_included) {
        return child_sum_min + sales[node];   
    }
    
    if (child_sum_min == sum) {
        child_sum_min += min_diff;
    }
    return child_sum_min;
}

int solution(vector<int> sales, vector<vector<int>> links) {
    int answer = 0;
    size_t employee_num = sales.size();
    memset(dp, -1, sizeof(dp));
    
    for (int i=1; i<=employee_num; i++) {
        teams.emplace(i, vector<int>());
    }
    
    int team_num = 0;
    for (auto link:links) {
        teams[link[0]].emplace_back(link[1]);
    }
    
    sales.insert(sales.begin(),0);
    dp[1][0] = dfs(1, false, sales);
    dp[1][1] = dfs(1, true, sales);
    answer = min(dp[1][0], dp[1][1]);
    
    return answer;
}