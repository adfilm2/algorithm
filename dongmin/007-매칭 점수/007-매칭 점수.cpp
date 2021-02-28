#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <unordered_map>

using namespace std;

int solution(string word, vector<string> pages) {
    int answer = 0;
    
    std::transform(word.begin(), word.end(), word.begin(), ::tolower);
    vector<string> page_urls;
    vector<int> base_scores;
    vector<int> link_nums;
    vector<vector<int> > links;
    
    unordered_map<string, int> url_map;
    
    for (int i=0; i<pages.size(); i++) {
        auto meta_property = pages[i].find("<meta property=");
        auto url_pos = pages[i].find("content=\"", meta_property);
        auto url_end = pages[i].find("\"", url_pos+9);
        string url = pages[i].substr(url_pos+9, url_end-url_pos-9);
        page_urls.push_back(url);
        url_map[url] = i;
    }
    
    for (int i=0; i<pages.size(); i++) {        
        
        // 기본 점수
        int base_score = 0;
        string lower_html = "";
        std::transform(pages[i].begin(), pages[i].end(), back_inserter(lower_html), ::tolower);
        
        size_t prev = 0;
        auto next = lower_html.find(word);
        while (next != string::npos) {
            string found = lower_html.substr(next, word.size());
            if (!isalpha(lower_html[next-1]) && !isalpha(lower_html[next+word.size()])) {
                base_score += 1;
            }
            
            prev = next;
            next = lower_html.find(word, prev+word.size());
        }
        
        base_scores.push_back(base_score);
    }
    
    // 링크 개수
    link_nums.assign(pages.size(), 0);
    links.assign(pages.size(), vector<int>());
    for (int i=0; i<pages.size(); i++) {
        size_t prev = 0;
        auto atag_start = pages[i].find("<a href=");
        while (atag_start != string::npos) {
        
            auto url_end = pages[i].find(">", atag_start);
            string link = pages[i].substr(atag_start+9, url_end-atag_start-10);
            
            link_nums[i] += 1;
            if (url_map.count(link) != 0)
                links[i].push_back(url_map[link]);
            
            prev = atag_start;
            atag_start = pages[i].find("<a href=", prev+10);
        }
    }
    
    // 링크 점수
    vector<double> base_per_links(pages.size(), 0);
    for (int i=0; i<pages.size(); i++) {
        base_per_links[i] = (double)base_scores[i] / link_nums[i];
    }
    
    vector<double> link_scores(pages.size(), 0);
    for (int i=0; i<link_scores.size(); i++) {
        for (int j=0; j<links[i].size(); j++) {
            link_scores[links[i][j]] += base_per_links[i];
        }
    }
    
    vector<double> matching_scores(pages.size(), 0);
    for (int i=0; i<pages.size(); i++) {
        matching_scores[i] += link_scores[i];
        matching_scores[i] += base_scores[i];
    }
    
    answer = max_element(matching_scores.begin(), matching_scores.end()) - matching_scores.begin();
    return answer;
}