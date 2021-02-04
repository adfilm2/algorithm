#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>

using namespace std;
typedef struct NumberTime {
    int num;
    int time;
} NumberTime;

struct cmp {
    bool operator()(const NumberTime& a, const NumberTime& b) {
        if (a.time == b.time) {
            return a.num > b.num;
        }
        return a.time > b.time;
    }
};

int solution(vector<int> food_times, long long k) {
    int answer = 0;
    priority_queue<NumberTime, vector<NumberTime>, cmp> pq;
    for (int n=0; n<food_times.size(); n++) {
        pq.push(NumberTime{n+1, food_times[n]});
    }    

    int acctime = 0;
    long long remained_time = k;
    long long cache = 0;
    while (!pq.empty()) {
        NumberTime least_food = pq.top();
        int remained_food = pq.size();
        pq.pop();

        int food_cache = food_times[least_food.num-1];
        food_times[least_food.num-1] = 0;

        int cycle_time = least_food.time - acctime;
        acctime += cycle_time;

        if (cycle_time == 0) continue;

        cache = remained_time;
        remained_time -= ((long long)cycle_time * (long long)remained_food);

        if (remained_time < 0) {
            pq.push(least_food);
            acctime -= cycle_time;
            food_times[least_food.num-1] = food_cache;
            break;
        }
    }

    if (remained_time >= 0) return -1;
    
    // 한 사이클을 돌 수 없는 시간만 남음
    remained_time = cache;
    for (int i=0; i<food_times.size(); i++) {
        if (food_times[i] != 0) {
            food_times[i] -= acctime;
        }
    }

    vector<int> remained_foods;
    while (!pq.empty()) {
        remained_foods.push_back(pq.top().num);
        pq.pop();
    }

    sort(remained_foods.begin(), remained_foods.end());
    answer = remained_foods[remained_time % (long long)remained_foods.size()]; 

    return answer;
}