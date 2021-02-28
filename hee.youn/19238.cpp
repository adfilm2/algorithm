#include<iostream>
using namespace std;
#define fi(i, a, b) for(int i = a; i < b; i++)
#define MAX_N 20
#define MAX_M 400
#define MAX_QUEUE 1000000

int N, M;
int map[MAX_N][MAX_N];

struct Point {
    int r;
    int c;
    bool operator >(Point point){
        return r > point.r || (r == point.r && c > point.c);
    }
};

bool isValid(Point* p) {
    int r = p -> r;
    int c = p -> c;
    if (map[r][c] == 1) return false;
    return r >= 0 && c >= 0 && r < N &&  c < N;
}

struct Person {
    int endR;
    int endC;
    bool isArrived(Point point) {
        return (point.r == endR && point.c == endC);
    }
} persons[MAX_M];
Person* standingMap[MAX_N][MAX_N];

int FEUL;
bool spendFeul(int needs) {
    if (FEUL < needs) return false;
    FEUL -= needs;
    return true;
}

void read_input(int *startR, int *startC) {
    cin >> N >> M >> FEUL;
    fi(i, 0, N) {
        fi(j, 0, N) {
            cin >> map[i][j];
            standingMap[i][j] = 0;
        }
    }
    int _startR, _startC;
    cin >> _startR >> _startC;
    *startR = _startR - 1;
    *startC = _startC - 1;
    int r, c;
    fi(i, 0, M) {
        cin >> r >> c >> persons[i].endR >> persons[i].endC;
        r -= 1;
        c -= 1;
        persons[i].endR -= 1;
        persons[i].endC -= 1;
        standingMap[r][c] = &persons[i];
    }
}

int dir[4][2]{ {-1, 0} ,{0, -1},{0, 1},{1,0} };
int visit[MAX_N][MAX_N];
Point queue[MAX_QUEUE];
int f, r;
bool move(Point* car, Person* p) {
    fi(i, 0, N) {
        fi(j, 0, N) {
            visit[i][j] = 0;
        }
    }
    f = r = -1;
    queue[++r] = *car;
    visit[car->r][car->c] = 1;
    while (f < r) {
        Point cur = queue[++f];
        fi(i, 0, 4) {
            Point nxt = { cur.r + dir[i][0], cur.c + dir[i][1] };
            if (!isValid(&nxt)) continue;
            if (visit[nxt.r][nxt.c] > 0) continue;
            queue[++r] = nxt;
            visit[nxt.r][nxt.c] = visit[cur.r][cur.c] + 1;
            if (!p->isArrived(nxt)) continue;
            int needs = visit[nxt.r][nxt.c] - 1;
            if (!spendFeul(needs)) return false;
            spendFeul(needs * -2);
            car->r = nxt.r;
            car->c = nxt.c;
            return true;
        }
    }
    return false;
}

Person* find_customer(Point* car) {
    if (standingMap[car->r][car->c]) {
        Person* ret = standingMap[car->r][car->c];
        standingMap[car->r][car->c] = 0;
        return ret;
    }
    int minDistance = MAX_N * MAX_N;
    fi(i, 0, N) {
        fi(j, 0, N) {
            visit[i][j] = 0;
        }
    }
    f = r = -1;
    queue[++r] = *car;
    visit[car->r][car->c] = 1;
    Point customer = { MAX_N,MAX_N };
    while (f < r) {
        Point cur = queue[++f];
        if (visit[cur.r][cur.c] >= minDistance) continue;
        fi(i, 0, 4) {
            Point nxt = { cur.r + dir[i][0], cur.c + dir[i][1] };
            if (!isValid(&nxt)) continue;
            if (visit[nxt.r][nxt.c] > 0) continue;
            visit[nxt.r][nxt.c] = visit[cur.r][cur.c] + 1;
            queue[++r] = nxt;
            if (!standingMap[nxt.r][nxt.c]) continue;
            minDistance = visit[nxt.r][nxt.c];
            if (customer > nxt) {
                customer = nxt;
            }
        }
    }
    if (customer.r == MAX_N) return 0;
    int needs = minDistance - 1;
    if (!spendFeul(needs)) return 0;
    car->r = customer.r;
    car->c = customer.c;
    Person* ret = standingMap[customer.r][customer.c];
    standingMap[customer.r][customer.c] = 0;
    return ret;
}
int solution(int startR, int startC) {
    Point car = { startR, startC };
    fi(i, 0, M) {
        Person* customer = find_customer(&car);
        if (customer == 0) return -1;
        if (!move(&car, customer)) return -1;
    }
    return FEUL;
}
int main() {
    int startR, startC;
    read_input(&startR, &startC);
    cout << solution(startR, startC);
    return 0;
}
