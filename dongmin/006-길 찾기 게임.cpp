#include <string>
#include <vector>
#include <algorithm>

using namespace std;
typedef struct info {
    int n, x, y;
} info;

struct node {
    info data;
    node *left;
    node *right;
};
struct tree {
    node* root = nullptr;
public:
    node* find(info value) {
        return find_impl(root, value);
    }

    void insert(info value) {
        if (!root) 
            root = new node{value, NULL, NULL};
        else
            insert_impl(root, value);
    }

    void preorder(vector<int>& order_list) {
        preorder_impl(root, order_list);
    }
    void postorder(vector<int>& order_list) {
        postorder_impl(root, order_list);
    }
private:
    node* find_impl(node* current, info value) {
        if (!current) {
            return NULL;
        }
        
        if (current->data.x == value.x) {
            return current;
        }

        if (value.x < current->data.x) {
            return find_impl(current->left, value);
        }

        return find_impl(current->right, value);
    }    

    void insert_impl(node* current, info value) {
        if (value.x < current->data.x) {
            if (!current->left) 
                current->left = new node {value, NULL, NULL};
            else
                insert_impl(current->left, value);
        }
        else {
            if (!current->right) 
                current->right = new node {value, NULL, NULL};
            else
                insert_impl(current->right, value);
        }
    }

    void preorder_impl(node* start, vector<int>& order_list) {
        if (!start)
            return ;
        
        order_list.push_back(start->data.n);
        preorder_impl(start->left, order_list);
        preorder_impl(start->right, order_list);
    }

    void postorder_impl(node* start, vector<int>& order_list) {
        if (!start)
            return ;
        
        postorder_impl(start->left, order_list);
        postorder_impl(start->right, order_list);
        order_list.push_back(start->data.n);
    }
};


bool cmp(info& u, info& v) {
    if(u.y == v.y) {
        return u.x < v.x;
    }
    return u.y > v.y;
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<vector<int>> answer;
    vector<info> infos;

    for (int i=0; i<nodeinfo.size(); i++) {
        infos.push_back(info {i+1, nodeinfo[i][0], nodeinfo[i][1]});
    }
    
    sort(infos.begin(), infos.end(), cmp);

    tree bst;
    for (int i=0; i<infos.size(); i++) {
        bst.insert(infos[i]);
    }

    answer.assign(2, vector<int>());
    bst.preorder(answer[0]);
    bst.postorder(answer[1]);
    
    return answer;
}