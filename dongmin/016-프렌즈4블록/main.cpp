#include <string>
#include <vector>
#include <iostream>

using namespace std;

bool isSameBlocks(vector<string>& board, int row, int col) {
    
    char first = board[row][col];
    for (int i=row; i<row+2; i++) {
        for (int j=col; j<col+2; j++) {
            if (first != board[i][j])
                return false;
        }
    }   
    return true;
}
void removeBlocks(vector<string>& board, int row, int col, int& cnt) {
    
    for (int i=row; i<row+2; i++) {
        for (int j=col; j<col+2; j++) {
            if (board[i][j] != '.'){
                board[i][j] = '.';
                cnt += 1;
            }
        }
    }
}
bool isValid(int row, int col, int m, int n) {
    return row>=0 && row<m && col>=0 && col<n;
}
void fillBlank(vector<string>& board, int row, int col) {
    int m = board.size(), n = board[0].size();
    int nr = row+1;
    while (isValid(nr, col, m, n) && board[nr][col] == '.') nr += 1;
    if (nr-1 == row) return;
    board[nr-1][col] = board[row][col];
    board[row][col] = '.';
}
void print(vector<string>& board) {
    for (int i=0; i<board.size(); i++) {
        cout << board[i] << endl;
    }
}

int solution(int m, int n, vector<string> board) {
    int answer = 0;
    int prev = -1;
    vector<vector<bool> > will_deleted;
    while (prev != answer) {
        prev = answer;
        will_deleted.assign(m-1, vector<bool>(n-1, 0));
        for (int r=0; r<m-1; r++) {
            for (int c=0; c<n-1; c++) {
                if (board[r][c] != '.' && isSameBlocks(board, r, c))
                    will_deleted[r][c] = true;
            }
        }

        for (int r=0; r<m-1; r++) {
            for (int c=0; c<n-1; c++) {
                if (will_deleted[r][c]) {
                    removeBlocks(board, r, c, answer);
                }
            }
        }     

        for (int r=m-2; r>=0; r--) {
            for (int c=n-1; c>=0; c--) {
                fillBlank(board,r,c);
            }
        } 
    }
    return answer;
}