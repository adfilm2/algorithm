#include <string>
#include <vector>
#include <iostream>
#define MAX 100
using namespace std;

int BO[MAX][MAX]={0};
int COL[MAX][MAX]={0};
int r,c;
int N;
bool isBo, isBuild;

bool checkBo(int r, int c){
    if(COL[r+1][c] || COL[r+1][c+1]) return true;   //보 끝에 기둥 있거나
    if(BO[r][c-1] && BO[r][c+1]) return true;       //양 옆에 보가 있거나
    
    return false;
}

bool checkCol(int r, int c){
    if(r == N ) return true; //바닥이거나
    if(BO[r][c-1] || BO[r][c]) return true;   //보 끝에 서있거나
    if(COL[r+1][c]) return true;        //아래에 기둥 있거나
    return false;
}


void possible(vector<int> frame){
    c = frame[0];
    r = N - frame[1];
    isBo = frame[2];
    isBuild = frame[3];
    
    if(isBuild){
        if(isBo){
            //build - bo
            if(checkBo(r,c)){
                BO[r][c] = 1;
            }
            
        }else{
            //build - column
            if( checkCol(r,c)){
                COL[r][c] =1;
            }
        }
    }else{
        if(isBo){
            //delete - bo
            BO[r][c] = 0;
            
            if(BO[r][c-1] && !checkBo(r, c-1) ){
                BO[r][c] = 1;
            }
            
            if(BO[r][c+1] && !checkBo(r, c+1) ){
                BO[r][c] = 1;
            }
            
            if(COL[r][c+1] && !checkCol(r, c+1) ){
                BO[r][c] = 1;
            }
            
            if(COL[r][c] && !checkCol(r, c)){
                BO[r][c] = 1;
            }
            
            
        }else{
            //delete - column
            COL[r][c] = 0;
            
            if(BO[r-1][c-1] && !checkBo(r-1, c-1) ){
                COL[r][c] = 1;
            }
            
            if(BO[r-1][c] && !checkBo(r-1, c) ){
                COL[r][c] = 1;
            }
            
            if(COL[r-1][c] && !checkCol(r-1, c)){
                COL[r][c] = 1;
            }
        }
    }
    
    
    
}


vector<vector<int>> solution(int n, vector<vector<int>> build_frame) {
    vector<vector<int>> answer;
    N = n;
    for(int i=0; i<build_frame.size(); i++){
        possible(build_frame[i]);
    }

    for(int j=0; j<=n; j++){
        for(int i=n; i>=0; i--){
            if(COL[i][j]){
                answer.push_back({j,n-i,0});
            }
            if(BO[i][j]){
                answer.push_back({j,n-i,1});
            }
        }
    }


    return answer;
}
