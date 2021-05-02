class Solution {
    int[][] map;
    int[][] rel;
    int[] rel_size;
    int[][] d;
    
    public int solution(int n, int m, int[][] edge_list, int k, int[] gps_log) {
        this.rel = new int[n][n];
        this.rel_size = new int[n];
        this.map = new int[n][n];
        this.d = new int[k][n];
        for(int x = 0; x < n; x++) {
            rel[x][rel_size[x] ++] = x;
            map[x][x] = 1;
        }
        for(int i = 0; i < m; i++){
            int x = edge_list[i][0] - 1;
            int y = edge_list[i][1] - 1;
            map[x][y] = map[y][x] = 1;
            rel[x][rel_size[x] ++] = y;
            rel[y][rel_size[y] ++] = x;
        }
        // initial value = 1
        d[0][0] = 1;
        for(int i = 0; i < k; i++) {
            gps_log[i] -=1;
        }
        for(int i = 1; i < k; i++) {
            for(int j = 0; j < n; j++) {
                int weight = gps_log[i] == j ? 0 : 1;
                int min = 9999;
                for(int idx = 0; idx < rel_size[j]; idx++) {
                    int from = rel[j][idx];
                    if(d[i - 1][from] == 0) continue;
                    if (min > d[i - 1][from] + weight)
                        min = d[i - 1][from] + weight;
                }
                if(min == 9999) continue;
                d[i][j] = min;
            }
        }
        if(d[k - 1][gps_log[k - 1]] == 0) return -1;
        return d[k - 1][gps_log[k - 1]] - 1;
    }
}