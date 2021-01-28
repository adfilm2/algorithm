
#include <string>
#include <vector>
#include <iostream>

using namespace std;


int solution(vector<int> food_times, long long k) {
    int n = food_times.size();
    while(k - n >= 0){
        if(k == 0) break;
        //for문 돌려
        k -= n;
        for(int i=0;i< food_times.size(); i++ ){
            
            if(food_times[i] == 0) continue; //다음칸으로
            
            food_times[i]--;
            
            if(food_times[i] == 0) n--;
            
        }
        
    }
    
    
    if (n == 0) return -1;
    
    for(int i=0; i<food_times.size(); i++){
        if(food_times[i] <= 0) continue;
        if(k == 0) return i+1;
        k--;
        
    }
    
    return -1;
}

int main(void){
    vector<int> test = {1,1,1,1};
    cout << solution(test, 4);
}
