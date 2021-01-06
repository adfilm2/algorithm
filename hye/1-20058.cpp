//
//  main.cpp
//  jj
//
//  Created by dohan on 04/01/2021.
//

#include <iostream>
#include <vector>

#define MAX 64

int grid[MAX][MAX], temp[MAX][MAX];
int N, Q;

using namespace std;


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
            if(!grid[i][j]){
                if(grid[i][j-1]) check[i][j-1]=1;
                if(grid[i][j+1]) check[i][j+1]=1;
                if(grid[i-1][j]) check[i-1][j]=1;
                if(grid[i+1][j]) check[i+1][j]=1;
            }
        }
    }
    
    
    if(check[0][0] && grid[0][0]) grid[0][0]--;
    if(check[0][N-1] && grid[0][N-1]) grid[0][N-1]--;
    if(check[N-1][0] && grid[N-1][0]) grid[N-1][0]--;
    if(check[N-1][N-1] && grid[N-1][N-1]) grid[N-1][N-1]--;
    
    for(int i=0; i<N; i++){
        for(int j=0; j<N ; j++){
            if(check[i][j]) grid[i][j]--;
        }
    }
    
    
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
//        for(int i=0; i<N; i++){
//            for(int j=0; j<N; j++){
//                cout << grid[i][j] << " ";
//            }
//            cout << endl;
//        }
//        cout << "++++++++++++++++"<< endl;
//
        //melting
        //melt();
        
        
//        print
        
    }
    
    int sum =0;
    
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            sum += grid[i][j];
        }
    }
    cout << sum;
   
}




