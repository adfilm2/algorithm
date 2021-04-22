#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;


int solution(vector<int> sticker)
{
    int dp[2][100000];
    int answer = 36;
    memset(dp,0,sizeof(dp));
    int len = sticker.size();
    
    if (len <= 2) return *max_element(sticker.begin(), sticker.end());
    
    dp[0][0] = sticker[0];
    dp[1][1] = sticker[1];
    
    dp[0][1] = max(sticker[0], sticker[1]);
    dp[1][2] = max(sticker[1], sticker[2]);
    
    for (int l=2; l<len-1; l++) {
        for (int i=0; i<2; i++) {
            dp[i][i+l] = max(dp[i][i+l-1], dp[i][i+l-2] + sticker[l+i]);
        }
    }
    
    answer = max(dp[0][len-2], dp[1][len-1]);
    
    return answer;
}