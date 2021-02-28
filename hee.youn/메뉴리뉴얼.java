import java.util.*;
import java.util.stream.*;

class Node implements Comparable<Node> {
    int count;
    String value;
    public Node(int c, String v){
        count = c;
        value = v;
    }
    
    @Override
    public int compareTo(Node n) {
        if(count == n.count) return value.compareTo(n.value);
        return - count + n.count;
    }
}
class Solution {
    HashMap<String, Integer> map = new HashMap<>();
    boolean[] target;
        
    void combination(String str, String key, int cur) {
        if(target[key.length()]) {
            int prev = map.containsKey(key) ? map.get(key) : 0;
            map.put(key, prev + 1);
        }
        for(int i = cur; i < str.length(); i++){
            combination(str, key + str.charAt(i), i + 1);
        }
    }
    void split(String str) {
        combination(str, "", 0);
    }
    
    public String[] solution(String[] orders, int[] course) {
        HashMap<Integer, ArrayList<Node>> map2 = new HashMap<>();
        target = new boolean[50];
        for(int i = 0; i < 20; i++) {
            target[i] = false;
        }
        for(int i = 0; i < course.length; i++) {
            target[course[i]] = true;
            map2.put(course[i], new ArrayList<>());
        }
        for(int i = 0; i < orders.length; i++) {
            String[] splited = orders[i].split("");
            Arrays.sort(splited);
            split(String.join("", splited));
        }
        ArrayList<Node> answer = new ArrayList<>();
        map.keySet()
            .stream()
            .filter(it -> map.get(it) >= 2)
            .map(it -> new Node(map.get(it), it))
            .forEach(it -> {
                map2.get(it.value.length()).add(it);
            });
        map2.keySet().forEach(key -> {
            ArrayList<Node> arr = map2.get(key);
            Collections.sort(arr);
            for(int i = 0; i < arr.size(); i++){
                if(arr.get(0).count != arr.get(i).count) break;
                answer.add(arr.get(i));
            }
        });
        return answer.stream()
            .map(it -> it.value)
            .sorted()
            .toArray(size -> new String[size]);
    }
}