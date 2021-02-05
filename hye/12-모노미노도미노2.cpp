
#include <iostream>
#define MAX 10000

using namespace std;

int blocks[MAX][3]={0,};
int green[6][4] = {0,};
int blue[6][4] = {0,};
int score = 0;


void deleteLine(int map[][4], int line){
    for(int i = line; i>0; i--){
        for(int j=0; j<4; j++){
            map[i][j] = map[i-1][j];
        }
    }
    
    for(int j=0; j<4; j++){
        map[0][j] = 0;
    }
}

void check01(){
    int a=0, b=0;
    for(int i=0; i<2; i++){
        for(int j=0; j<4;j++){
            if(green[i][j]){
                a++; break;
            }
        }
    }
    
    
    for(int i=0; i<2; i++){
        for(int j=0; j<4;j++){
            if(blue[i][j]){
                b++; break;
            }
        }
    }

    
    for(int i=0; i<a; i++){
        deleteLine(green, 5);
        
    }
    for(int i=0; i<b; i++){
        deleteLine(blue, 5);
        
    }
    
}



void addScore(){
    for(int i=0; i<6; i++){
        int a =0;
        for(int j=0; j<4; j++){
            if(!green[i][j]) break;
            a++;
        }
        if(a == 4){
            score++;
            deleteLine(green, i);
        }

    }
    
    for(int i=0; i<6; i++){
        int a =0;
        for(int j=0; j<4; j++){
            if(!blue[i][j]) break;
            a++;
        }
        if(a == 4){
            score++;
            deleteLine(blue, i);
        }

    }
}


void drop(bool isGreen, int t, int c){
    //green drop
    if(isGreen){
        if(t == 2){     //◼︎◼︎
            
            int i = 0;
            while(i<5){
                if(green[i+1][c] || green[i+1][c+1]) break;
    
                i++;
            }
            green[i][c] = 1;
            green[i][c+1] = 1;
            
            
            
            
        }else{
            int i = 0;
            while(i<5){
                if(green[i+1][c]) break;
                i++;
            }
            green[i][c] = 1;
            
            if(t == 3) green[i-1][c] = 1;
            
        }
        
        
    }else{
        //blue drop
        if(t == 3){     //◼︎◼︎
            
            int i = 0;
            while(i<5){
                
                if(blue[i+1][3-c] || blue[i+1][4-c]) break;
                
                i++;
            }
            blue[i][3-c] = 1;
            blue[i][4-c] = 1;
            
            
            
            
        }else{
            int i = 0;
            while(i<5){ 
                
                if(blue[i+1][3-c]) break;
                i++;
            }
            blue[i][3-c] = 1;
            
            if(t == 2) blue[i-1][3-c] = 1;
            
        }
        
    }
    
}


int main(void){

    //input
    int N;
    cin >> N;
    for(int i=0; i<N; i++){
        cin >> blocks[i][0] >> blocks[i][1] >> blocks[i][2];
    }
    
    for(int i=0; i<N; i++){
        
        //블록 내림
        drop(1,blocks[i][0],blocks[i][2]);  //green
        drop(0,blocks[i][0],3-blocks[i][1]);    //blue
        
        //행 다찼는지 확인 - 스코어 올림 - 행삭제
        addScore();
        //0,1칸 차 있는지 확인 - 맨아래 행 삭제
        check01();
    }
    
    
    
    int sum =0;
    for(int i=0; i<6; i++){
        for(int j=0; j<4; j++){
            sum += green[i][j];
            sum += blue[i][j];
        }
    }
    
    cout << score << endl;
    cout << sum << endl;
    
    
}

