#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
using namespace std;

struct Pos {int r,c;};
bool visited[13];
map<int, vector<Pos> > buildings;

void dfs(int whole, int pick, int idx, int cur, int& min) {
    if (pick == cur) {
        int dist_sum = 0;
        int house_num = buildings[1].size();
        int chicken_num = buildings[2].size();

        for (int i=0; i<house_num; i++) {
            int min_dist = 987654321;
            Pos house = buildings[1][i];
            for (int j=0; j<chicken_num; j++) {
                if (visited[j]) continue ;
                Pos chicken = buildings[2][j];
                int dist = abs(chicken.r - house.r) + abs(chicken.c - house.c);
                if (min_dist > dist) min_dist = dist;
            }
            dist_sum += min_dist;
        }

        if (min > dist_sum) min = dist_sum;
        return ;
    }

    for (int i=idx; i<whole; i++) {
        if (visited[i]) continue ;
        visited[i] = true;
        dfs(whole, pick, i, cur+1, min);
        visited[i] = false;
    }
}

void solve(int n, int m, int chicken_num, vector<vector<int> > city_map) {
    int removed = chicken_num - m;
    int min_distance = 987654321;
    memset(visited, 0, sizeof(visited));

    buildings[1] = vector<Pos>();
    buildings[2] = vector<Pos>();
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (!city_map[i][j]) continue ;
            buildings[city_map[i][j]].push_back({i,j});
        }
    }

    dfs(chicken_num, removed, 0, 0, min_distance);
    cout << min_distance;
}


int main() {   
    int N, M;
    cin >> N >> M;
    vector<vector<int> > city_map(N, vector<int>(N,0));

    int chicken_num = 0;
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            cin >> city_map[i][j];
            if (city_map[i][j] == 2) {
                chicken_num++;
            }
        }
    }

    solve(N, M, chicken_num, city_map);
    return 0;
}