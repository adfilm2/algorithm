#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

bool checkRow(int r, int N, int X, vector<vector<int> > &map) {

    int prev = map[r][0];
    int cnt = 0;
    bool to_install = false;

    for (int c=0; c<N; c++) {
        if (abs(map[r][c] - prev) > 1) return false;
        if (prev == map[r][c]) cnt++;
        if (map[r][c] - prev == 1) {
            if (cnt < X) return false;
            cnt = 1;
        }
        if (prev - map[r][c] == 1) {
            if (to_install) return false;
            to_install = true;
            cnt = 1;
        }
        if (to_install && cnt == X) {
            cnt = 0;
            to_install = false;
        }
        prev = map[r][c];
    }
    return !to_install;
}

bool checkCol(int c, int N, int X, vector<vector<int> > &map) {
    int prev = map[0][c];
    int cnt = 0;
    bool to_install = false;

    for (int r=0; r<N; r++) {
        if (abs(map[r][c] - prev) > 1) return false;
        if (prev == map[r][c]) cnt++;
        if (map[r][c] - prev == 1) {
            if (cnt < X) return false;
            cnt = 1;
        }
        if (prev - map[r][c] == 1) {
            if (to_install) return false;
            to_install = true;
            cnt = 1;
        }
        if (to_install && cnt == X) {
            cnt = 0;
            to_install = false;
        }
        prev = map[r][c];
    }
    return !to_install;
}

int solve(int N, int X, vector<vector<int> > &map) {
    int answer = 0;

    for (int r=0; r<N; r++) {
        answer += checkRow(r, N, X, map);
    }
    for (int c=0; c<N; c++) {
        answer += checkCol(c, N, X, map);
    }

    return answer;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;

	freopen("sample_input.txt", "r", stdin);
	cin>>T;
	
	for(test_case = 1; test_case <= T; ++test_case)
	{
        int N, X;
        vector<vector<int> > map;

        cin >> N >> X;

        map.assign(N, vector<int>(N, 0));
        for (int i=0; i<N; i++) {
            for (int j=0; j<N; j++) {
                cin >> map[i][j];
            }
        }

        cout << "#" << test_case << " " << solve(N, X, map) << endl;
	}
	return 0;
}