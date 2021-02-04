#include <iostream>


using namespace std;

int onepan[50][50] = {0,};
int rotation[50][3] = {0,};
int pointer[50] = {0,}; //기준
int N, M, T;


void remove(){
    int pivot=0;
    for(int i=0; i<M; i++){ //M개의 숫자
        for(int j=0; j<N; j++){     //N개의 원판
            pivot = pointer[j] + i;
            if(pivot >= M) pivot -= M;
            
        }
    }
}

void run(int x, bool d, int k){
    int i=1;
    
    while(x*i <= N){
        int a = x*i;
        
        if(d){
            pointer[a-1] += k;     //반시계방향
            if(pointer[a-1] >= M) pointer[a-1] -= M;
        }else{
            pointer[a-1] -= k;     //시계방향
            if(pointer[a-1] < 0) pointer[a-1] += M;
        }
        
        
        i++;
    }
    
}




int main(void){
    //input
    
    cin >> N >> M >> T ;
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            cin >> onepan[i][j];
        }
    }
    for(int i=0; i<T; i++){
        for(int j=0; j<3; j++){
            cin >> rotation[i][j];
        }
    }

    
    
    //풀이
    for(int i=0; i<T;i++){
        run(rotation[i][0],rotation[i][1],rotation[i][2]);
        remove();
    }
    
    
    
    
    
    
    
}

