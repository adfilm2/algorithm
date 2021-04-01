                                                                                                                                                                                            import java.util.HashMap;
import java.util.ArrayList; 

class Solution {
    HashMap<String, Integer> dict = new HashMap<>();
    int key = 1;
    public int[] solution(String msg) {
        for(char c = 'A'; c <= 'Z'; c++) {
            dict.put(c+"", key);
            key++;
        }
        int h = 0;
        int len = msg.length();
        
        ArrayList<Integer> list = new ArrayList<>();
        while(h < len) {
            String word = "" + msg.charAt(h);
            h++;
            int recent = -1;
            while(dict.containsKey(word)) {
                recent = dict.get(word);
                if(h==len) break;
                word = word + msg.charAt(h);
                h++;
            }
            if(!dict.containsKey(word)) h--;
            list.add(recent);
            dict.put(word, key);
            key++;
        }
        int[] answer = new int[list.size()];
        for(int i = 0; i < answer.length; i++){
            answer[i] = list.get(i);
        }
        return answer;
    }
}
