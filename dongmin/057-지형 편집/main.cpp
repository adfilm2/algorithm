#include<vector>
#include<algorithm>
#include<iostream>
#include<climits>
using namespace std;

long long solution(vector<vector<int> > land, int P, int Q) {
    long long answer = LLONG_MAX;
    int n = land.size();
    
    vector<int> right_vec = *max_element(land.begin(), land.end());
    vector<int> left_vec = *min_element(land.begin(), land.end());
    
    int right = *max_element(right_vec.begin(), right_vec.end());
    int left = *min_element(left_vec.begin(), left_vec.end());
    
    while (left <= right) {
        int mid = (left + right) / 2;
        
        long long sum = 0;
        long long rd = 0;
        
        for (auto r : land) {
            for (int h : r) {
                long long diff = mid - h;
                
                sum += (diff>0 ? diff*P : -diff*Q);
                rd += (diff+1>0 ? (diff+1)*P : -(diff+1)*Q);
            }
        }
        
        answer = min(answer, sum);
        answer = min(answer, rd);
        
        if (left == right) break;
        if (sum < rd) {
            right = mid;
        } else {
            left = mid+1;
        }
    }
    
    return answer;
}