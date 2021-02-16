#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

int N;

vector< std::function<int(vector<vector<int> > &city, int x, int y, int d1, int d2)> > districtSums = {
    [](vector<vector<int> > &city, int x, int y, int d1, int d2) -> int{
        int sum=0;
        int xysum_min = x+y;

        for(int r=0; r<x+d1; r++) {
            for(int c=0; c<=y; c++) {
                if(r+c >= xysum_min) continue;
                sum += city[r][c];
            }
        }
        return sum;
    },
    [](vector<vector<int> > &city, int x, int y, int d1, int d2) -> int{
        int sum=0;
        int xysub_min = x-y;

        for(int r=0; r<=x+d2; r++) {
            for(int c=y+1; c<N; c++) {
                if(r-c >= xysub_min) continue;
                sum += city[r][c];
            }
        }
        return sum;
    },
    [](vector<vector<int> > &city, int x, int y, int d1, int d2) -> int{
        int sum=0;
        int xysub_max = x-y+2*d1;

        for(int r=x+d1; r<N; r++) {
            for(int c=0; c<y-d1+d2; c++) {
                if(r-c <= xysub_max) continue;
                sum += city[r][c];
            }
        }
        return sum;
    },
    [](vector<vector<int> > &city, int x, int y, int d1, int d2) -> int{
        int sum=0;
        int xysum_max = x+y+2*d2;

        for(int r=x+d2+1; r<N; r++) {
            for(int c=y-d1+d2; c<N; c++) {
                if(r+c <= xysum_max) continue;
                sum += city[r][c];
            }
        }
        return sum;
    },
    [](vector<vector<int> > &city, int x, int y, int d1, int d2) -> int{

        int xysum_min = x+y, xysum_max = x+y+2*d2;
        int xysub_min = x-y, xysub_max = x-y+2*d1;

        int sum=0;
        for(int r=x; r<=x+d1+d2; r++) {
            for(int c=y-d1; c<y+d2+1; c++) {
                if(r+c < xysum_min || r+c > xysum_max) continue;
                if(r-c < xysub_min || r-c > xysub_max) continue;
                
                sum += city[r][c];
            }
        }
        return sum;
    }
};

int main() {
    
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> N;
    vector<vector<int> > city(N, vector<int>(N,0));
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            cin >> city[i][j];

    int answer = 1e9;
    for(int r=0; r<N; r++) {
        for(int c=0; c<N; c++) {
            for(int d1=1; d1<=N-1; d1++) {
                for (int d2=1; d2<=N-1; d2++) {
                    if(r+d1+d2>=N) continue;
                    if(r+d2>=N) continue;
                    if(r+d1>=N) continue;
                    if(c+d2>=N) continue;
                    if(c-d1<0) continue;
                    
                    vector<int> district;
                    for(int i=0; i<5; i++) {
                        district.push_back(districtSums[i](city, r, c, d1, d2));
                    }
                    int subt = *max_element(district.begin(), district.end()) - *min_element(district.begin(), district.end());
                    
                    if(answer>subt) {
                        answer = subt;
                    }
                }
            }
        }
    }

    cout << answer;
    return 0;
}