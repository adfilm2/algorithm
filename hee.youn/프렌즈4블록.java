import java.util.*;

class Solution {
    
    char map[][];
    int m;
    int n;
    int clear(int x, int y){
        int ret = map[x][y] == 0 ? 0 : 1;
        map[x][y] = 0;
        return ret;
    }
    
    void init(String[] board) {
        map = new char[m][n];
        for(int i = 0; i < m; i++){
            for(int j = 0; j < n; j++){
                map[i][j] = board[i].charAt(j); 
            }
        }
    }
    int[][] shapeInfo = new int[][]{ {0, 1}, {1, 0}, {1, 1}};
    boolean isValid(int x, int y){
        return x >= 0 && x< m && y >= 0 && y< n;
    }
    ArrayList<Integer> hitList = new ArrayList<>();
    int simulate() {
        int ret = 0;
        hitList.clear();
        for(int x = 0; x < m; x++) {
            for(int y = 0; y < n; y++) {
                int k;
                for(k = 0; k < 3; k++) {
                    int nx = x + shapeInfo[k][0];   
                    int ny = y + shapeInfo[k][1];
                    if(!isValid(nx, ny)) break;
                    if(map[x][y] != map[nx][ny]) break;
                }
                if(k < 3) continue;
                hitList.add(x);
                hitList.add(y);
            }
        }
        for(int i = 0; i < hitList.size(); i += 2){
            int x = hitList.get(i);
            int y = hitList.get(i+1);
            ret += clear(x, y);
            for(int k = 0; k < 3; k++) {
                int nx = x + shapeInfo[k][0];   
                int ny = y + shapeInfo[k][1];
                ret += clear(nx, ny);
            }
        }
        return ret;
    }
    void shift() {
        char[][] buf = map.clone();
        for(int j = 0; j < n; j++) {
            int h = m - 1;
            for(int i = m - 1; i >= 0; i--){
                if(buf[i][j] == 0) continue;
                map[h][j] = buf[i][j];
                h--;
            }
            for(; h >= 0; h--){
                map[h][j] = 0;
            }
        }
    }
    public int solution(int m, int n, String[] board) {
        this.m = m;
        this.n = n;
        init(board);
        
        int answer = 0;
        while(true) {
            int clear = simulate();   
            if(clear == 0) break;
            shift();
            answer += clear;
        }
        return answer;
    }
}