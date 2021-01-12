#include <string>
#include <vector>
#include <iostream>

using namespace std;

bool compare(int r, int c,vector<vector<int>> key, vector<vector<int>> lock ){
    int K = key.size();
    int L = lock.size();
    for(int i=0; i<K; i++){
        for(int j=0; j<K; j++){
            if(r+i>0 && c+j>0 && r+i<L && c+j<L){
                if(key[i][j]){}
            }
        }
    }
    
    
    return true;
}


bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    bool answer = true;
    int M = key.size();
    int N = lock.size();
    
    for(int i= 1-M; i<N; i++){
        for(int j=1-M; j<N; j++){
            compare(i, j, key, lock);
        }
    }
    
    
    return answer;
}

int main(void){
    vector<vector<int>> key = {{0, 0, 0}, {1, 0, 0}, {0, 1, 1}};
    cout << key.size();
}
