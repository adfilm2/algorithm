#include <string>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct pos {
	int row;
	int col;
}Pos;

string listingAllAlphabet(int R, int C, vector<string> board) {
	string ret = "";
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (board[i][j] >= 'A' && board[i][j] <= 'Z' && ret.find(board[i][j]) == string::npos) {
				ret.push_back(board[i][j]);
			}
		}
	}
	return ret;
}

bool allTileRemoved(int R, int C, vector<string>& board) {
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (board[i][j] >= 'A' && board[i][j] <= 'Z') {
				return false;
			}
		}
	}
	return true;
}

void findPositionOfTile(int R, vector<string>& board, Pos& first, Pos& second, char tile) {
	int order = 1;
	for (int i = 0; i < R; i++) {
		int j = board[i].find(tile);
		int k = board[i].find_last_of(tile);

		if (j != string::npos) {
			if (j == k) {
				order ? first = { i,j } : second = { i,j };
				order -= 1;
			}
			else {
				first = { i, j };
				second = { i, k };
				return;
			}
		}
	}
}

bool sameRowCheck(vector<string>& board, int c1, int c2, int row) {
	int initc = min(c1, c2);
	int endc = max(c1, c2);
	for (int j = initc + 1; j < endc; j++) {
		char otherTile = board[row][j];
		if (otherTile == '*' || (otherTile >= 'A' && otherTile <= 'Z')) {
			return false;
		}
	}
	return true;
}

bool sameColCheck(vector<string>& board, int r1, int r2, int col) {
	int initr = min(r1, r2);
	int endr = max(r1, r2);
	for (int i = initr + 1; i < endr; i++) {
		char otherTile = board[i][col];
		if (otherTile == '*' || (otherTile >= 'A' && otherTile <= 'Z')) {
			return false;
		}
	}
	return true;
}

bool isAbleToRemove(int R, int C, vector<string>& board, Pos first, Pos second, char tile) {
	bool ret = true;

	if (first.row == second.row) {
		ret = sameRowCheck(board, first.col, second.col, first.row);
	}
	else if (first.col == second.col) {
		ret = sameColCheck(board, first.row, second.row, first.col);
	}
	else {
		bool leftCheck = true, rightCheck = true;

		leftCheck = sameColCheck(board, first.row, second.row, first.col) &&
			sameRowCheck(board, first.col, second.col, second.row) && (board[second.row][first.col] == '.');

		rightCheck = sameColCheck(board, first.row, second.row, second.col) &&
			sameRowCheck(board, first.col, second.col, first.row) && (board[first.row][second.col] == '.');
		ret = leftCheck | rightCheck;
	}

	return ret;
}

void removeTile(vector<string>& board, Pos first, Pos second, char tile) {
	board[first.row][first.col] = '.';
	board[second.row][second.col] = '.';
}

string solution(int m, int n, vector<string> board) {
	string answer = "";
	string list = listingAllAlphabet(m, n, board);
	sort(list.begin(), list.end());
	while (!allTileRemoved(m, n, board)) {
		string temp = answer;
		for (int i = 0; i < list.size(); i++) {
			Pos first, second;
			findPositionOfTile(m, board, first, second, list[i]);
			if (isAbleToRemove(m, n, board, first, second, list[i])) {
				removeTile(board, first, second, list[i]);
				answer.push_back(list[i]);
				list.erase(i, 1);
				break;
			}
		}
		if (temp == answer) {
			return "IMPOSSIBLE";
		}
	}
	return answer;
}