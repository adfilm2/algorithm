import java.util.*;

/*
 * JAVA 8 API
 * Collections.binarySearch
 * If the list contains multiple elements equal to the specified object, there is no guarantee which one will be found.
 *
 * -> 이분탐색 구현이 낫다.
 */
class Solution {
    private Map<String, List<Integer> > scores = new HashMap<>();

    void dfs(String[] splited, String str, int depth) {

        if(splited.length-1 == depth) {
            int score = Integer.parseInt(splited[splited.length-1]);
            if(!scores.containsKey(str)) {
                ArrayList<Integer> value = new ArrayList<>();
                value.add(score);
                scores.put(str, value);
                return ;
            }

            scores.get(str).add(score);
            return ;
        }

        dfs(splited, str+splited[depth], depth+1);
        dfs(splited, str+"-", depth+1);
    }

    public int[] solution(String[] info, String[] query) {
        List<Integer> answer = new ArrayList<>();

        for (String unitInfo : info) {
            String[] splited = unitInfo.split(" ");
            dfs(splited, "", 0);
        }

        scores.values().forEach(Collections::sort);
        scores.forEach((key1, value) -> System.out.println(key1 + " " + value));

        for (String q: query) {
            String[] splited = q.split(" and | ");
            String key = String.join("",
                    Arrays.stream(splited)
                    .filter(s -> !Character.isDigit(s.charAt(0)))
                    .toArray(String[]::new));
            if(!scores.containsKey(key)) {
                answer.add(0);
                continue;
            }

            int score = Integer.parseInt(splited[splited.length-1]);
            List<Integer> list = scores.get(key);
            int left = 0, right = list.size();
            int mid = 0;

            while (right > left) {
                mid = (left + right) / 2;
                if (list.get(mid) < score) {
                    left = mid + 1;
                } else {
                    right = mid;
                }
            }

            answer.add(scores.get(key).size() - right);
        }

        return answer.stream().mapToInt(it -> it).toArray();
    }
}