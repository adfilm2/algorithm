
#include <iostream>
#include <string>
#include <vector>

using namespace std;


bool valid(char c){
    if(c < 58 && c > 47) return true;
    if(c <123 && c > 96) return true;
    if(c == 46 || c == 45 || c == 95) return true;
    
    
    return false;
}


string solution(string new_id) {
    string step2 = "";
    string step3 = "";

    //1단계. 소문자로
    
    for(int i=0; i<new_id.size(); i++){
        new_id[i]= tolower(new_id[i]);
    }
    
    //2단계 특문제거
    char a,b;
    for(int i=0; i<new_id.size();i++){
        a = new_id[i];
        if(valid(a)){
            step2 += a;
        }
    }
    
    
    //3단계 연속마침표 제거
    for(int i=0; i<step2.size();i++){
        a = step2[i];
        b = step2[i+1];
        if(a == 46 && b == 46) continue;
        step3 += a;
    }
    
    
    //4단계 앞뒤마침표 제거
    if(step3.front() == 46) step3.erase(step3.begin());
    if(step3.back() == 46) step3.erase(step3.end()-1);
    
    
    //5단계
    if(step3.empty()) step3 += "a";
    
    //6단계
    if(step3.length()>=16) step3.erase(15);
    if(step3.front() == 46) step3.erase(step3.begin());
    if(step3.back() == 46) step3.erase(step3.end()-1);
    
    
    //7단계
    if(step3.length() <= 2){
        a = step3.back();
        while (step3.length() < 3) {
            step3 += a;
        }
    }

    
    return step3;
}
