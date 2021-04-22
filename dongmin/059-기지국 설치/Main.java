public class Solution {

    public int solution(int n, int[] stations, int w) {
        int answer = 0;
        int start = stations[0];
        int previousRight = start + w;

        int range = 2 * w + 1;
        if (start - w > 1) {
            answer = updateAnswer(answer, start - w - 1, range);
        }

        for (int i = 1; i < stations.length; i++) {
            int left = stations[i] - w;
            int right = stations[i] + w;
            if (left > previousRight + 1) {
                answer = updateAnswer(answer, left - previousRight - 1, range);
            }
            previousRight = right;
        }

        if (previousRight < n) {
            answer = updateAnswer(answer, n - previousRight, range);
        }

        return answer;
    }

    private int updateAnswer(int answer, int emptySpace, int range) {
        answer += emptySpace / range;
        if (emptySpace % range != 0) {
            answer++;
        }
        return answer;
    }
}