#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

struct Rotate {
    int num;
    bool is_clockwise;
};

vector<vector<vector<int> > > face = { { {1, 6} }, { {0, 2}, {2, 6} }, { {1, 2}, {3, 6} }, { {2, 2} } };

void rotate(int org[4][8], int num, bool is_clockwise) {
    int* temp = new int[8];
    int add = (is_clockwise ? 1 : -1);
    for (int i=0; i<8; i++) {
        temp[(i+add+8) % 8] = org[num][i];
    }

    memcpy(org[num], temp, 8 * sizeof(int));
}

void rotateBeside(int magnets[4][8], int num, bool is_clockwise, bool is_left, vector<Rotate> &rotated) {

    if (num == 0 || num == 3) return;
    
    int compare_num = num + 1;
    if (!is_left) compare_num = num - 1;

    int compare_tooth = 6;
    if (!is_left) compare_tooth = 2;

    if (magnets[num][(compare_tooth + 4) % 8] != magnets[compare_num][compare_tooth]) {
        rotated.push_back(Rotate{compare_num, !is_clockwise});
        rotateBeside(magnets, compare_num, !is_clockwise, compare_num > num, rotated);
    }

}

void rotateWith(int magnets[4][8], int num, bool is_clockwise) {
    vector<Rotate> rotated = { Rotate{num, is_clockwise} };
    vector<vector<int> > face_with = face[num];

    for (int i=0; i<face_with.size(); i++) {
        int beside_num = face_with[i][0];
        int beside_tooth = face_with[i][1];
        
        int compare = magnets[num][2];
        if (beside_tooth == 2) {
            compare = magnets[num][6];
        }

        if (compare != magnets[beside_num][beside_tooth]) {
            rotated.push_back(Rotate{beside_num, !is_clockwise});
            rotateBeside(magnets, beside_num, !is_clockwise, beside_num > num, rotated);
        }
    }

    for (int i=0; i<rotated.size(); i++) {
        rotate(magnets, rotated[i].num, rotated[i].is_clockwise);
    }
}

    

int calculate(int magnets[4][8]) {
    int sum = 0;
    for (int i=0; i<4; i++) {
        sum += (magnets[i][0] == 1 ? pow(2, i) : 0);
    }
    return sum;
}

int solve(int K, int magnets[4][8], int** rotation) {
    int score = 0;

    for (int i=0; i<K; i++) {
        int num = rotation[i][0] - 1;
        bool is_clockwise = rotation[i][1] == 1 ? true : false;

        rotateWith(magnets, num, is_clockwise);
    }

    score += calculate(magnets);
    return score;
}

int main(int argc, char** argv)
{
	int test_case;
	int T;
	
	freopen("sample_input.txt", "r", stdin);
	cin>>T;
    
	for(test_case = 1; test_case <= T; ++test_case)
	{
        int K;
        int magnets[4][8];
        int** rotation;

        cin >> K;
        for (int i=0; i<4; i++) {
            for (int j=0; j<8; j++) {
                cin >> magnets[i][j];
            }
        }

        rotation = new int* [K];
        for (int i=0; i<K; i++) {
            int a, b;
            cin >> a >> b;
            rotation[i] = new int[2];
            rotation[i][0] = a;
            rotation[i][1] = b;
        }

        cout << "#" << test_case << " " << solve(K, magnets, rotation) << endl;
	}
	return 0;
}