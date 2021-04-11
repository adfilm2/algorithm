#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct node {
    bool is_root;
    int cnt;
    node* next[26];
    
    node(bool is_root) {
        this->is_root = is_root;
        cnt = 1;
        for (int i=0; i<26; i++) {
            next[i] = NULL;
        }
    }
    ~node() {
        for (int i=0; i<26; i++) {
            if (next[i] != NULL) {
                delete next[i];
            }
        }
    }
    
    void insert(const char* s) {
        if (*s == '\0') return;
        
        int asc = *s - 'a';
        if (next[asc] == NULL) {
            next[asc] = new node(false);
        } else {
            next[asc] -> add();
        }
        
        next[asc] -> insert(s + 1);
    }
    
    int find(const char* s, int num) {
        if (*s == '\0') return num;
        if (!is_root && cnt == 1) return num;
        
        int asc = *s - 'a';
        return next[asc] -> find(s+1, num+1);
    }
    
    void add() {
        cnt++;
    }
};

int solution(vector<string> words) {
    int answer = 0;
    node trie(true);
    
    for (string word: words) {
        trie.insert(word.c_str());
    }
    
    for (string word: words) {
        answer += trie.find(word.c_str(), 0);
    }
    return answer;
}