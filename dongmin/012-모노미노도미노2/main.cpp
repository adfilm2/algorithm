#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
#define fi(i, a, b) for(register int i = a; i < b; i++)
int N;
int gb[6][4];
int bb[6][4];
int bt[4], gt[4];

void printmap() {
	fi(i, 0, 6) {
		fi(j, 0, 4) {
			cout << gb[i][j] << " ";
		}
		cout << "		";
		fi(j, 0, 4) {
			cout << bb[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

int main() {

    cin >> N;
    int t,x,y;
    int score = 0;

    memset(gb,0,sizeof(gb));
    memset(bb,0,sizeof(bb));
    for(int i=0; i<4; i++) {
        bt[i] = 5; gt[i] = 5;
    }

    for (int n=0; n<N; n++) {
        cin >> t >> x >> y;

        int cumr;
        switch (t) {
        case 1:
            gb[gt[y]][y] = 1; gt[y]-=1;
            bb[bt[x]][x] = 1; bt[x]-=1;
            break;
        case 2:
            cumr = min(gt[y], gt[y+1]);
            gb[cumr][y] = 2;       gt[y]=cumr-1;
            gb[cumr][y+1] = 3;   gt[y+1]=cumr-1;
            bb[bt[x]][x] = 3;       
            bb[bt[x]-1][x] = 2;     bt[x] -= 2;
            break;
        case 3:
            gb[gt[y]][y] = 5;
            gb[gt[y]-1][y] = 4;     gt[y]-=2;
            cumr = min(bt[x], bt[x+1]);
            bb[cumr][x] = 4;       bt[x]=cumr-1;
            bb[cumr][x+1] = 5;   bt[x+1]=cumr-1;
            break;
        }
        
        int fullgn=0, fullbn=0;
        int rg=0, rb=0;
        for(int r=5; r>=0; r--) {
                
            bool bfull=true, gfull=true;
            for(int c=0; c<4; c++) {
                if(gb[r][c] == 0) gfull=false;
                if(bb[r][c] == 0) bfull=false;
            }

            if(gfull) {
                fullgn += 1;
                rg = r;
            }
            if(bfull) {
                fullbn += 1;
                rb = r;
            }
            
        }

        
        // 꽉찬 줄 제거
        for (int i=0; i<fullgn; i++) {
            for (int c=0; c<4; c++) {
                gb[rg+i][c] = 0;
            }
        }

        for (int i=0; i<fullbn; i++) {
            for (int c=0; c<4; c++) {
                bb[rb+i][c] = 0;
            }
        }

        // 꽉찬 줄 위에 있는 블록들이 내려옴
        for (int r=rg-1; r>=0; r--) {
            for (int c=0; c<4; c++) {
                gb[r+fullgn][c] = gb[r][c];
                gb[r][c]=0;
            }
        }

        for (int r=rb-1; r>=0; r--) {
            for (int c=0; c<4; c++) {
                bb[r+fullbn][c] = bb[r][c];
                bb[r][c]=0;
            }
        }

        // 연한칸에 위치한 경우
        int outgn=0, outbn=0;
        for(int r=0; r<=1; r++) {
            
            bool gout=false, bout=false;
            for(int c=0; c<4; c++) {
                if(gb[r][c] != 0) gout=true;
                if(bb[r][c] != 0) bout=true;
            }
            if(gout) outgn+=1;
            if(bout) outbn+=1;
            
        }

        if (outgn) {
            for (int i=0; i<outgn; i++) {
                for (int c=0; c<4; c++) {
                    gb[5-i][c] = 0;
                }
            }
            
            for (int r=5-outgn; r>=0; r--) {
                for (int c=0; c<4; c++) {
                    gb[r+outgn][c] = gb[r][c];
                    gb[r][c]=0;
                }
            }
        }

        if (outbn) {
            for (int i=0; i<outbn; i++) {
                for (int c=0; c<4; c++) {
                    bb[5-i][c] = 0;
                }
            }
            for (int r=5-outbn; r>=0; r--) {
                for (int c=0; c<4; c++) {
                    bb[r+outbn][c] = bb[r][c];
                    bb[r][c]=0;
                }
            }
        }

        // 각 열들의 최상단 행번호 갱신
        for(int c=0; c<4; c++) {
            gt[c]=5; bt[c]=5;
            bool checkg=false, checkb=false;
            for(int r=0; r<6; r++) {
                if (!checkg && gb[r][c] != 0) {
                    checkg =true;
                    gt[c] = r-1;
                }
                if (!checkb && bb[r][c] != 0) {
                    checkb = true;
                    bt[c] = r-1;
                }
            }
        }

        score += (fullgn + fullbn);
    }

    int remained = 0;
    for (int r=0; r<6; r++) {
        for (int c=0; c<4; c++) {
            if (gb[r][c] != 0) remained += 1;
            if (bb[r][c] != 0) remained += 1;
        }
    }

    printf("%d\n%d", score, remained);
    return 0;
}