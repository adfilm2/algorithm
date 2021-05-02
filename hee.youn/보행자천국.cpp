#include <vector>
#include<stdio.h>
#define BLOCKED 1
#define RIGHT 0
#define DOWN 1

using namespace std;

struct Node{
    int x;
    int y;
    Node operator +(Node node) {
        return { x + node.x, y + node.y };
    }
    Node operator -(Node node){
        return { x - node.x, y - node.y };
    }
};
int N, M;
bool outOfRange(Node node){
    return node.x < 0 || node.y < 0 || node.x >= M || node.y >= N;
}

Node dir[2] {{0, 1}, {1, 0}};

int MOD = 20170805;

int d[500][500][2];

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
int solution(int m, int n, vector<vector<int>> city_map) {
    M = m;
    N = n;
    d[0][0][RIGHT] = d[0][0][DOWN] = 1;
    for(int i = 1; i < m; i++){
        d[i][0][RIGHT] = 0;
        d[i][0][DOWN] = d[i - 1][0][DOWN] && city_map[i][0] != BLOCKED;
    }
    for(int i = 1; i < n; i++){
        d[0][i][RIGHT] = d[0][i - 1][RIGHT] && city_map[0][i] != BLOCKED;
        d[0][i][DOWN] = 0;
    }
    for(int r = 1; r < m; r++) {
        for(int c = 1; c < n; c++) {
            d[r][c][0] = d[r][c][1] = 0;
            if(city_map[r][c] == BLOCKED) continue;
            for(int i = 0; i < 2; i++) {
                Node prev = Node{r, c} - dir[i];
                if(outOfRange(prev)) continue;
                if(city_map[prev.x][prev.y] == 2) {
                    d[r][c][i] += d[prev.x][prev.y][i];
                    d[r][c][i] %= MOD;   
                    continue;
                }
                d[r][c][i] += d[prev.x][prev.y][RIGHT] + d[prev.x][prev.y][DOWN];
                d[r][c][i] %= MOD;
            }
        }
    }
    /*
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            printf("%2d/%2d ", d[i][j][RIGHT],d[i][j][DOWN]);
        }
        printf("\n");
    }*/
    return (d[m - 1][n - 1][RIGHT] + d[m - 1][n - 1][DOWN] ) % MOD;
}