
#include <iostream>
#define MAX 1000

using namespace std;

int N, K;
int A[MAX] = {0};
bool B[MAX] = {0};
int step =0;
int cnt =0;
int up, down;


int main(void){
    //input
    cin >> N >> K ;
    for(int i=0;i<2*N; i++){
        cin >> A[i] ;
    }
    
    up = 0;
    down = N-1;
    
    while (cnt < K) {
        step++;
        //rotate
        up--; down--;
        if(up<0) up += 2*N;
        if(down<0) down+= 2*N;
        
        //move
        B[down] = 0;
        for(int i = down; ; i--){
            if(i<0) i += 2*N;
            if(i == up) break;
            
            if(B[i]){
                int t=i;
                if( i+1 == 2*N ) t= -1;
                if(B[t+1] || !A[t+1])continue;
                
                B[t+1] = true;
                B[i] = false;
                A[t+1]--;
                if(A[t+1]==0) cnt ++;
            }
        }
        B[down] = 0;
        
        //loading
        if(!B[up] && A[up]>0){
            B[up]=true;
            A[up]--;
            if(A[up] == 0) cnt ++;
        }
        
    }
    
    cout  <<step;
    
    
}

