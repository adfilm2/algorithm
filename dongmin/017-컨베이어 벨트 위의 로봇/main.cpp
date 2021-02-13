#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
using namespace std;

int main() {

    int N, K;
    vector<int> durability;

    cin >> N >> K;
    durability.assign(2*N, 0);
    for(int i=0; i<durability.size(); i++){
        cin >> durability[i];
    }

    vector<int> belt;
    for(int i=0; i<2*N; i++) {
        belt.push_back(i);
    }

    deque<int> robots;
    int zero_cnt = 0;
    int step = 0;
    while(zero_cnt<K) {

        int prev = belt[2*N-1];
        for(int i=0; i<2*N; i++) {
            int temp = belt[i];
            belt[i] = prev;
            prev = temp;
        }

        if(robots.size() > 0) {
            int front_robot = robots.front();
            if(front_robot == belt[N-1]) {
                robots.pop_front();
            }
        }

        for(int i=0; i<robots.size(); i++) {
            
            int next = (robots[i] + 1)%belt.size();
            if(durability[next]>0 && (i==0 || robots[i-1] != next)) {

                robots[i] = next;
                durability[next]--;
                if(durability[next] == 0) zero_cnt++;
            }
        }

        if(robots.size()>0 && (robots.front() == belt[N-1])) {
            robots.pop_front();
        }

        if((robots.size()==0 || robots.back() != belt[0]) && durability[belt[0]] > 0){
            robots.push_back(belt[0]);
            durability[belt[0]]--;
            if(durability[belt[0]] == 0) zero_cnt++;
        }

        step += 1;
    }

    printf("%d",step);
    return 0;
}