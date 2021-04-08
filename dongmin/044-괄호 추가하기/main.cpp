#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

void solve(int N, string exp);

int main() {    
    int N;
    cin >> N;

    string exp;
    cin >> exp;
    solve(N, exp);

    return 0;
}

int operate(int l, int r, char c) {
    if (c == '+') return l + r;
    if (c == '-') return l - r;
    return l * r;
}

int calculate(string &operators, vector<int> &operands) {
    int n = operators.size();
    int result = operands[0];
    for (int i=0; i<n; i++) {
        result = operate(result, operands[i+1], operators.at(i));
    }
    return result;
}

void combination(int len, int idx, vector<int>& paren, string &operators, vector<int> &operands, int& max) {

    if (idx > len) {
        int picked_size = paren.size();
        int N = operands.size();
        vector<bool> checked(N, false);

        if (picked_size == 0) return;
        vector<int> final_operands;
        string final_operators = "";
        int p_idx = 0;

        for (int i=0; i<N; i++) {
            if (p_idx < paren.size() && paren[p_idx] == i && i != N-1) {
                p_idx += 1;
                final_operands.push_back(operate(operands[i], operands[i+1], operators.at(i)));
                checked[i] = true;
                checked[i+1] = true;
            } else if (!checked[i]) {
                final_operands.push_back(operands[i]);
                checked[i] = true;
            }

            if (N-1 == i) break;
            if (!checked[i+1]) {
                final_operators += operators.at(i);
            }
        }
        
        int result = calculate(final_operators, final_operands);
        if (result > max) {
            max = result;
        }
        return ;
    }

    paren.push_back(idx);
    combination(len, idx+2, paren, operators, operands, max);
    paren.pop_back();
    combination(len, idx+1, paren, operators, operands, max);
} 

void solve(int N, string exp) {
    string operators = "";
    vector<int> operands;
    operands.push_back(exp[0] - '0');

    for (int i=1; i<N; i+=2) {
        operators += exp[i];
        operands.push_back(exp[i+1] - '0');
    }

    int max = calculate(operators, operands);
    vector<int> paren;
    combination((N-1)/2, 0, paren, operators, operands, max);

    cout << max << endl;
}
