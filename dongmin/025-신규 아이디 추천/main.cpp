#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include <unordered_set>

using namespace std;

bool isValidChar(char c) {
    return (c >= '0' && c <= '9') || (c >= 'a' && c<='z') || c == '-' || c == '_' || c == '.';
}

string solution(string new_id) {
    string answer = "";
    //1
    std::transform(new_id.begin(), new_id.end(), new_id.begin(), ::tolower);
    //2
    string banned_char;
    for(char ch: new_id) {
        if(!isValidChar(ch)) {
            banned_char += ch;
        }
    }
    for(auto ch: banned_char) {
        new_id.erase(std::find(new_id.begin(), new_id.end(), ch));
    }
    //3
    typedef struct DotDup {
        int pos;
        int num;
    } DotDup;

    vector<DotDup> dups;
    bool isDot = false;
    int start = 0;
    int num = 1;
    for(int i=0; i<new_id.size(); i++) {
        char ch = new_id[i];
        if(!isDot) {
            if(ch == '.') {
                start = i;
                isDot = true;
            }
            else isDot = false;
        }
        else {
            if(ch == '.') {
                num += 1;
            }
            else {
                isDot = false;
                dups.push_back({start, num});
                num = 1;
            }
        }
    }
    if(num >= 2) {
        dups.push_back({start, num});
    }

    for(int i=dups.size()-1; i>=0; i--) {
        new_id.erase(dups[i].pos+1, dups[i].num-1);
    }

    //4
    if(new_id.back() == '.') {
        new_id.pop_back();
    }
    if(new_id.front() == '.') {
        new_id.erase(0,1);
    }

    //5
    if(new_id.size() == 0) new_id += 'a';

    //6
    if(new_id.size() >= 16) {
        new_id.erase(new_id.begin()+15, new_id.end());
        if(new_id.back() == '.') new_id.pop_back();
    }
    //7
    if(new_id.size() <= 2) {
        char backch = new_id.back();
        while(new_id.size() != 3) {
            new_id += backch;
        }
    }

    answer = new_id;
    return answer;
}