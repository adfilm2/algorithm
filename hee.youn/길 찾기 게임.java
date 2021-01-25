import java.util.Arrays;
import java.util.ArrayList;

class Solution {
    int N;
    Node[] nodes;
    Node root;
    void addNode(Node node){
        if(root == null){
            root = node;
            return;
        }
        Node head = root;
        while(head != null) {
            if(node.x < head.x) {
                if(head.left == null){
                    head.left = node;
                    break;
                }
                head = head.left;
            } else {
                if(head.right == null){
                    head.right = node;
                    break;
                }
                head = head.right;
            }
        }
    }
    
    ArrayList<Integer> pre, post;
    void recursive(Node head) {
        if(head == null) return;
        pre.add(head.v);
        recursive(head.left);
        recursive(head.right);
        post.add(head.v);
    }
    public int[][] solution(int[][] nodeinfo) {
        this.N = nodeinfo.length;
        this.root = null;
        nodes = new Node[N];
        for(int i = 0; i < N; i++){
            nodes[i] = new Node(i+1, nodeinfo[i][0], nodeinfo[i][1]);
            nodes[i].left = null;
            nodes[i].right = null;
        }
        Arrays.sort(nodes);
        for(int i = 0; i < N; i++){
            addNode(nodes[i]);
        }
        int[][] answer = new int[2][N];
        pre = new ArrayList<Integer>();
        post = new ArrayList<Integer>();
        recursive(root);
        for(int i = 0; i < N; i++){
            answer[0][i] = pre.get(i);
            answer[1][i] = post.get(i);
        }
        return answer;
    }
}

class Node implements Comparable<Node> {
    int v;
    int x;
    int y;
    Node left;
    Node right;
    public Node(int v, int x, int y){
        this.v = v;
        this.x = x;
        this.y = y;
    }
    @Override
    public int compareTo(Node node) {
         if (this.y > node.y) {
             return -1;
         } else if (this.y == node.y) {
             return this.x < node.x ? -1 : 1;
         } else {
             return 1;
         }
     }
    @Override
    public String toString(){
        return "Node("+v +","+x+","+y+")";
    }
}