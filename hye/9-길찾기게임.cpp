#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define max(x,y) ((x)>(y))?(x):(y)
using namespace std;

struct node {
    node(int x, int y, int num) : x(x), y(y), num(num){}
    node* left;
    node* right;
    int x,y,num;
    
};

vector<node> nodeList;

bool compare(node& a, node& b){
    if(a.y == b.y){
        return a.x < b.x;
    }else{
        return a.y > b.y;
    }
}

void add(node * p, node * c){
    for(int i=0; i<nodeList.size(); i++){
        if(nodeList[i+1].x < nodeList[i].x){
            nodeList[i].left = &nodeList[i+1];
        }
        
    }
}


vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer;
    return answer;
}


int main(void){
    vector<vector<int>> nodeinfo = {{5,3},{11,5},{13,3},{3,5},{6,1},{1,3},{8,6},{7,2},{2,2}};
    
    int y=0;
    for(int i=0; i<nodeinfo.size(); i++){
        nodeList.push_back(node(nodeinfo[i][0],nodeinfo[i][1],i+1));
        y = max(nodeinfo[i][1], y );
    }
    sort(nodeList.begin(), nodeList.end(), compare);
    
    
    for(int i=0 ;i<nodeList.size(); i++){
        cout << nodeList[i].x << " "<< nodeList[i].y << endl;
    }
    
    for(int i=1; i<nodeList.size(); i++){
        add(&nodeList[0], &nodeList[i]);
    }
    
}

 



