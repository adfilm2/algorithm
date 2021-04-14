class Solution {
    boolean[] check = new boolean[200001];
    public int solution(int[] nums) {
        int answer = 0;
        for(int num : nums) {
           if(check[num]) continue;
           answer ++;
           check[num] = true;
        }
        
        return Math.min(nums.length / 2, answer);
    }
}