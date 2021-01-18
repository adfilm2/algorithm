
#include <iostream>
#include <queue>
#define Nmax 20
#define Mmax 400
#define min(a, b) (((a)<(b)) ? (a) : (b))
using namespace std;


int Map[Nmax][Nmax] ={0,};
int visit[Nmax][Nmax] ={0,};
int client[Mmax][5] ={0,};
int dy[] = { -1,0,1,0 };
int dx[] = { 0,1,0,-1 };
int N, M, oil;
int minDis;

int find(int sr, int sc, int dr, int dc){
    int dist = 0;
    //[sr][sc]부터 [ar][ac]까지 최단거리 반환
    
    return dist;
}


int nextClient(int r, int c){
    int next = 999;
    int temp;
    int idx;
    
    for(int i=0; i<M; i++){
        if(client[i][0]) continue;  //이미 태운적있으면 pass
        
        temp = find(r,c,client[i][1],client[i][2]);
        
        //temp가 더 적거나, 같은데 temp의 r이 더 적을때 next에 temp저장
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
        
        if(oil - minDis <= 0){
            cout << -1;
            break;
        }
        
        oil -= minDis;
        r = client[n][1];
        c = client[n][2];
        
        dis = find(r,c,client[n][3],client[n][4]);
        if(oil - dis <= 0){
            cout << -1;
            break;
        }
        oil += dis;
        r = client[n][3];
        c = client[n][4];
        client[n][0] = 1;
        
    }
    
    cout << oil;
    
    
    
    
}
