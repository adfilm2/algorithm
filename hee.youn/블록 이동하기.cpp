#include <string>
#include <vector>
#define MAX_N 100
#define HORIZONTAL 0
#define VERTICAL 1
#define MAX_POOL 10000000
#define fi(i, a, b) for(int i = a; i < b; i++)

using namespace std;

int map[MAX_N][MAX_N];
int N;
int check[MAX_N][MAX_N][2];
int answer;

int dir4[4][2]{{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

bool anotherPart(int x, int y, int dir, int* nx, int *ny);

struct Robot {
    int x;
    int y;
    int dir; // 0: HORIZONTAL, 1: VERTICAL
    int time;
    bool isGoal() {
        if(x == N - 1 && y == N-1) return true;
        int otX, otY;
        anotherPart(x, y, dir, &otX, &otY);
        if(otX == N - 1 && otY == N - 1) return true;
        return false;
    }
} robots[MAX_POOL];
int robot_size;

void readBoard(vector<vector<int>> board);

Robot* get(int x, int y, int dir, int time) {
    Robot* ret = &robots[robot_size];
    ret->x = x;
    ret->y = y;
    ret->dir = dir;
    ret->time = time;
    robot_size++;
    return ret;
}

Robot* robot_move(Robot* r, int d) {
    // 삭제 가능 예상
    int nx1 = r->x + dir4[d][0];
    int ny1 = r->y + dir4[d][1];
    if(nx1 < 0 || ny1 < 0 || nx1 >= N || ny1 >= N) return 0;
    // -------------
    int otX, otY;
    anotherPart(r->x, r->y, r->dir, &otX, &otY);
    int nx2 = otX + dir4[d][0];
    int ny2 = otY + dir4[d][1];
    if(nx2 < 0 || ny2 < 0 || nx2 >= N || ny2 >= N) return 0;
    if(map[nx1][ny1] == 1 || map[nx2][ny2] == 1) return 0;
    if(check[nx1][ny1][r->dir] > 0) return 0;
    Robot* ret = get(nx1, ny1, r->dir, r->time + 1);
    return ret;
}

Robot* queue[MAX_POOL];
int f, r;

bool add_robot(int x, int y, int dir, int time) {    
    if(check[x][y][dir] > 0) return false;
    check[x][y][dir] = time;
    Robot* nxt = get(x, y, dir, time);
    if(nxt->isGoal()){
        answer = nxt->time;
    }
    queue[++r] = nxt;
    return true;
}

int solution(vector<vector<int>> board) {
    answer = -1;
    f = r = 0;
    robot_size = 0;
    readBoard(board);
    
    add_robot(0, 0, HORIZONTAL, 1);
    while(f < r) {
        Robot* cur = queue[++f];
        if(cur->dir == HORIZONTAL) {
            int downX = cur->x + 1;
            int downY = cur->y;
             // 아래로 회전 가능
            if(downX >= 0 && downX < N && downY >= 0 && downY + 1 < N) {
                if(map[downX][downY] == 0 && map[downX][downY + 1] == 0) {
                    add_robot(cur->x, cur->y, VERTICAL, cur->time + 1);
                    add_robot(cur->x, cur->y + 1, VERTICAL, cur->time + 1);
                }    
            }
            int upX = cur->x - 1;
            int upY = cur->y;
             // 위로 회전 가능
            if(upX >= 0 && upX < N && upY >= 0 && upY + 1 < N) {
                if(map[upX][upY] == 0 && map[upX][upY + 1] == 0) {
                    add_robot(upX, upY, VERTICAL, cur->time + 1);
                    add_robot(upX, upY + 1, VERTICAL, cur->time + 1);
                }
            }
            
        } else if(cur -> dir == VERTICAL) {
            int leftX = cur->x;
            int leftY = cur->y - 1;
             // 좌로 회전 가능
            if(leftX >= 0 && leftX + 1 < N && leftY >= 0 && leftY < N) {
                if(map[leftX][leftY] == 0 && map[leftX + 1][leftY] == 0) {
                    add_robot(leftX, leftY, HORIZONTAL, cur->time + 1);
                    add_robot(leftX + 1, leftY, HORIZONTAL, cur->time + 1);
                }
            }
            int rightX = cur->x;
            int rightY = cur->y + 1;
             // 우로 회전 가능
            if(rightX >= 0 && rightX + 1 < N && rightY >= 0 && rightY < N) {
                if(map[rightX][rightY] == 0 && map[rightX + 1][rightY] == 0) {
                    add_robot(rightX, cur->y, HORIZONTAL, cur->time + 1);
                    add_robot(rightX + 1, cur->y, HORIZONTAL, cur->time + 1);
                }
            }
        }
        // simple move
        fi(d, 0, 4) {
            Robot* nxt = robot_move(cur, d);
            if(nxt == 0) continue;
            add_robot(nxt->x, nxt->y, nxt->dir, cur->time + 1);
        }
        if(answer != -1) {
            return answer - 1;
        }
    }
    return answer;
}

// private

bool anotherPart(int x, int y, int dir, int* nx, int *ny){
    if(dir == HORIZONTAL) { 
        *nx = x;
        *ny = y + 1;
        return true;
    } 
    if(dir == VERTICAL) {
        *nx = x + 1;
        *ny = y;
        return true;
    }
    return false;
}

void readBoard(vector<vector<int>> board){
    N = board.size();
    int i = 0, j;
    for (vector<int> vec : board) {
        j = 0;
        for (int it : vec) {
            map[i][j] = it;
            check[i][j][0] = 0;
            check[i][j][1] = 0;
            j++;
        }
        i++;
    }
}