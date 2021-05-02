#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
using namespace std;

struct Path {
    int sr, sc;
    int er, ec;
    bool operator==(const Path &o) const {
        return sr==o.sr && sc==o.sc && er==o.er && ec==o.ec;
    }
    bool operator()(const Path &o) const {
        return sr==o.sr && sc==o.sc && er==o.er && ec==o.ec;
    }
};

namespace std {
    template<>
    struct hash<Path> {
        size_t operator()(const Path& o) const {
            return o.sr ^ o.sc ^ o.er ^ o.ec;
        }
    };
}

unordered_map<char, int> direction_map = {{'U', 0}, {'R', 1}, {'D', 2}, {'L', 3}};
int d[4][2] = {{-1,0}, {0,1}, {1,0}, {0,-1}};

bool isValid(int r, int c) {
    return r>=0 && r<11 && c>=0 && c<11;
}

template <typename K>
bool isExist(std::unordered_set<K>& s, K key) {
    auto itr = s.find(key);
    if (itr != s.end()) {
        return true;  
    }
    return false;
}

int solution(string dirs) {
    int answer = 0;
    
    unordered_set<Path> path;
    int r = 5, c = 5;
    for (auto dir: dirs) {
        int idx = direction_map[dir];
        int nr = r + d[idx][0];
        int nc = c + d[idx][1];
        Path p1 = {r,c,nr,nc};
        Path p2 = {nr,nc,r,c};
        
        if (!isValid(nr, nc)) continue;
        if (!isExist(path, p1)) {
            path.insert(p1);
            path.insert(p2);
            answer++;
        }
        
        r = nr; c = nc;
    }
    
    return answer;
}