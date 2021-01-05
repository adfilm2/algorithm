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


using namespace std;


void rotate(int y, int x,int L ){
    for(int i=0; i<L; i++){
        for(int j=0; j<L; j++){
            temp[i][j] = grid[y+i][x+j];
        }
    }
    for(int i=0; i<L; i++){
        for(int j=0; j<L; j++){
            grid[y+L-j-1][x+i]=temp[i][j];
        }
    }
}



int main(void) {
    //input
    int N, Q;
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
                rotate(i*L,j*L,L)
            }
        }
        
        //melting
        
        
        
        //print
        for(int i=0; i<N;i++){
            for(int j=0; j<N; j++){
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
    }
    
    
    
    
}


