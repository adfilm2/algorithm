//
//  2-20057.cpp
//  hh
//
//  Created by dohan on 06/01/2021.
//

#include <iostream>
#define MAX 500
using namespace std;
int N, result =0;
int grid[MAX][MAX];
float percent[9] = {0.01,0.02,0.07,0.1,0.05,0.1,0.07,0.02,0.01};
int dx[4] = {-1,0,1,0};
int dy[4] = {0,1,0,-1};
int sy[4][10]={
    {-1,-2,-1,-1,0,1,1,2,1,0},
    {0,1,1,2,3,2,1,1,0,2},
    {-1,-2,-1,-1,0,1,1,2,1,0},
    {0,-1,-1,-2,-3,-2,-1,-1,0,-2}
};
int sx[4][10]={
    {0,-1,-1,-2,-3,-2,-1,-1,0,-2},
    {-1,-2,-1,-1,0,1,1,2,1,0},
    {0,1,1,2,3,2,1,1,0,2},
    {-1,-2,-1,-1,0,1,1,2,1,0}
};


void moveSand(int y, int x, int dir){
    int nextx = x + dx[dir];
    int nexty = y + dy[dir];
    int sand = grid[nexty][nextx];
    
    int i, j;
    for(int k=0; k<9; k++){
        i = y + sy[dir][k];
        j = x + sx[dir][k];
        if(i < 0 || i >= N || j <0 || j >=N){
            result += floor(sand * percent[k]);
            grid[nexty][nextx] -= floor(sand * percent[k]);
        }else{
            grid[i][j] += floor(sand * percent[k]) ;
            grid[nexty][nextx] -= floor(sand * percent[k]);
            cout << "grid["<<i<<"]["<<j<<"] "<<grid[i][j]<<endl;
        }
    }
    
    i = y + sy[dir][9];
    j = x + sx[dir][9];
    if(i < 0 || i >= N || j <0 || j >=N){
        result += grid[nexty][nextx];
    }else{
        grid[i][j] += grid[nexty][nextx];
    }
    grid[nexty][nextx] = 0;
}


int main(void){
    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++) cin >> grid[i][j];
    }
    
    
    //start move
    
    int curx = N/2;
    int cury = N/2;
    int dir = 0;
    
    
    
    for(int n=1; n<N; n++){
        for(int i=0 ; i<2; i++){
            for(int k=0; k<n; k++){
                if(curx == 0 && cury == 0){
                    break;
                }
                moveSand(cury, curx, dir);
                cury = cury + dy[dir];
                curx = curx + dx[dir];
                
            }
            dir = (dir+1)%4;
        }
    }
    
    cout << result;
}
