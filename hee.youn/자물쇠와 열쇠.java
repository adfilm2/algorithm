class Solution {
    int[][][] rotatedKey;
    int N, M;
    public boolean solution(int[][] key, int[][] lock) {
        boolean answer = false;
        this.M = key.length;
        this.N = lock.length;
        this.rotatedKey = new int[4][M][M];
        genRotateKey(key);
        // rotate Test
        /* {
        for(int rotateCnt = 0; rotateCnt < 4; rotateCnt ++ ) {
            System.out.println("지금 회전은 "+ rotateCnt);
            for(int i = 0; i < M; i++) {
                for(int j = 0; j < M; j++) {
                    System.out.print(rotatedKey[rotateCnt][i][j] +" ");
                }
                System.out.println();
            }
            System.out.println();
        }
        } */
        int holeCnt = 0;
        for(int i = 0; i < N; i++) {
            for(int j = 0; j < N; j++) {
                holeCnt += lock[i][j] == 0 ? 1 : 0;
            }
        }
        for(int i = 1 - M; i < N; i++) {
            for(int j = 1 - M; j < N; j++) {
                if(check(lock, i, j, holeCnt)) return true;
            }
        }
        return false;
    }
    
    void genRotateKey(int[][] origin){
        for(int r = 0; r < 4; r ++ ) {
            for(int i = 0; i < M; i++) {
                for(int j = 0; j < M; j++) {
                    int x = i;
                    int y = j;
                    for(int k = 0; k < r; k++){
                        int ret = rotate(x, y);   
                        x = ret / 1000;
                        y = ret % 1000;
                    }
                    rotatedKey[r][x][y] = origin[i][j];
                }
            }   
        }
    }
    
    int rotate(int x, int y){
        int _x, _y;
        _x = y;
        _y = M - 1 - x;
        return _x * 1000 + _y;
    }
    int checkSingle(int[][] lock, int x, int y, int ideal, int r) {
        int lockin = 0;
         for(int di = 0; di < M; di++) {
            for(int dj = 0; dj < M; dj++) {
                int i = x + di;
                int j = y + dj;
                if(i < 0 || j < 0 || i >= N || j >= N) continue;
                if(lock[i][j] + rotatedKey[r][di][dj] != 1) return -1;
                if(lock[i][j] == 0) lockin++;
            }
        }
        return lockin;
    }
    boolean check(int[][] lock, int x, int y, int ideal) {
        for(int r = 0; r < 4; r++) {
            int lockin = checkSingle(lock, x, y, ideal, r);
            if(lockin != ideal) continue;
            return true;
        }
        return false;
    }
}