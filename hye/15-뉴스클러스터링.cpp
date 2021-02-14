
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int findInter(vector<string> set1, vector<string> set2){
    int n =0;
    
    vector<string> minset = (set1 < set2)? set1 : set2;
    vector<string> bigset = (set1 < set2)? set2 : set1;
    
    int save =0;
    for(int i=0; i<minset.size(); i++){
        
        for(int j=save; j<bigset.size(); j++){
            if(minset[i][0] < bigset[j][0]) break;
            if(minset[i] == bigset[j]){
                n++;
                save = j+1;
                break;
            }
            
        }
    }
    
    
    return n;
}



vector<string> makeSet(string str){
    vector<string> set;
    for(int i=0; i<str.length()-1; i++){
        if(str[i+1]<65 || str[i+1]>90 || str[i]<65 || str[i]>90) continue;
        set.push_back(str.substr(i,2));
    }
    
    return set;
}


int solution(string str1, string str2) {
    int answer = 0;
    
    transform(str1.begin(), str1.end(), str1.begin(), ::toupper);
    transform(str2.begin(), str2.end(), str2.begin(), ::toupper);
    
    vector<string> set1 = makeSet(str1);
    vector<string> set2 = makeSet(str2);
    
    if(set1.empty() && set2.empty()) return 65536;
    
    sort(set1.begin(), set1.end());
    sort(set2.begin(), set2.end());
    
    int inter = findInter(set1, set2);
    int uni = set1.size() + set2.size() - inter;
    
    
    answer = (int)(65536 * inter / uni);
    return answer;
}


int main(void){
    
    string str2 = "aaaazxy"; //6개, aa,aa,aa,az,zx,xy
    string str1 = "aaail";  // aa,aa,ai,al
    
    transform(str1.begin(), str1.end(), str1.begin(), ::toupper);
    transform(str2.begin(), str2.end(), str2.begin(), ::toupper);
    
    vector<string> set1 = makeSet(str1);
    vector<string> set2 = makeSet(str2);
    
    for(int i=0; i<set2.size(); i++){
        cout << set2[i] << " ";
    }
    
    sort(set1.begin(), set1.end());
    sort(set2.begin(), set2.end());
    
    int inter = findInter(set1, set2);
    int uni = set1.size() + set2.size() - inter;
    cout << inter << "   " ;
    cout << ((float)inter/(float)uni)*65536;
    
    
}
