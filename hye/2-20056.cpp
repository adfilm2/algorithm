//
//  3-20056.cpp
//  hh
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
    bool isErased;
};
vector<Fireball> Firelist;

void move(){
    fill(&map[0][0],&map[MAX-1][MAX],-1 );
    
    for(int i=0; i<Firelist.size(); i++){
        int newr = Firelist[i].r;
        int newc = Firelist[i].c;
        newr += (dy[Firelist[i].d] * Firelist[i].s);
        newc += (dx[Firelist[i].d] * Firelist[i].s);
        
        //그 칸에 제일먼저왔으면
        if( map[newr][newc] == -1 ){
            map[newr][newc] = i;
            Firelist[i].r = newr;
            Firelist[i].c = newc;
        }else{  //이미 와있으면
            int pre = map[newr][newc];
            Firelist[pre].num ++;
            Firelist[pre].m += Firelist[i].m;
            Firelist[pre].s += Firelist[i].s;
            Firelist[pre].d += Firelist[i].d;
            
            Firelist[i].isErased = true;
            
        }
            
    }
}

void fusion(){
    
    for(int i=0; i<Firelist.size(); i++){
        
        if(Firelist[i].isErased == true) continue;
        if(Firelist[i].num > 0 && Firelist[i].m < 5){
            Firelist[i].isErased = true;
            continue;
        }
        
        
        int r, c, m, s;
        r = Firelist[i].r;
        c = Firelist[i].c;
        
        m = Firelist[i].m/5;
        Firelist[i].m = m;
        cout << m << endl;
        s = Firelist[i].s/(Firelist[i].num+1);
        Firelist[i].s = s;
        
        
        
        for(int j=0; j<3; j++){
            Fireball a;
            a.r = r;
            a.c = c;
            a.idx = ball_idx;
            ball_idx++;
            a.isErased = false;
            a.num =0;
            a.m = m;
            a.s = s;
            if(Firelist[i].d %2 ==0){
                a.d = j*2;
            }else{
                a.d= j*2 +1;
            }
            Firelist.push_back(a);
            
        }
        
        Firelist[i].d = (Firelist[i].d%2 == 0)? 6:7;
        
        
    }
}

int main(void){
    //input
    cin >> N >> M >> K ;
    for(int i=0; i<M; i++){
        int r, c;
        cin >> r >> c ;
        
    
        Fireball a;
        a.r = r;
        a.c = c;
        a.idx = ball_idx;
        ball_idx++;
        cin >> a.m >> a.s >> a.d;
        a.s = a.s%N;
        a.num =0;
        a.isErased = false;
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
        if(Firelist[i].isErased) continue;
        
        sum += Firelist[i].m;
    }
    
    cout << sum;
}

