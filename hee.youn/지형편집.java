import java.util.HashMap;
import java.util.PriorityQueue;

public class Solution {
    HashMap<Integer, Integer> countMap = new HashMap<>();
    PriorityQueue<Integer> pq = new PriorityQueue<>();
    void update(int x){
        int prev = 0;
        if(countMap.containsKey(x)){
            prev = countMap.get(x);
        }else {
            pq.add(x);
        }
        countMap.put(x, prev + 1);
    }
    public long solution(int[][] land, int P, int Q) {
        int N = land.length;
        long sum = 0;
        long plan = N * N;
        int min = land[0][0];
        int max = land[0][0];
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                min = min > land[i][j] ? land[i][j] : min;
                max = max < land[i][j] ? land[i][j] : max;
                sum += land[i][j];
                update(land[i][j]);
            }
        }
        long cost = (sum - plan * min) * Q;
        long answer = cost;
        int acc = countMap.get(min);
        
        int prevHeight = pq.poll();
        while(!pq.isEmpty()){
            int i = pq.poll();
            cost += ((plan - acc) * -Q + acc * P) * (i - prevHeight);
            if(answer >= cost) {
                answer = cost;
            } else {
                break;
            }
            prevHeight = i;
            if(countMap.containsKey(i))
                acc += countMap.get(i);
        }        
        return answer;
    }
}