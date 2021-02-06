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
    
    map<Time, vector<Time> > crew_assigned_map;
    Time bus_arrival("09:00");
    
    for(int i=0; i<n; i++) {
        crew_assigned_map[bus_arrival] = vector<Time>();
        bus_arrival += Time(t);
    }
    
    sort(timetable.begin(), timetable.end());
    
    for (int i=0; i<timetable.size(); i++) {
        Time crew_arrival(timetable[i]);
    
        for (auto& bus_time: crew_assigned_map) {
            
            if (crew_arrival <= bus_time.first && bus_time.second.size() < m) {
                bus_time.second.push_back(crew_arrival);
                break;
            }
        }
    }
    
    vector<Time> last_bus_boarding_time = prev(crew_assigned_map.end())->second;
    size_t lbbt_size = last_bus_boarding_time.size();
    
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