#include <vector>
#include <iostream>
#include <cstring>
using namespace std;

bool is_prime[3001];

void dfs(vector<int>& nums, int idx, int to_pick, vector<int> &picked, int &cnt) {
    if (to_pick == 0) {
        int sum = 0;
        for (int n: picked) {
            sum += n;
        }
        
        cnt += is_prime[sum];
        return ;
    }
    
    int len = nums.size();
    for (int i=idx; i<len; i++) {
        picked.push_back(nums[i]);
        dfs(nums, i+1, to_pick-1, picked, cnt);
        picked.pop_back();
    }
}

int solution(vector<int> nums) {
    int answer = 0;
    memset(is_prime, true, sizeof(is_prime));
    
    for (int i=2; i<=3000; i++) {
        for (int j=2; i*j<=3000; j++) {
            is_prime[i*j] = false;
        }
    }
    
    vector<int> picked;
    dfs(nums, 0, 3, picked, answer);
    return answer;
}