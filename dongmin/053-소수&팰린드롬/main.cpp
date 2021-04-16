#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

bool isPalindrome(int num) {
    string str = to_string(num);
    const int len = str.length();
    for (int i=0; i<len/2; i++) {
        if (str[i] != str[len-1-i]) return false;
    }
    return true;
}


int main() {
    const int MAX = 1000000;
    int N;
    cin >> N;

    map<int, int> prime;
    bool eratos[1003002] = {0,};

    for (int i=2; i<1003002; i++) {
        if (eratos[i]) continue;
        prime[i] = 1;
        for (int j=i; j<1003002; j+=i) {
            eratos[j] = true;
        }
    }
    
    for (auto it = prime.lower_bound(N); it != prime.end(); it++) {
        if (isPalindrome(it->first)) {
            cout << it->first << endl;
            break;
        }
    }

    return 0;
}