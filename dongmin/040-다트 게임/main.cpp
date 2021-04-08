#include <string>
#include <vector>
#include <iostream>
using namespace std;

bool isOption(char ch) {
    return ch=='*' || ch=='#';
}

int calculateBonus(char ch, int score) {
    if (ch == 'S') {
        return score;
    } else if (ch == 'D') {
        return score * score;
    }
    
    return score * score * score;
}

int solution(string dartResult) {
    int answer = 0;
    
    vector<int> scores;
    
    int result_length = dartResult.size();
    for(int i=0; i<result_length;) {
        int score = dartResult[i++] - '0';
        if (isdigit(dartResult[i])) {
            score = 10;
            i++;
        }
        
        int bonus = calculateBonus(dartResult[i++], score);
        scores.push_back(bonus);
        
        if (i>=result_length) {
            break;
        }
        if (isOption(dartResult[i])) {
            int sidx = scores.size() - 1;
            
            if (dartResult[i++] == '*') {
                scores[sidx] *= 2;
                if (sidx-1 >= 0) {
                    scores[sidx-1] *= 2;
                }
            } else {
                scores[sidx] *= -1;
            }
        }
    }
    
    int scores_length = scores.size();
    for (int i=0; i<scores_length; i++) {
        answer += scores[i];
    }
    
    return answer;
}