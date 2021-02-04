#include <string>
#include <vector>
#include <map>

using namespace std;
typedef struct webpage {
    string url;
    string body;
} webpage;

struct tag {
    string name;
    vector<tag*> child;
    map<string, string> properties;
    string text;
};

struct parser {
    tag* root;
    string page;
    vector<tag*> tag_stack;

    void parseProperty(int& idx) {

        int closed_tag_idx = page.find_first_of('>', idx);
        int key_last_idx = page.find_first_of('=', idx);
        while (closed_tag_idx > key_last_idx) {
            int value_last_idx = page.find_first_of('"', key_last_idx+2);
            string key = string(page.begin()+idx, page.begin()+key_last_idx);
            string value = string(page.begin()+key_last_idx+2, page.begin()+value_last_idx-1);
        }


    }

    void parse() {

        for (int i=0; i<page.size(); i++) {
            
            if (page[i] == '<') {
                string tag_name;
                if (page[i+1] == '/') {
                    // 닫는 태그 경우
                    int closed_tag_idx = page.find_first_of('>', i);
                    tag_name = string(page.begin() + i+2, page.begin() + closed_tag_idx);
                    tag* child_tag = tag_stack.back();
                    tag_stack.pop_back();
                    tag* parent_tag = tag_stack.back();
                    parent_tag->child.push_back(child_tag);
                    i = closed_tag_idx + 1;
                }
                else {
                    // 여는 태그 경우
                    int first_space_idx = page.find_first_of(' ', i);
                    int closed_tag_idx = page.find_first_of('>', i);

                    if (first_space_idx < closed_tag_idx) {
                        tag_name = string(page.begin() + i, page.begin() + first_space_idx);
                        i = first_space_idx+1;
                        parseProperty(i);
                    }
                    else {
                        tag_name = string(page.begin() + i, page.begin() + closed_tag_idx);
                    }

                    tag* new_tag = new tag{tag_name, {}, {}, ""};
                }
            }
        }
    }
};

int solution(string word, vector<string> pages) {
    int answer = 0;
    int num_of_pages = pages.size();

    vector<webpage> parsed_pages;
    parsed_pages.assign(num_of_pages, {"", ""});

    for (int i=0; i<num_of_pages; i++) {
        parser page_parser = {nullptr, pages[i]};
        

    }

    return answer;
}