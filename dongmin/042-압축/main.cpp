#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

vector<int> solution(string msg) {
    vector<int> answer;
    map<string, int> dict;
    
    int next = 27;
    char ch = 'A';
    for (int i=1; i<27; i++) {
        dict[to_string(ch++)] = i;
    }
    
    int len = msg.size();
    int i=0;
    while (true) {
        string prev = to_string(msg[i]);
        if (i == len-1) {
            answer.push_back(dict[prev]);
            break;
        }
        
        int prev_i = i;
        int j;
        for (j=2; i+j<=len; j++) {
            string sub = msg.substr(i,j);
            if (dict.count(sub) == 0) {
                answer.push_back(dict[prev]);
                dict[sub] = next++;
                prev_i = i;
                i = i+j-1;
                break;
            } else {
                prev = sub;
            }
        }
        
        if (prev_i+j==len+1) {
            answer.push_back(dict[prev]);
            break;
        }
    }
    
    return answer;
}