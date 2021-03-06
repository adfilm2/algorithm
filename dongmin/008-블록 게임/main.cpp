#include <string>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>

using namespace std;
struct Rectangle {
    int minr, maxr, minc, maxc;
};
struct PossibleBlock {
    int num, c1, c2, minr, maxr;
};

void findBlocks(vector<vector<int> > &board, map<int, Rectangle> &rectangles, int N) {
    for (int r=0; r<N; r++) {
        for (int c=0; c<N; c++) {
            int block = board[r][c];
            if (block != 0 && rectangles.count(block) == 0) {
                rectangles.insert(make_pair(block, Rectangle{51, -1, 51, -1}));
            }
        }   
    }
}

void findRectangles(vector<vector<int> >& board, map<int, Rectangle> &rectangles, int N) {

    for (int r=0; r<N; r++) {
        for (int c=0; c<N; c++) {
            int block_num = board[r][c];
            if (block_num != 0) {
                if (rectangles[block_num].minr > r) rectangles[block_num].minr = r;
                if (r > rectangles[block_num].maxr) rectangles[block_num].maxr = r;
                if (rectangles[block_num].minc > c) rectangles[block_num].minc = c;
                if (c > rectangles[block_num].maxc) rectangles[block_num].maxc = c;
            } 
        }
    }
}

bool isPossibleBlanks(int r1, int c1, int r2, int c2) {

    if (r1==0 && c1==1 && r2==0 && c2==2) return true;
    if (r1==0 && c1==0 && r2==1 && c2==0) return true;
    if (r1==0 && c1==1 && r2==1 && c2==1) return true;
    if (r1==0 && c1==0 && r2==0 && c2==1) return true;
    if (r1==0 && c1==0 && r2==0 && c2==2) return true;
    return false;
}

void findPossibleBlocks(vector<vector<int> > &board, vector<PossibleBlock>& blocks, map<int, Rectangle>& rectangles) {
    typedef struct Pos {
        int r,c;
    } Pos;

    map<int, vector<Pos> > blanks;
    for (auto rec: rectangles) {
        int block_num = rec.first;
        int minr = rec.second.minr, maxr = rec.second.maxr, minc = rec.second.minc, maxc = rec.second.maxc;
        int idx=0;
        blanks[block_num] = { Pos{0,0}, Pos{0,0} };

        for (int r=minr; r<=maxr; r++ ) {
            for (int c=minc; c<=maxc; c++) {

                int nr=r-minr, nc=c-minc;
                if (board[r][c] != block_num) {
                    blanks[block_num][idx++] = Pos{nr,nc};
                }
            }
        }
    }

    for (auto blank: blanks) {
        int block_num = blank.first;
        vector<Pos> bp = blank.second;

        if (isPossibleBlanks(bp[0].r, bp[0].c, bp[1].r, bp[1].c)) {
            blocks.push_back({block_num, bp[0].c+rectangles[block_num].minc, bp[1].c+rectangles[block_num].minc,
                             rectangles[block_num].minr, rectangles[block_num].maxr});
        }
    }
}

int solution(vector<vector<int>> board) {
    int answer = 0;
    int N = board.size();

    map<int, Rectangle> rectangles;
    findBlocks(board, rectangles, N);
    findRectangles(board, rectangles, N);

    vector<PossibleBlock> block_possible_eliminated;
    findPossibleBlocks(board, block_possible_eliminated, rectangles);
    
    bool can_eliminated[201];
    memset(can_eliminated, 0, sizeof(can_eliminated));

    sort(block_possible_eliminated.begin(), block_possible_eliminated.end(), [](auto a, auto b) {
        if (a.minr == b.minr) {
            return a.maxr < b.maxr;
        }
        return a.minr < b.minr;
    });
    
    // 제거될 수 있는 블럭들에 대해서
    for (int idx=0; idx < block_possible_eliminated.size(); idx++) {
        int possible_block = block_possible_eliminated[idx].num;
        int c1 = block_possible_eliminated[idx].c1, c2 = block_possible_eliminated[idx].c2;
        bool is_can_eliminated = true;

        int maxc = rectangles[possible_block].maxc, minc = rectangles[possible_block].minc;
        int maxr = rectangles[possible_block].maxr, minr = rectangles[possible_block].minr;
        for (int r=maxr; r>=0; r--) {

            if (board[r][c1] != possible_block && board[r][c1] != 0) {
                if (!can_eliminated[board[r][c1]]) {
                    is_can_eliminated = false;
                    break;
                }
            }
            
            if (board[r][c2] != possible_block && board[r][c2] != 0) {
                if (!can_eliminated[board[r][c2]]) {
                    is_can_eliminated = false;
                    break;
                }
            }
        }

        if (is_can_eliminated) {
            can_eliminated[possible_block] = true;
            answer += 1;
        }
    }

    return answer;
}