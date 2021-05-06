import java.util.*;

class Solution {
    
    final static short X = 0;
    final static short Y = 1;
    final static short FIRST = 0;
    final static short SECOND = 1;
    final static char EMPTY = '.';
    final static char BLOCKED = 26;
    
    int[] blocks = new int[27];
    char[] history = new char[27];
    long[][] preconditions = new long[27][2];
    int block_size;
    long isDeleted;
    
    int[][][] positions = new int[27][2][2];
    char[][] map;
      
    long moveX(int x, int y, int ex, int ey) {
        if(x == ex) return 0;

        long need = 0;
        if(map[x][y] != EMPTY) {
            need |= (1 << map[x][y]);
        }
        do{
            x += 1;
            if(map[x][y] != EMPTY) {
                need |= (1 << map[x][y]);
            }
        }while(x < ex);
        return need;
    }
    
    long moveY(int x, int y, int ex, int ey) {
        if(y == ey) return 0;
        long need = 0;
        int dirY = y < ey ? 1 : -1;
        if(map[x][y] != EMPTY) { 
            need |= (1 << map[x][y]);
        }
        do{
            y += dirY;
            if(map[x][y] != EMPTY) {
                need |= (1 << map[x][y]);
            }
        }while(y != ey);
        return need;
    }
    public String solution(int m, int n, String[] board) {
        block_size = 0;
        this.map = new char[m][n];
        for(int i = 0; i < 26; i++) positions[i][FIRST][X] = -1;
        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                map[i][j] = board[i].charAt(j);
                if(map[i][j] == '*') {
                    map[i][j] = BLOCKED;
                    continue;
                }
                if(map[i][j] == EMPTY) continue;
                map[i][j] -= 'A';
                int code = map[i][j];
                if(positions[code][FIRST][X] == -1) {
                    blocks[block_size++] = map[i][j];
                    positions[code][FIRST][X] = i;
                    positions[code][FIRST][Y] = j;
                } else {
                    positions[code][SECOND][X] = i;
                    positions[code][SECOND][Y] = j;
                }
            }
        }
        Arrays.sort(blocks, 0, block_size);
        this.isDeleted = 0;
        for(int i = 0; i < block_size; i++) {
            int code = blocks[i];
            int sx = positions[code][FIRST][X];
            int sy = positions[code][FIRST][Y];
            int ex = positions[code][SECOND][X];
            int ey = positions[code][SECOND][Y];
            
            preconditions[code][0] = moveX(sx, sy, ex, ey) | moveY(ex, sy, ex, ey);
            preconditions[code][1] = moveY(sx, sy, ex, ey) | moveX(sx, ey, ex, ey);
            preconditions[code][0] &= ~(1 << code);
            preconditions[code][1] &= ~(1 << code);
            /*
            System.out.println(""+ ((char)('A' + code)) + " need :");
            for(int cc = 0; cc <= 26; cc++) {
                long bit = 1 << cc;
                if((bit & preconditions[i][0]) == 0) continue;
                if(cc == 26) System.out.print(" *");
                else System.out.print(" " + (char)('A'+cc));
            }
            System.out.println();
            for(int cc = 0; cc <= 26; cc++) {
                long bit = 1 << cc;
                if((bit & preconditions[i][1]) == 0) continue;
                if(cc == 26) System.out.print(" *");
                else System.out.print(" " + (char)('A'+cc));
            }
            System.out.println();
            */
        }
        
        StringBuilder builder = new StringBuilder();
        
        int len = block_size;
        for(int level = 0; level < len; level++) {
            boolean hit = false;
            for(int i = 0; i < block_size; i++) {
                int code = blocks[i];
                long bit = 1 << code;
                if((isDeleted & bit) > 0) continue;
                if((preconditions[code][0] & (~isDeleted)) > 0
                   && (preconditions[code][1] & (~isDeleted)) > 0) continue;
                isDeleted |= bit;
                builder.append((char)('A' + code));
                --block_size;
                for(int j = i; j < block_size; j++) {
                    blocks[j] = blocks[j + 1];
                }
                hit = true;
                break;
            }
            if(!hit) {
                return "IMPOSSIBLE";
            }
        }
        return builder.toString();
    }
}
