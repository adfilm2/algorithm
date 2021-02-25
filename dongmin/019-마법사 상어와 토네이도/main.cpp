#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
struct TorRate {
    int r, c;
    double rate;
};

int N;
int dir[4][2] = {{0,-1}, {1,0}, {0,1}, {-1,0}};
bool isOuterRange(int r, int c) {
    return r<0||c<0||r>=N||c>=N;
}
void flutterSands(vector<vector<int> >& amount, int r, int c, int d, int &outer) {
    vector<TorRate> trs(9, TorRate{0,0,0});
    int fluttered = amount[r][c];
    amount[r][c] = 0;

    int dr = dir[d][0], dc = dir[d][1];
    trs = {
        {r+2*dr, c+2*dc, 0.05},
        {r+dr+((dr==0)?1:0), c+dc+((dc==0)?1:0), 0.1}, {r+dr+((dr==0)?-1:0), c+dc+((dc==0)?-1:0), 0.1},
        {r+(-1*dr)+((dr==0)?1:0), c+(-1*dc)+((dc==0)?-1:0), 0.01}, {r+(-1*dr)+((dr==0)?-1:0), c+(-1*dc)+((dc==0)?1:0), 0.01},
        {r+((dr==0)?1:0), c+((dc==0)?1:0), 0.07}, {r+((dr==0)?-1:0), c+((dc==0)?-1:0), 0.07},
        {r+((dr==0)?2:0), c+((dc==0)?2:0), 0.02}, {r+((dr==0)?-2:0), c+((dc==0)?-2:0), 0.02}
    };

    int sum = 0;
    for_each(trs.begin(), trs.end(), [&sum, &outer, &amount, fluttered](TorRate tr) {
        sum += fluttered*tr.rate;
        if(isOuterRange(tr.r, tr.c)) {
            outer += fluttered*tr.rate;
            return ;
        }
        
        amount[tr.r][tr.c] += fluttered*tr.rate;
    });

    int remained = fluttered - sum;
    if(isOuterRange(r+dr, c+dc)) {
        outer += remained;
    }
    else {
        amount[r+dr][c+dc] += remained;
    }
}


int main() {
    cin >> N;
    vector<vector<int> > amount(N,vector<int>(N,0));
    for_each(amount.begin(), amount.end(), [](auto& v) {
        for_each(v.begin(), v.end(), [](auto& el) {
            cin >> el;
        });
    });

    int outer = 0;
    int r = N/2, c= N/2;
    int factor = 0;
    int dist = 0;
    while(!isOuterRange(r,c)) {
        if(factor%2 == 0) dist++;
        int dr = dir[factor%4][0], dc = dir[factor%4][1];
        for(int d=1; d<=dist; d++) {
            r += dr; c += dc;
            if(isOuterRange(r,c)) break;
            flutterSands(amount, r, c, factor%4, outer);
        }
        factor++;
    }

    cout << outer;
    return 0;
}