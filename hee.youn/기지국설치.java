class Solution {
    public int solution(int n, int[] stations, int w) {
        int[] st = stations;
        int width = w * 2 + 1;
        
        int start = 1;
        int count = 0;
        for(int i = 0; i < st.length; i++){
            int left = st[i] - w;
            int right = st[i] + w;
            while(i + 1 < st.length && st[i + 1] - w <= right + 1) {
                i++;
                right = st[i] + w;
            }
            if(start < left) {
                count += (left - start + width - 1) / width; 
                start = right + 1;
            }
            if(left <= start && start <= right)
                start = right + 1;
        }
        if(start <= n) {
            count += (n + 1 - start + width - 1) / width; 
        }
        return count;
    }
}