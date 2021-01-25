#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

bool isSameTuple(vector<string>& left, vector<string>& right) {

    int col_num = left.size();
    int same_cnt = 0;
    for (int c=0; c<col_num; c++) {
        if (left[c] == right[c]) {
            same_cnt += 1;
        }
    }

    if (same_cnt == col_num) return true;
    return false;
}

bool isUnique(vector<vector<string> >& sub, int row_num) {

    for (int l=0; l<row_num; l++) {
        for (int r=l+1; r<row_num; r++) {

            if (isSameTuple(sub[l], sub[r])) {
                return false;
            }
        }
    }

    return true;
}

int solution(vector<vector<string>> relation) {
    int answer = 0;
    int row_num = relation.size();
    int col_num = relation[0].size();

    vector<int> column_combination;
    queue<vector<int> > qu;
    vector<vector<int> > candidates;
    
    for (int c=0; c<col_num; c++) {
        column_combination.push_back(c);
        qu.push(column_combination);
        column_combination.pop_back();
    }

    while (!qu.empty()) {
        vector<int> comb = qu.front();
        qu.pop();

        bool minimal = true;
        for (int i=0; i<candidates.size(); i++) {
            vector<int> compared_key = candidates[i];

            if(includes(comb.begin(), comb.end(), compared_key.begin(), compared_key.end())) {
                minimal = false;
                break;
            }
        }

        if (!minimal) continue;

        vector<vector<string> > sub;
        for (int r=0; r<row_num; r++) {

            vector<string> tup;
            for (int n=0; n<comb.size(); n++) {
                int col = comb[n];
                tup.push_back(relation[r][col]);
            }
            sub.push_back(tup);
        }

        if (isUnique(sub, row_num)) {
            candidates.push_back(comb);
            answer += 1;
        }

        for (int c=comb.back()+1; c<col_num; c++) {
            vector<int> new_comb = comb;
            new_comb.push_back(c);
            qu.push(new_comb);
        }

    }

    return answer;
}