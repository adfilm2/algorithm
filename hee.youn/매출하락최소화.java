import java.util.*;

class Solution {
    final static int NONE = 0;
    final static int SELECTED = 1;
    
    int min(int a, int b){
        return a > b ? b : a;
    }
    
    class Node {
        int idx;
        int value;
        ArrayList<Node> children;
        public Node(int idx, int value){
            this.idx = idx;
            this.value = value;
            children = new ArrayList<Node>();
        }
    }
    Node[] nodes;
    
    int[][] d;
    int search(Node cur) {
        if(cur.children.size() == 0) {
            d[cur.idx][NONE] = 0;
            d[cur.idx][SELECTED] = cur.value;
            return 0;
        }
        int total = 0;
        int minSelected = Integer.MAX_VALUE;
        int buf= 0;
        for(Node node : cur.children) {
            search(node);
            total += min(d[node.idx][NONE],d[node.idx][SELECTED]);
        }
        
        for(Node node : cur.children) {
            buf = min(d[node.idx][NONE],d[node.idx][SELECTED]);
            if(minSelected > d[node.idx][SELECTED] + total - buf) {   
                minSelected = d[node.idx][SELECTED] + total - buf;
            }
        }
            
        d[cur.idx][NONE] = minSelected;
        d[cur.idx][SELECTED] = total + cur.value;
        return min(d[cur.idx][NONE], d[cur.idx][SELECTED]);
    }
    public int solution(int[] sales, int[][] links) {
        d = new int[sales.length][2];
        this.nodes = new Node[sales.length];
        for(int i = 0; i < sales.length; i++) nodes[i] = new Node(i, sales[i]);
        for(int i = 0; i < links.length; i++) nodes[links[i][0]-1].children.add(nodes[links[i][1]-1]);
        int ret = search(nodes[0]);
        return ret;
    }
}
