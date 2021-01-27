#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct node {
    node(int x, int y, int num) : x(x), y(y), num(num), left(NULL), right(NULL){}
    node* left;
    node* right;
    int x,y,num;
};

vector<node> nodeList;
vector<int> preAns;
vector<int> postAns;

bool compare(node& a, node& b){
    if(a.y == b.y){
        return a.x < b.x;
    }else{
        return a.y > b.y;
    }
}

void add(node * p, node * c){
    
        if(c->x < p->x){
            if(p->left == NULL){
                p->left = c;
            }else{
                add(p->left, c);
            }
            
        }else{
            if(p->right == NULL){
                p->right = c;
            }else{
                add(p->right, c);
            }
        }
        
    }

void pre(node * p){
    if(p){
        preAns.push_back(p->num);
        pre(p->left);
        pre(p->right);
    }
}

void post(node * p){
    if(p){
        post(p->left);
        post(p->right);
        postAns.push_back(p->num);
    }
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer;
    
    for(int i=0; i<nodeinfo.size(); i++){
        nodeList.push_back(node(nodeinfo[i][0],nodeinfo[i][1],i+1));
    }
    sort(nodeList.begin(), nodeList.end(), compare);
    
    
    for(int i=0 ;i<nodeList.size(); i++){
        cout << nodeList[i].x << " "<< nodeList[i].y << endl;
    }
    node * root = &nodeList[0];
    
    for(int i=1; i<nodeList.size(); i++){
        add(root, &nodeList[i]);
    }
    
    pre(root);
    post(root);
    
    answer.push_back(preAns);
    answer.push_back(postAns);
    
    for(int i=0; i<2;i++){
        for(int j=0; j<answer[0].size();j++){
            cout << answer[i][j] << " ";
        }
        cout << endl;
    }
    
    
    return answer;
}


int main(void){
    vector<vector<int>> nodeinfo = {{5,3},{11,5},{13,3},{3,5},{6,1},{1,3},{8,6},{7,2},{2,2}};
    vector<vector<int>> answer;
    for(int i=0; i<nodeinfo.size(); i++){
        nodeList.push_back(node(nodeinfo[i][0],nodeinfo[i][1],i+1));
    }
    sort(nodeList.begin(), nodeList.end(), compare);
    
    
    for(int i=0 ;i<nodeList.size(); i++){
        cout << nodeList[i].x << " "<< nodeList[i].y << endl;
    }
    node * root = &nodeList[0];
    
    for(int i=1; i<nodeList.size(); i++){
        add(root, &nodeList[i]);
    }
    
    pre(root);
    post(root);
    
    answer.push_back(preAns);
    answer.push_back(postAns);
    
    for(int i=0; i<2;i++){
        for(int j=0; j<answer[0].size();j++){
            cout << answer[i][j] << " ";
        }
        cout << endl;
    }
    
}

 


