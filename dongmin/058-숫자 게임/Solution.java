import java.util.Arrays;

public class Solution {
    public int solution(int[] A, int[] B) {
        int score = 0;

        Arrays.sort(A);
        Arrays.sort(B);

        int j = 0;
        for (int i = 0; i < A.length && j < B.length; ) {
            if (A[i] < B[j]) {
                i++;
                score++;
            }
            j++;
        }

        return score;
    }
}