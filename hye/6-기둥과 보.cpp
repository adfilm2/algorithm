#include <string>
#include <vector>
#include <iostream>
#define MAX 100
using namespace std;

int map[MAX][MAX]={0};
int r,c;
bool isBo, isBuild;

bool checkBo(){
    return true;
}

bool checkCol(){
    return true;
}


bool possible(vector<int> frame, int N){
    c = frame[0];
    r = N - frame[1];
    isBo = frame[2];
    isBuild = frame[3];
    
    if(isBuild){
        if(isBo){
            //build - bo
            if(map[r+1][c] == 2) return true;
            if(map[r][c-1] ==1 && map[r][c+1] ==1) return true;
        }else{
            //build - column
            if(r == 0 || map[r+1][c] == 2 || map[r][c-1] == 1 || map[r][c] == 1) return true;
        }
    }else{
        if(isBo){
            //delete - bo
            
        }else{
            //delete - column
        }
    }
    
    
    
    return false;
}


vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    vector<vector<int>> answer;
    
    for(int i=0; i<build_frame.size(); i++){
        possible(build_frame[i],n);
    }
    
    
    return answer;
}

int main(void){
    vector<vector<int>> a= {{1,0,0,1},{1,1,1,1},{2,1,0,1},{2,2,1,1},{5,0,0,1},{5,1,0,1},{4,2,1,1},{3,2,1,1}};
    cout << a.size();
    possible(a[0],4);
}

