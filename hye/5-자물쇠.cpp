#include <string>
#include <vector>
#include <iostream>

using namespace std;

bool compare(int r, int c,vector<vector<int>> key, vector<vector<int>> lock ){
    int K = key.size();
    int L = lock.size();
    
    //key의 1부분이 lock의 0이랑 맞는지 확인
    for(int i=0; i<K; i++){
        for(int j=0; j<K; j++){
            if(r+i>0 && c+j>0 && r+i<L && c+j<L){
                if(key[i][j] == lock[r+i][c+j]) return false;
                if(!lock[r+i][c+j]) lock[r+i][c+j] = 1;
            }
        }
    }
    //lock의 0부분 다 채워졌는지 확인
    for(int i=0; i<L; i++){
        for(int j=0; j<L; j++){
            if(!lock[i][j]) return false;
        }
    }
    
    return true;
}

vector<vector<int>> rotate(vector<vector<int>> key){
    int k = key.size();
    int temp[20][20]={0};
    for(int i=0; i<k; i++){
        for(int j=0; j<k; j++){
            temp[i][j] = key[i][j];
        }
    }
    for(int i=0; i<k; i++){
        for(int j=0; j<k; j++){
            key[j][k-i-1] = temp[i][j];
        }
    }
    
    return key;
}


bool solution(vector<vector<int>> key, vector<vector<int>> lock) {
    
    int M = key.size();
    int N = lock.size();
    
    for(int n=0; n<4; n++){
        for(int i= 1-M; i<N; i++){
            for(int j=1-M; j<N; j++){
                if(compare(i, j, key, lock)){
                    return true;
                }
            }
        }
        key = rotate(key);
    }
    
    
    return false;
}

int main(void){
    vector<vector<int>> key = {{0, 0, 0}, {1, 0, 0}, {0, 1, 1}};
    vector<vector<int>> lock = {{1, 1, 1}, {1, 1, 0}, {1, 0, 1}};
//    cout << solution(key, lock);
    for(int i=0; i<key.size(); i++){
        for(int j=0; j<key.size(); j++){
            cout << key[i][j] << " ";
        }
        cout << endl;
    }
    
    key = rotate(key);
    for(int i=0; i<key.size(); i++){
        for(int j=0; j<key.size(); j++){
            cout << key[i][j] << " ";
        }
        cout << endl;
    }
}

