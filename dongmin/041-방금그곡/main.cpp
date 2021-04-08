#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Info {
    string start, end, title, notes;
    int runningTime() {
        int eh = stoi(end.substr(0,2));
        int em = stoi(end.substr(3));
        int sh = stoi(start.substr(0,2));
        int sm = stoi(start.substr(3));
        return (eh-sh)*60 + (em-sm);
    }
};

struct Music {
    int seq;
    vector<string> melody;
    string title;
    int matched;
    int running_time;
    
    bool operator<(Music m) {
        if (this->matched == m.matched) {
            if (this->running_time == m.running_time) {
                return this->seq > m.seq;
            }
            return this->running_time < m.running_time;
        }
        return this->matched < m.matched;
    }
};

vector<string> makeNotes(string note_str) {
    vector<string> notes;
    int len = note_str.size();
    for (int i=0; i<len;i++) {
        if (note_str[i] == '#') {
            string &new_note = notes.back();
            new_note += '#';
            continue ;
        }
        notes.push_back(note_str.substr(i,1));
    }
    return notes;
}

string solution(string m, vector<string> musicinfos) {
    vector<Info> infos;
    for (string info : musicinfos) {
        string s = info.substr(0, 5);
        string e = info.substr(6, 5);
        int comma = info.find(",", 12);
        string title = info.substr(12, comma - 12);
        string notes = info.substr(comma+1);
        infos.push_back(Info{s,e,title,notes});
    }
    
    int seq = 0;
    vector<string> query = makeNotes(m);
    vector<Music> musics;
    for (Info info : infos) {
        vector<string> notes = makeNotes(info.notes);
        vector<string> whole;
        
        int running_time = info.runningTime();
        int note_len = notes.size();
        for (int i=0; i<running_time; i++) {
            int idx = i%note_len;
            whole.push_back(notes[idx]);
        }
        
        musics.push_back(Music{seq++, whole, info.title, 0, running_time});
    }
    
    int qsize = query.size();
    string query_sequence = "";
    for (int i=0; i<qsize; i++) {
        query_sequence += query[i];
    }
    
    for (Music &music : musics) {
        int len = music.melody.size();
        
        for (int i=0; i<len; i++) {
            string n = music.melody[i];
            string qn = query[0];
            if (n != qn) continue;
            if (i+qsize > len) break;
            string sub = "";
            for (int j=i; j<i+qsize; j++) {
                sub += music.melody[j];
            }
            if (sub == query_sequence) {
                music.matched = 1;
            }
        }
    }
    
    sort(musics.begin(), musics.end());
    if (musics.back().matched == 0) {
        return "(None)";
    }
    
    return musics.back().title;
}