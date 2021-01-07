//
//  main.cpp
//  jj
//
//  Created by dohan on 03/01/2021.
//

#include <iostream>
#define MAX 64
using namespace std;

int grid[MAX][MAX], temp[MAX][MAX];
bool visited[MAX][MAX] = {false};
int dx[] = { 0, 0, 1, -1 };
int dy[] = { 1, -1, 0, 0 };
int N, Q;


int max(int x, int y){
    return (x>y)?x:y;
}


void rotate(int y, int x,int L ){
    for(int i=0; i<L; i++){
        for(int j=0; j<L; j++){
            temp[i][j] = grid[y+i][x+j];
        }
    }
    for(int i=0; i<L; i++){
        for(int j=0; j<L; j++){
            grid[y+j][x+L-i-1]=temp[i][j];
        }
    }
}


void melt(){
    bool check[MAX][MAX] ={false};
    
    for(int i=0 ; i<N; i++){
        for(int j=0 ; j<N; j++){
        
            int cnt = 0;
            for(int k=0;k<4; k++){
                int y = i+dx[k];
                int x = j+dy[k];
                if(x>=0 && y>=0 && x<N && y<N){
                    if(grid[y][x]>0) cnt++;
                }
            }
            if(cnt < 3) check[i][j] = 1;
        }
    }
    
    for(int i=0; i<N; i++){
        for(int j=0; j<N ; j++){
            if(check[i][j]&& grid[i][j] >0) grid[i][j]--;
        }
    }
    
}


int dfs(int i, int j){
    int a = 1;
    visited[i][j] = true;
    for(int k=0;k<4; k++){
        int y = i+dx[k];
        int x = j+dy[k];
        if(x>=0 && y>=0 && x<N && y<N){
            if(!visited[y][x] && grid[y][x]){
                a += dfs(y, x);
            }
        }
    }
    return a;
}


int countIce(){
    
    int sum=0;
    
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(grid[i][j] && !visited[i][j]){
                sum = max(sum, dfs(i,j));
            }
        }
    }
    
    return sum;
}


int main(void) {
    //input
    
    cin >> N >> Q ;
    N = 1 << N ;
    for(int i=0; i<N; i++){
        for(int j=0; j<N ; j++){
            cin >> grid[i][j];
        }
    }
    
    for(int i=0; i<Q; i++){
        int L;
        cin >> L;
        L = 1 << L;
        
        //rotate
        for(int i=0; i<N/L; i++){
            for(int j=0; j<N/L; j++){
                rotate(i*L,j*L,L);
            }
        }
 
        //melting
        melt();
        
    }
    
    //sum
    int sum =0;
    
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            sum += grid[i][j];
        }
    }
    cout << sum << endl;
    
    //dfs
    int ice = countIce();
    cout << ice;
    
    
   
}



