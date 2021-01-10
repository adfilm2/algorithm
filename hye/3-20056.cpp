//
//  3-20056.cpp
//
//  Created by dohan on 09/01/2021.
//

#include <iostream>
#include <vector>
#define MAX 50
using namespace std;

int map[MAX][MAX] = {-1};
int N, M, K;
int ball_idx =0;
int dy[8] = {-1,-1,0,1,1,1,0,-1};
int dx[8] = {0,1,1,1,0,-1,-1,-1};


struct Fireball {
    int r, c, idx, m, s, d, num;
    bool isErased;  //지움 표시
};
vector<Fireball> Firelist;

void move(){
    fill(&map[0][0],&map[MAX-1][MAX],-1 );  //-1로 표시
    
    for(int i=0; i<Firelist.size(); i++){
        
        if(Firelist[i].isErased == true) continue;
        
        int newr = Firelist[i].r + (dy[Firelist[i].d] * (Firelist[i].s%N));
        int newc = Firelist[i].c + (dx[Firelist[i].d] * (Firelist[i].s%N));
        if(newr < 0) newr += N;
        if(newc < 0) newc += N;
        if(newr >= N) newr -= N;
        if(newc >= N) newc -= N;
        
        
        //그 칸에 제일먼저왔으면
        if( map[newr][newc] == -1 ){
            map[newr][newc] = Firelist[i].idx;      //idx저장
            Firelist[i].r = newr;
            Firelist[i].c = newc;
        }else{  //이미 와있으면
            int pre = map[newr][newc];
            Firelist[pre].num++;
            Firelist[pre].m += Firelist[i].m;
            Firelist[pre].s += Firelist[i].s;
            if(Firelist[pre].d > -1 && Firelist[pre].d %2 != Firelist[i].d%2 ){
                Firelist[pre].d = -1;
            }
            Firelist[i].isErased = true;
            
        }
        
    }
}

void fusion(){
    int sizee = Firelist.size();
    
    for(int i=0; i<sizee; i++){
        Fireball ball = Firelist[i];
//        if(ball.isErased == true) continue;
//        if(Firelist[i].num == 0) continue;
//        if(Firelist[i].m < 5){
//            Firelist[i].isErased = true;
//            continue;
//        }
        if(!ball.isErased && ball.num >0 ){
            if( ball.m <5 ){
                Firelist[i].isErased = true;
                continue;
            }
            
            int r, c, m, s;
            r = ball.r;
            c = ball.c;
            m = ball.m/5;
            s = ball.s/(ball.num+1);
            
            
            for(int j=0; j<4; j++){
                Fireball a;
                a.r = r;
                a.c = c;
                a.idx = ball_idx;
                ball_idx++;
                a.isErased = false;
                a.num =0;
                a.m = m;
                a.s = s;
                if(ball.d == -1){
                    a.d = j*2 + 1;
                }else{
                    a.d= j*2;
                }
                Firelist.push_back(a);
                
            }
            
            Firelist[i].isErased = true;
        }
        
    }
}

int main(void){
    //input
    
    cin >> N >> M >> K ;
    for(int i=0; i<M; i++){
        Fireball a;
        cin >> a.r >> a.c >> a.m >> a.s >> a.d;
        a.r --;
        a.c --;
        a.num =0;
        a.isErased = false;
        a.idx = ball_idx;
        ball_idx++;
        Firelist.push_back(a);
        
    }
    
    
    
    //command * k
    for(int i=0; i<K; i++){
        move();
        fusion();
    }
    
    //print total m
    int sum =0;
    for(int i=0; i<Firelist.size(); i++){
        if(Firelist[i].isErased==false){
            sum += Firelist[i].m;
        }
        
        
    }
    
    cout << sum;
}


