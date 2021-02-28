#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;
struct Time {
    int h, m;
    Time(int h, int m) {
        this->h = h;
        this->m = m;
    }
    Time(string time) {
        auto colon_pos = time.find(":");
        this->h = stoi(time.substr(0,colon_pos));
        this->m = stoi(time.substr(colon_pos+1));
    }
    Time(int minute) {
        this->h = 0;
        this->m = minute%60;
        this->h += (minute/60);
    }
    
    Time& operator+=(const Time& a) {
        int mnt = this->m + a.m;
        this->m = mnt%60;
        this->h = this->h + a.h + mnt/60;
        return *this;
    }
    Time operator-(int m) {
        int minute = this->m - m;
        int hour = this->h;
        while (minute < 0) {
            minute += 60;
            hour-= 1;
        }
        return Time(hour, minute);
    }
    
    // 여러개의 int를 하나의 문자열로 편하게 바꾸는 방법: stringstream (#include <sstream>)
    string toString() {
        stringstream ss;
        ss << h/10 << h%10 << ":" << m/10 << m%10;
        return ss.str();
    }
};

bool operator==(const Time& left, const Time& right) {
    return left.h==right.h && left.m==right.m;
}
bool operator<(const Time& left, const Time& right) {
    if (left.h == right.h) {
        return left.m < right.m;
    }
    return left.h < right.h;
}
bool operator<=(const Time& left, const Time& right) {
    if (left.h == right.h) {
        return left.m <= right.m;
    }
    return left.h <= right.h;
}

string solution(int n, int t, int m, vector<string> timetable) {
    string answer = "";
    
    /**
     *  1. 버스 도착 정보를 미리 구한다.
     *  @variable crew_assigned_map : 크루들이 어떤 시각에 오는 버스에 탑승하는지 매핑하는 변수
     **/ 
    map<Time, vector<Time> > crew_assigned_map;
    Time bus_arrival("09:00");
    
    for(int i=0; i<n; i++) {
        crew_assigned_map[bus_arrival] = vector<Time>();
        bus_arrival += Time(t);
    }
    
    /**
     *  2. 크루들의 도착 정보를 정렬한다.
     *     crew_assigned_map에 매핑할 때, 순서를 보장한다.
     **/ 
    sort(timetable.begin(), timetable.end());
    
    /**
     * 3. 순서대로 정렬된 크루 도착 정보를 버스 도착 시각과 비교하여 탈 수 있는 버스에 할당한다.
     *   @statement crew_arrival <= bus_time.first && bus_time.second.size() < m
     *    : 크루 도착 정보가 버스 도착 시각과 같거나 작고, 그 버스에 수용할 수 있는 인원 m보다 적은 인원이 탔다면,
     *      그 버스 도착 정보에 할당하고 그 크루의 탐색을 종료한다.
     **/ 
    for (int i=0; i<timetable.size(); i++) {
        Time crew_arrival(timetable[i]);
    
        for (auto& bus_time: crew_assigned_map) {
            
            if (crew_arrival <= bus_time.first && bus_time.second.size() < m) {
                bus_time.second.push_back(crew_arrival);
                break;
            }
        }
    }
    
    /**
     * 4. 콘이 마지막 버스를 타고 싶어하기 때문에 crew_assgined_map에서 마지막 element를 뽑아와야 한다.
     *   @stl_reference std::prev (#include <algorithm>)
     *     : 파라미터로 주어진 반복자의 하나 이전 반복자를 리턴한다. 반대의 기능으로 std::advance가 있다.
     *   
     * 5. 그 버스에 탄 사람이 m명 보다 적다면, 즉 수용할 수 있는 인원이 남았다면
     *    그 버스가 오는 시각에 콘이 도착하면 된다.
     * 
     * 6. [놓친 부분]
     *    그 버스가 꽉 찼다면, 마지막으로 탄 사람보다 1분 일찍 오면 된다.
     **/ 
    vector<Time> last_bus_boarding_time = prev(crew_assigned_map.end())->second;
    
    if (last_bus_boarding_time.size() < m) {
        Time last_bus_time = prev(crew_assigned_map.end())->first;
        answer = last_bus_time.toString();
    }
    else {
        
        Time latest = last_bus_boarding_time.back();
        Time one_minute_ago = latest - 1;
        answer = one_minute_ago.toString();
    }

    return answer;
}