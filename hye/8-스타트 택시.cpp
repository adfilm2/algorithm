#include <iostream>
#include<cstring>
#include <queue>
#define Nmax 20
#define Mmax 400
#define min(a, b) (((a)<(b)) ? (a) : (b))
using namespace std;


int Map[Nmax][Nmax] ={0,};
int visit[Nmax][Nmax];
int client[Mmax][5] ={0,};
int dr[] = { -1,0,1,0 };    //위 오 아래 왼
int dc[] = { 0,1,0,-1 };
int N, M, oil;
int minDis; //nextclient까지의 거리



int find(int sr, int sc, int ar, int ac){
    
    memset(visit, -1, sizeof(visit));
    visit[sr][sc]=0;
    queue<pair<int, int>> q;
    q.push({sr,sc});
    
    while (!q.empty()) {
        int r = q.front().first;
        int c = q.front().second;
        
        if(r == ar && c == ac) return visit[ar][ac] ;     //목적지면 return
        q.pop();
        for(int i=0; i<4; i++){
            int rr = r + dr[i];
            int cc = c + dc[i];
            
            if(rr < 0|| cc < 0 || rr >=N || cc >= N) continue;      //범위 넘어가면 pass
            if(visit[rr][cc] >=0) continue;       //가본곳이면 pass
            if(Map[rr][cc]) continue;   //벽있으면 pass
            
            visit[rr][cc] = visit[r][c] + 1;
            q.push({rr,cc});
        }
    }
    
    
    return visit[ar][ac];
}


int nextClient(int r, int c){
    int next = 999;
    int temp;
    int idx = -1;
    
    for(int i=0; i<M; i++){
        if(client[i][0]) continue;  //이미 태운적있으면 pass
        
        temp = find(r,c,client[i][1],client[i][2]);
        
        //temp가 더 적거나, 같은데 temp의 r이 더 적을때 next에 temp저장
        if(temp == -1) continue;
        if( temp < next || (temp == next && client[i][1] < client[idx][1] ) ){
            next = temp;
            idx = i;
        }else if(temp == next && client[i][1] == client[idx][1] ){      //행도 같을때
            
            if(client[i][2] < client[idx][2]){      //열 비교
                next = temp;
                idx =i;
            }
        }
    }
    
    minDis = next;
    return idx;
}


int main(void){
    //input
    cin >> N >> M >> oil;
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            cin >> Map[i][j];
        }
    }
    int c,r;        //current position
    cin >> r >> c;
    c--;
    r--;
    for(int i=0; i<M; i++){
        client[i][0] = 0;   //visited
        cin >> client[i][1] >> client[i][2] >> client[i][3] >> client[i][4];
        for(int j=1; j<5; j++){
            client[i][j] --;
        }
    }
    
    
    int n, dis;

    for(int i=0; i<M; i++){
        n = nextClient(r, c);
        if(n == -1){
            cout << -1;
            return 0;
        }
        if(oil - minDis <= 0){
            cout << -1;
            return 0;
        }

        oil -= minDis;
        r = client[n][1];
        c = client[n][2];

        dis = find(r,c,client[n][3],client[n][4]);
        if(dis == -1){
            cout << -1;
            return 0;
        }
        if(oil - dis < 0){
            cout << -1;
            return 0;
            
        }
        oil += dis;
        r = client[n][3];
        c = client[n][4];
        client[n][0] = 1;

    }

    cout << oil;
    
    
    
    
}
