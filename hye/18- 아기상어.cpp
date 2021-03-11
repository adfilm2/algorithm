#include <iostream>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

struct target{
    int dist;
    int r;
    int c;
};

struct compare{
    bool operator()(target &a, target &b){
        if(a.dist != b.dist){
            return a.dist > b.dist;
        }else if(a.r != b.r){
            return  a.r > b.r;
        }else{
            return a.c > b.c;
        }
    }
};


priority_queue<target, vector<target>, compare> edible;
queue<target> targets;

int Map[20][20] = {0,};
bool Visit[20][20] = {0,};
int N;
int timer = 0;
int mysize = 2;
int dr[] = { -1,0,1,0 };    //위 오 아래 왼
int dc[] = { 0,1,0,-1 };




void find(){
    
    
    
    //현재위치에서 모든 물고기간의 거리 저장
    while(!targets.empty()){
        target a = targets.front();
        targets.pop();
        for(int i=0; i<4; i++){
            int nr = a.r + dr[i];
            int nc = a.c + dc[i];
            
            if( nr >= N || nr < 0 || nc >=N || nc < 0) continue;    //경계확인
            if( Map[nr][nc] > mysize || Visit[nr][nc]) continue;  //큰 물고기가 있는 곳과 다녀온 곳은 못감
            
            targets.push({a.dist +1, nr, nc});
            Visit[nr][nc] = true;
            
            //먹을 수 있으면 edible에 저장
            if(Map[nr][nc] < mysize && Map[nr][nc] >0){
                edible.push({a.dist +1, nr, nc});
            }
        }
    }
}

int main(void){
    //input
    int ate = 0;
    int r,c;
    cin >> N;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> Map[i][j];
            
            if(Map[i][j] == 9) {
                r = i;
                c = j;
                Map[i][j] = 0;
                Visit[i][j] = true;
                targets.push({0,i,j});
            }
            
        }
    }
    
    
    //size보다 작은, 가까운 물고기 찾기
    //BFS
    while (true) {
        find(); //edible에 현재위치에서 먹을 수 있는 물고기들 저장
        memset(Visit,false,sizeof(Visit));  //visit 초기화
        
        if(edible.empty()){
            cout << timer;
            break;
        }else{
            target t = edible.top();
            edible.pop();
            ate ++;
            timer = t.dist;
            Map[t.r][t.c] = 0;
            targets.push({t.dist, t.r, t.c});
            Visit[t.r][t.c] = true;
        }
        if(ate == mysize){
            mysize++;
            ate =0;
        }
        while(!edible.empty()){
            edible.pop();
        }
        
        
        
    }
    
    
    
    
}

