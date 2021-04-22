#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>

using namespace std;

int makeSeries(int N, int rep) {
    int ret = 0;
    int add = N;
    while ((rep--) > 0) {
        ret += add;
        add *= 10;
    }
    return ret;
}

void insertNumbers(int left, int right, unordered_set<int> &st, vector<unordered_set<int> > &dp) {
    for (int l : dp[left]) {
        for (int r : dp[right]) {
            st.insert(l*r);
            st.insert(l+r);
            int sub = l-r;
            if (sub>0) st.insert(sub);
            if (r>0) st.insert(l/r);
        }
    }
}

int solution(int N, int number) {
    vector<unordered_set<int> > dp;
    
    dp.push_back(unordered_set<int>());
    unordered_set<int> a;
    a.insert(N);
    dp.push_back(a);
    if (number == N) return 1;
    
    for (int i=2; i<9; i++) {
        unordered_set<int> b;
        b.insert(makeSeries(N, i));
        
        for (int j=1; j<i; j++) {
            insertNumbers(j, i-j, b, dp);
        }
        
        if (b.find(number) != b.end())  {
            return i;
        }
        dp.push_back(b);
    }
    
    return -1;
}