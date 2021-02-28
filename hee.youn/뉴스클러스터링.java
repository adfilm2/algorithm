import java.util.*;
class Solution {
    HashMap<String, Integer> map1 = new HashMap<>();
    HashMap<String, Integer> map2 = new HashMap<>();
    boolean isAlpabet(char c){
        return c >= 'a' && c <= 'z';
    }
    void stringToMap(HashMap<String, Integer> map, String str) {
        for(int i = 0; i < str.length() - 1; i++){
            String key = "" + str.charAt(i) + str.charAt(i + 1);
            key = key.toLowerCase();
            if(isAlpabet(key.charAt(0)) && isAlpabet(key.charAt(1))) {
                int prev = 0;
                if(map.containsKey(key)) {
                    prev = map.get(key);
                }
                map.put(key, prev + 1);
            }
        }
    }
    
    public int solution(String str1, String str2) {
        stringToMap(map1, str1);
        stringToMap(map2, str2);
        int answer = 0;
        
        int intersection = 0;
        int total = 0;
        Iterator iterator1 = map1.keySet().iterator();
        while(iterator1.hasNext()) {
            String key = (String)iterator1.next();
            int v1 = map1.get(key);
            if(map2.containsKey(key)){
                int v2 = map2.get(key);
                total += v2;
                intersection += Math.min(v1, v2);
                map2.remove(key);
            }
            total += v1;
        }
        Iterator iterator2 = map2.keySet().iterator();
        while(iterator2.hasNext()) {
            String key = (String)iterator2.next();
            int v2 = map2.get(key);
            total += v2;
        }
        if(total == 0) return 65536;
        int union = total - intersection;
        return intersection * 65536 / union;
    }
}