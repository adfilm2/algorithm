#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct dto {
    string min, max;
};

int compare(string l, string r) {
    int l_size = l.length();
    int r_size = r.length();

    if (l_size > r_size) {
        return 1;
    }

    if (l_size == r_size) {
        if (l[0] == '0' || r[0] == '0') return -2;
        bool is_same = true; 
        for (int i=0; i<l_size; i++) {
            if (l[i] != r[i]) {
                return l[i] > r[i] ? 1 : -1;
            }
        }
        return 0;
    }

    return -1;
}

dto solve(int n) {
    vector<string> min_dp = {"", "", "1", "7", "4", "2", "0", "8" };
    vector<string> max_dp = {"", "", "1", "7", "11", "71", "111", "711" };

    if (n<=7) {
        if (n==6) return dto{ "6", max_dp[n] };
        return dto{ min_dp[n], max_dp[n] };
    }

    for (int i=8; i<=n; i++) {

        string pushed_min = "";
        for (int k=0; k<1000; k++) pushed_min += "9";
        string pushed_max = "0";
        for (int j=2; j<=i/2; j++) {
            int counter = i-j;
            string left_min = min_dp[j] + min_dp[counter];
            string right_min = min_dp[counter] + min_dp[j];

            string left_max = max_dp[j] + max_dp[counter];
            string right_max = max_dp[counter] + max_dp[j];

            
            if (compare(left_min, pushed_min) == -1) {
                pushed_min = left_min;
            }
            if (compare(right_min, pushed_min) == -1) {
                pushed_min = right_min;
            }
                        
            if (compare(right_max, pushed_max) == 1) {
                pushed_max = right_max;
            }
            if (compare(left_max, pushed_max) == 1) {
                pushed_max = left_max;
            }
        }

        if (pushed_min[0] == '0') pushed_min[0] = '6';
        min_dp.push_back(pushed_min);
        max_dp.push_back(pushed_max);
    }

    return dto{min_dp[n], max_dp[n]};
}

int main() {
    int C, N;
    cin >> C;

    for (int c=0; c<C; c++) {
        cin >> N;
        dto mm = solve(N);
        cout << mm.min << " " << mm.max << "\n";
    } 
}