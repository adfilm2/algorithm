import java.util.HashMap;

class Solution {
    class Node {
        char c;
        int value;
        Node[] next;
        public Node(char c, int value){
            this.c = c;
            this.value = value;
            this.next = new Node[27];
        }
        Node getNext(char c) {
            if(next[c-'a'] == null) {
                next[c-'a'] = new Node(c, 0);
            }
            return next[c-'a'];
        }
        @Override
        public String toString(){
            return c+"("+value+")";
        }
    }
    
    Node root;
    
    int job(String word) {
        int len = word.length();
        Node head = root;
        for(int i = 0; i < len; i++) {
            char c = word.charAt(i);
            head = head.getNext(c);
            if(head.value == 1) {
                return i + 1;
            }
        }
        return len;
    }
    
    public int solution(String[] words) {
        root = new Node(' ', words.length);
        for(String word : words) {
            int len = word.length();
            Node head = root;
            for(int i = 0; i < len; i++) {
                char c = word.charAt(i);
                head = head.getNext(c);
                head.value += 1;
            }
        }
        
        int answer = 0;
        for(String word : words) {
            answer += job(word);
        }
        return answer;
    }
}
