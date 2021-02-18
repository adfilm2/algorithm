#include<iostream>
#include<vector>
#include<cstring>
#include<map>
#include<algorithm>
#include<functional>
using namespace std;
#define R 0
#define C 1

typedef struct {
    int num, freq;
} NumFreq;
bool cmp(const NumFreq& a, const NumFreq& b) {
    return a.freq==b.freq ? a.num < b.num : a.freq < b.freq;
}

int arr[100][100];

function<void(int&, int&)> operations[2] = {
        [](int &rnum, int &cnum) -> void{
            int max = 0;
            for(int i=0; i<rnum; i++) {
                map<int, int> freq;
                vector<NumFreq> temp;
                for(int j=0; j<cnum; j++) {
                    int num = arr[i][j];
                    if(num == 0) continue;
                    if(!freq.count(num)) {
                        temp.push_back(NumFreq{num, 0});
                        freq[num] = 1;
                    }
                    else freq[num] +=1 ;
                }

                for(int m=0; m < freq.size(); m++) {
                    temp[m].freq = freq[temp[m].num];
                }
                int new_cnum = freq.size() * 2;
                sort(temp.begin(), temp.end(), cmp);
                if(new_cnum > max) max = new_cnum;
                memset(arr[i], 0, sizeof(int) * 100);
                for(int c=0; c<temp.size(); c++) {
                    if(2*c==100) break;
                    arr[i][2*c] = temp[c].num;
                    arr[i][2*c+1] = temp[c].freq;
                }
            }

            cnum = max;
        },
        [](int &rnum, int &cnum) -> void{
            int max = 0;
            int cpy_arr[100][100];
            memset(cpy_arr, 0, sizeof(cpy_arr));

            for(int i=0; i<cnum; i++) {
                map<int, int> freq;
                vector<NumFreq> temp;
                for(int j=0; j<rnum; j++) {
                    int num = arr[j][i];
                    if(num == 0) continue;
                    if(!freq.count(num)) {
                        temp.push_back(NumFreq{num, 0});
                        freq[num] = 1;
                    }
                    else freq[num] +=1 ;
                }

                for(int m=0; m < freq.size(); m++) {
                    temp[m].freq = freq[temp[m].num];
                }
                int new_rnum = freq.size() * 2;
                if(new_rnum > max) max = new_rnum;
                sort(temp.begin(), temp.end(), cmp);
                for(int r=0; r<temp.size(); r++) {
                    if(2*r==100) break;
                    cpy_arr[2*r][i] = temp[r].num;
                    cpy_arr[2*r+1][i] = temp[r].freq;                
                }
            }
            memcpy(arr, cpy_arr, sizeof(arr));
            rnum = max;
        }
};

void solution(int r, int c, int k, int& rnum, int& cnum) {
    int ans = 0;
    while(arr[r][c] != k) {
        if(ans == 101) break;
        int type = rnum>=cnum ? R : C;
        operations[type](rnum, cnum);
        ans += 1;
    }

    if(ans == 101) ans = -1;
    printf("%d", ans);
}

int main() {
    int r,c,k;
    int rnum, cnum;
    cin >> r >> c >> k;
    rnum = 3, cnum = 3;
    memset(arr, 0, sizeof(arr));
    for(int i=0; i<3; i++) {
        for(int j=0; j<3; j++) {
            cin >> arr[i][j];
        }
    }

    solution(r-1,c-1,k,rnum,cnum);
    return 0;
}