import java.util.*;

class Solution {
    int N;
    int[][] board;
    
    int top[];
    
    int[][][] typeData = new int[][][]{{{0, 0}, {0, 1}, {0, 2}, {1, 2}},
                                   {{0, 0}, {0, 1}, {1, 0}, {2, 0}},
                                   {{0, 0}, {1, 0}, {1, 1}, {1, 2}},
                                   {{0, 0}, {1, 0}, {2, 0}, {2, -1}},
                                   
                                   {{0, 0}, {0, 1}, {0, 2}, {1, 0}},
                                   {{0, 0}, {1, 0}, {2, 0}, {2, 1}},
                                   {{0, 0}, {1, 0}, {1, -1}, {1, -2}},
                                   {{0, 0}, {0, 1}, {1, 1}, {2, 1}},
                                   
                                   {{0, 0}, {1, -1}, {1, 0}, {1, 1}},
                                   {{0, 0}, {1, 0}, {1, 1}, {2, 0}},
                                   {{0, 0}, {0, 1}, {0, 2}, {1, 1}},
                                   {{0, 0}, {1, -1}, {1, 0}, {2, 0}}};
    
    int[][][] typeNeed = new int[][][]{ {{1, 0}, {1,1}},
                                       {{1, 1}, {2, 1}},
                                       {{0, 1}, {0, 2}},
                                       {{0, -1}, {1, -1}},
                                       
                                       {{1, 1}, {1, 2}},
                                       {{0, 1}, {1, 1}},
                                       {{0, -2}, {0, -1}},
                                       {{1, 0}, {2, 0}},
                                       
                                       {{0, -1}, {0, 1}},
                                       {{0, 1}, {2, 1}},
                                       {{1, 0}, {1, 2}},
                                       {{0,0}, {2, 1}}};
    
    boolean possible[] = new boolean[]{false, false, true, true,
                                       false, true, true, false,
                                       true, false, false, false};
    
    ArrayList<Block> blocks = new ArrayList<>();
    
    boolean outRange(int nr, int nc) {
        return nr < 0 || nc < 0 || nr >= N || nc >= N;
    }
    
    int getTop(int c) {
        while(top[c] < N && board[top[c]][c] == 0) top[c] ++;
        return top[c];
    }
    
    int getType(int r, int c) {
        int pivot = board[r][c];
        if(pivot == 0) return -1;
        for(int type = 0; type < 12; type++) {
            int k;
            for(k = 0; k < 4; k++) {
                int nr = r + typeData[type][k][0];
                int nc = c + typeData[type][k][1];
                if(outRange(nr, nc)) break;
                if(pivot != board[nr][nc]) break;
            }
            if(k < 4) continue;
            return type;
        }
        return -1;
    }
    
    boolean isPossible(Block block) {
        int type = block.type;
        int r = block.r;
        int c = block.c;
        for(int k = 0; k < 2; k++) {
            int nr = r + typeNeed[type][k][0];
            int nc = c + typeNeed[type][k][1];
            if(outRange(nr, nc)) return false;
            if(0 != board[nr][nc]) return false;
            int head = getTop(nc);
            if(head == N) return false;
            if(board[head][nc] != board[r][c]) return false;
        }
        return true;
    }
    
    void remove(Block block) {
        int type = block.type;
        int r = block.r;
        int c = block.c;
        board[r][c] = 0;
        for(int k = 0; k < 4; k++) {
            int nr = r + typeData[type][k][0];
            int nc = c + typeData[type][k][1];
            board[nr][nc] = 0;
        }   
    }
    
    public int solution(int[][] board) {
        this.N = board.length;
        this.board = board;
        top = new int[N];
        for(int c = 0; c < N; c++){
            top[c] = 0;
            getTop(c);
        }
        
        for(int r = 0; r < N; r++) {
            for(int c = 0; c < N; c++) {
                int type = getType(r, c);
                if(type == -1) continue;
                if(!possible[type]) continue;  
                blocks.add(new Block(board[r][c], r, c, type));
            }
        }
        
        int answer = 0;
        boolean hit = true;
        while(hit) {
            hit = false;
            for(int i = 0; i < blocks.size(); i++) {
                Block block = blocks.get(i);
                if(!isPossible(block)) continue;                    
                answer ++;
                hit = true;
                remove(block);
                blocks.remove(i);
                break;
            }
        }
        return answer;
    }
}
class Block {
    int no;
    int r;
    int c;
    int type;
    public Block(int no, int r, int c, int type) {
        this.no = no;
        this.r = r;
        this.c = c;
        this.type = type;
    }
}