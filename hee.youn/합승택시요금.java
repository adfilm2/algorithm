class Solution {
    int N;
    int[][] adj;
    
    int[][] distance;
    int INF = 20000000;
    
    void generateFloydWarshall() {
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                if(i == j) distance[i][j] = 0;
                else distance[i][j] = adj[i][j] == 0 ? INF : adj[i][j];
            }
        }
        for(int k = 0; k < N; k++){
            for(int i = 0; i < N; i++){
                for(int j = 0; j < N; j++){
                    if(distance[i][k] + distance[k][j] >= distance[i][j]) continue;
                    distance[i][j] = distance[i][k] + distance[k][j];
                }
            }
        }
    }
    
    public int solution(int n, int s, int a, int b, int[][] fares) {
        this.N = n;
        s -= 1;
        a -=1;
        b -= 1;
        this.adj = new int[n][n];
        this.distance = new int[n][n];
        for(int i = 0; i < fares.length; i++) { 
            int from = fares[i][0] - 1;
            int to = fares[i][1] - 1;
            int cost = fares[i][2];
            adj[from][to] = cost;
            adj[to][from] = cost;
        }
        generateFloydWarshall();
        int min = INF;
        for(int i = 0; i < n; i++){
            int predict = distance[s][i] + distance[i][a] + distance[i][b];
            if(min > predict) {
                min = predict;
            }          
        }
        return min;
    }
}