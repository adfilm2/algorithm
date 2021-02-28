#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

struct Time {
    int h,m,s,ms;
    Time(int msec) {
        ms = msec%1000;
        s = (msec/1000)%60;
        m = (msec/(1000*60))%60;
        h = (msec/(1000*60*60))%24;
    }
    Time(string s) {
        auto h_idx = s.find(":");
        auto m_idx = s.find(":", h_idx+1);
        auto s_idx = s.find(".", m_idx+1);
        
        this->h = stoi(s.substr(0, 2));
        this->m = stoi(s.substr(h_idx+1, 2));
        this->s = stoi(s.substr(m_idx+1, 2));
        this->ms = stoi(s.substr(s_idx+1));
    }
    Time(int h, int m, int s, int ms){
        this->h=h; this->m=m; this->s=s; this->ms=ms;
    }
    
    int toMsec() {
        return ms + 1000*s + 60000*m + 3600000*h;
    }
    
};

ostream& operator<<(ostream& os, const Time& a) {
    os << a.h << " " << a.m << " " << a.s << " " << a.ms;
    return os;
}


int solution(vector<string> lines) {
    int answer = 0;
    
    vector<Time> end_time;
    vector<int> processing;
    
    // 로그 파싱
    for (int i=0; i<lines.size(); i++) {
        auto date_end = lines[i].find(" ");
        auto time_end = lines[i].find(" ", date_end+1);
        auto processing_end = lines[i].find("s", time_end+1);
        
        string time_log = lines[i].substr(date_end+1, time_end-date_end-1);
        Time end = Time(time_log);
        string processing_time = lines[i].substr(time_end+1, processing_end-time_end-1);
        
        float process = stof(processing_time);
        int process_sec = (int)(process * 1000);
        
        end_time.push_back(end);
        processing.push_back(process_sec);
    }
    
    vector<int> plus_time, minus_time;
    
    // 시작 시간이 가장 빠른 시간을 구함
    int min_start = 987654321;
    for (int i=0; i<end_time.size(); i++) {
        int start_time = end_time[i].toMsec() - processing[i]+1;
        if(min_start > start_time) {
            min_start = start_time;
        }
    }
    
    // 언제 요청이 시작하고 끝나는지 msec 배열에 체킹.
    // 그 크기는 (마지막 로그의 끝나는 시각 - 시작 시각이 가장 빠른 시각 + 1)
    plus_time.assign(end_time.back().toMsec() - min_start + 1, 0);
    minus_time.assign(plus_time.begin(), plus_time.end());
    int start = end_time.front().toMsec() - processing.front()+1;

    for (int i=0; i<end_time.size(); i++) {
        int start_time = end_time[i].toMsec() - processing[i]+1;
        
        plus_time[start_time - min_start] += 1;
        minus_time[end_time[i].toMsec() - min_start] += 1;
    }
        
    if (end_time.size() == 1) return 1;
    if (plus_time.size() < 1000) {
        return end_time.size();
    }
    
    // 처음 1초 구간에서 몇개의 요청을 처리하는지 계산
    int init = 0;
    for (int t=0; t<1000; t++) {
        if (plus_time[t] != 0) init+=plus_time[t];
    }
    
    /**
     * 연속적인 배열을 1000 크기의 구간을 가지고 탐색
     * 끝 포인터가 처리를 시작하는 시각(plus_time[t] != 0)을 발견하면 처리량 증가
     * 시작 포인터가 처리를 끝나는 시각(minus_time[t] != 0)을 발견하면 다음 time_unit에 처리량 감소 
     *  -> carry 사용
     **/
    int max_tp = 0;
    int carry = 0;
    int prev_tp = init;
    
    for (int t=1; t<plus_time.size()-999; t++) {
        int tp = prev_tp;
        
        tp += carry;
        carry = 0;
        if (plus_time[t+999] != 0) tp+=plus_time[t+999];
        if (minus_time[t] != 0) carry-=minus_time[t];
        
        if (tp > max_tp) max_tp = tp;
        prev_tp = tp;
    }

    return max_tp;
}