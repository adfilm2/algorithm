#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
using namespace std;

struct Fireball {
    int r,c,m,s,d;
    Fireball() {r=0;c=0;m=0;s=0;d=0;}
    Fireball(int r, int c, int m, int s, int d){
        this->r=r; this->c=c; this->m=m; this->s=s; this->d=d; 
    }
};

int N,M,K;
const int dir[8][2] = { {-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1} };
void moveFireballs(vector<vector<vector<int> > > &field, map<int, Fireball> &fireballs) {

    vector<vector<vector<int> > > cp_field(N, vector<vector<int> >(N, vector<int>()));

    for(auto& fb: fireballs) {
        
        int nr = (fb.second.r + fb.second.s*dir[fb.second.d][0]) % N;
        int nc = (fb.second.c + fb.second.s*dir[fb.second.d][1]) % N;
        while(nr<0) nr+=N;
        while(nc<0) nc+=N;

        cp_field[nr][nc].push_back(fb.first);
        fb.second.r = nr; fb.second.c = nc;
    }

    copy(cp_field.begin(), cp_field.end(), field.begin());
}
void splitFireballsAfterMove(vector<vector<vector<int> > >& field, map<int, Fireball>& fireballs) {

    vector<vector<vector<int> > > cp_field(N, vector<vector<int> >(N, vector<int>()));

    if(fireballs.size() == 0) return ;
    // 런타임 에러 -> size == 0 일 때, rbegin()이 end()를 반환.
    // 반복자 사용시 크기 고려
    int new_id = fireballs.rbegin()->first + 1;
    for(int r=0; r<N; r++) {
        for(int c=0; c<N; c++) {

            if(field[r][c].size() >= 2) {
                int sm=0, ss=0;

                bool is_all_odd = true, is_all_even = true;
                for(int el=0; el<field[r][c].size(); el++) {
                    int id = field[r][c][el];
                    sm += fireballs[id].m;
                    ss += fireballs[id].s;
                    if(fireballs[id].d%2 == 0) is_all_odd = false;
                    if(fireballs[id].d%2 == 1) is_all_even = false;
                    fireballs.erase(id);
                }

                int new_m = sm/5;
                int new_s = ss/field[r][c].size();
                vector<int> new_d;
                if(is_all_even || is_all_odd){
                    new_d = {0,2,4,6};
                } else{
                    new_d = {1,3,5,7};
                }

                if(new_m > 0) {
                    for(int id=new_id; id<new_id+4; id++) {
                        cp_field[r][c].push_back(id);
                        fireballs[id] = Fireball(r, c, new_m, new_s, new_d[id-new_id]);
                    }

                    new_id += 4;
                }
            }
            else if(field[r][c].size()==1) {
                cp_field[r][c].push_back(field[r][c][0]);
            }
        }
    }

    copy(cp_field.begin(), cp_field.end(), field.begin());
}

int main() {
    cin >> N >> M >> K;

    vector<vector<vector<int> > > field;
    field.assign(N, vector<vector<int> >(N, vector<int>()));

    map<int, Fireball> fireballs;

    for(int i=0; i<M; i++) {
        int r, c;
        fireballs[i] = Fireball(0,0,0,0,0);
        cin >> r >> c >> fireballs[i].m >> fireballs[i].s >> fireballs[i].d;
        fireballs[i].r=r-1; fireballs[i].c=c-1;
        field[r-1][c-1].push_back(i);
    }

    for (int t=0; t<K; t++) {

        moveFireballs(field, fireballs);
        splitFireballsAfterMove(field, fireballs);
    }

    int mass = 0;
    for(auto fb: fireballs) {
        mass += fb.second.m;
    }
    printf("%d", mass);

    return 0;
}