#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
#include <queue>
using namespace std;

int N, Q;
const int dir[4][2] = { {1,0}, {-1,0}, {0,1}, {0,-1} };
void rotateClockwise(vector<vector<int> > &amount, int sr, int sc, int sub_size) {

    vector<vector<int> > cp_sub_amount(sub_size, vector<int>(sub_size,0));
    for(int r=sr; r<sr+sub_size; r++) {
        for(int c=sc; c<sc+sub_size; c++) {
            cp_sub_amount[c-sc][sub_size-1 - (r-sr)] = amount[r][c];
        }
    }
    
    for(int r=0; r<sub_size; r++) {
        for(int c=0; c<sub_size; c++) {
            amount[sr+r][sc+c] = cp_sub_amount[r][c];
        }
    }
}

void castFirestorm(vector<vector<int> > &amount, int sub_size) {

    int rn = amount.size() / sub_size;
    int sr=0, sc=0;
    for(int i=0; i<rn; i++) {
        sr = i * sub_size;
        for(int j=0; j<rn; j++) {
            sc = j * sub_size;
            rotateClockwise(amount, sr, sc, sub_size);
        }
    }
}

void meltIce(vector<vector<int> > &amount, int size) {

    // 동시에 처리할 일을 처리할 때 -> 임시 배열에 결과값 저장 후 마지막에 한번에 복사
    vector<vector<int> > cp_amount(amount.begin(), amount.end());
    for(int r=0; r<amount.size(); r++) {
        for(int c=0; c<amount.size(); c++) {

            int cnt = 0;
            if(amount[r][c] == 0) continue;
            for(int d=0; d<4; d++) {
                int nr = r+dir[d][0], nc = c+dir[d][1];
                if(nr<0||nc<0||nr>=size||nc>=size) {
                    cnt += 1;
                    continue;
                }
                if(amount[nr][nc] == 0) {
                    cnt += 1;
                }
            }

            if(cnt>1) {
                cp_amount[r][c] -= 1;
            }
        }
    }

    copy(cp_amount.begin(), cp_amount.end(), amount.begin());
}

int getMaxChunk(vector<vector<int> >& amount, int size) {

    struct Pos {int r,c;};
    int max_chunk = 0;
    vector<vector<bool> > visited(size, vector<bool>(size, 0));
    queue<Pos> qu;

    for(int r=0; r<size; r++) {
        for(int c=0; c<size; c++) {
            if(!visited[r][c]) {
                visited[r][c] = 1;
                if(amount[r][c]==0) continue;
                qu.push(Pos{r,c});
                int chunk = 0;
                while(!qu.empty()) {
                    Pos here = qu.front();
                    qu.pop();
                    chunk += 1;
                    for(int d=0; d<4; d++) {
                        Pos there = {here.r+dir[d][0], here.c+dir[d][1]};
                        if(there.r < 0 || there.c<0 || there.r>=size || there.c>=size) continue;
                        if(amount[there.r][there.c] == 0) continue;
                        if(visited[there.r][there.c]) continue;
                        visited[there.r][there.c] = 1;
                        qu.push(there);
                    }
                }

                if(chunk>max_chunk) max_chunk = chunk;
            }
        }
    }

    return max_chunk;
}

int main() {
    cin >> N >> Q;
    int size = (int)pow(2.0, (double)N);
    vector<vector<int> > ice_amount(size, vector<int>(size, 0));
    for(int i=0; i<size; i++) {
        for(int j=0; j<size; j++){
            cin >> ice_amount[i][j];
        }
    }

    for(int q=0; q<Q; q++) {
        int L;
        cin >> L;
        int sub_size = (int)pow(2.0, (double)L);

        castFirestorm(ice_amount, sub_size);
        meltIce(ice_amount, size);
    }

    int sum=0;
    for(int r=0; r<size; r++) {
        for(int c=0; c<size; c++) {
            sum += ice_amount[r][c];
        }
    }

    int max_chunk = getMaxChunk(ice_amount, size);
    cout << sum << endl << max_chunk;
    return 0;
}