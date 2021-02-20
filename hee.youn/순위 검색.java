import java.util.*;

class Solution {
    
    HashMap<String, ArrayList<Integer>> map = new HashMap<>();
    void update(String key, int score) {
        if(!map.containsKey(key)) {
            map.put(key, new ArrayList<Integer>());
        }
        map.get(key).add(score);
    }
    
    String[][] buf = new String[5][2];
    public int[] solution(String[] info, String[] query) {
        for(int i = 0; i < 5; i++){
            buf[i][0] = "-";
        }
        for(String _info : info) {
            String[] infos = _info.split(" ");
            int score = Integer.parseInt(infos[4]);
            
            for(int i = 0; i < 4; i++){
                buf[i][1] = infos[i];
            }
            String[] conditions = new String[4];
            for(int k1 = 0; k1 < 2; k1++) {
                conditions[0] = buf[0][k1];
                for(int k2 = 0; k2 < 2; k2 ++) {
                    conditions[1] = buf[1][k2];
                    for(int k3 = 0; k3 < 2; k3 ++) {
                        conditions[2] = buf[2][k3];
                        for(int k4 = 0; k4 < 2; k4 ++) {
                            conditions[3] = buf[3][k4];
                            String key = String.join(" and ", conditions);
                            update(key, score);
                        }
                    }   
                }
            }
        }
        for(String key : map.keySet()) {
            Collections.sort(map.get(key));
        }
        
        int[] answer = new int[query.length];
        for(int i = 0; i < query.length; i++) {
            String[] infos = query[i].split(" and | ");
            int score = Integer.parseInt(infos[4]);
            String condition = String.join(" and ", Arrays.copyOfRange(infos, 0, 4));
            if(!map.containsKey(condition)) {
                answer[i] = 0;
                continue;
            }
            ArrayList<Integer> list = map.get(condition);
            int left = 0;
            int right = list.size();
            while(left < right) {
                int mid = left + (right - left) / 2;
                if(list.get(mid) < score) {
                    left = mid + 1;
                } else {
                    right = mid;
                }
            }
            answer[i] = list.size() - right;
        }
        return answer;
    }
}