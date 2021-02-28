#include <string>
#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>

using namespace std;

string toLower(string str) {
    string ret = "";
    for (auto c: str) {
        ret += tolower(c);
    }
    return ret;
}
bool isAlphabetString(string str) {
    
    for (int i=0; i<str.size(); i++) {
        if (!isalpha(str[i])) {
            return false;
        }
    }
    return true;
}

int solution(string str1, string str2) {
    int answer = 0;
    
    multiset<string> ms1, ms2;
    multiset<string> intersection_set, union_set;
    
    str1 = toLower(str1);
    str2 = toLower(str2);
    for (int i=0; i<str1.length()-1; i++) {
        string splited = str1.substr(i,2);
        if (isAlphabetString(splited))
            ms1.insert(splited);
    }
    for (int i=0; i<str2.length()-1; i++) {
        string splited = str2.substr(i,2);
        if (isAlphabetString(splited))
            ms2.insert(splited);
    }
    
    set_intersection(ms1.begin(), ms1.end(), ms2.begin(), ms2.end(), 
                     std::inserter(intersection_set, intersection_set.end()));
    set_union(ms1.begin(), ms1.end(), ms2.begin(), ms2.end(),
              std::inserter(union_set, union_set.end()));
    
    if (union_set.size() == 0 && intersection_set.size() == 0) {
        return 65536;   
    }
    float jakad = (float)intersection_set.size() / union_set.size();
    answer = (int)(jakad * 65536);
    
    return answer;
}