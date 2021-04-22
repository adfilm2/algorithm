#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <unordered_set>

using namespace std;

struct Edge {
    int s,e,c;
    bool operator<(const Edge& o) const {
        if (c == o.c) {
            if (s == o.s) {
                return e > o.e;
            }
            return s > o.s;
        }
        return c > o.c;
    }
};

bool isCycle(int n, vector<vector<bool> > &graph, Edge edge) {
    vector<int> stack;
    vector<bool> visited(n, false);
    stack.push_back(edge.s);
    visited[edge.s] = true;
    
    while (!stack.empty()) {
        int v = stack.back();
        stack.pop_back();
        
        for (int i=0; i<n; i++) {
            if (visited[i]) continue;
            if (!graph[v][i]) continue;
            if (edge.e==i) return true;
            visited[i] = true;
            stack.push_back(i);
        }
    }
    return false;
    
}

bool isExist(unordered_set<int> &us, int v) {
    return us.find(v) != us.end();
}

int solution(int n, vector<vector<int>> costs) {
    int answer = 0;
    priority_queue<Edge> pq;
    
    for (auto e: costs) {
        pq.push(Edge{e[0], e[1], e[2]});
    }
    
    vector<vector<bool> > graph(n, vector<bool>(n, 0));
    int cnt = 0;
    
    while (cnt < n-1) {
        Edge ed = pq.top();
        pq.pop();
        if (isCycle(n, graph, ed)) continue;
        cnt++;
        graph[ed.s][ed.e] = 1;
        graph[ed.e][ed.s] = 1;
        answer += ed.c;
    }
    
    return answer;
}