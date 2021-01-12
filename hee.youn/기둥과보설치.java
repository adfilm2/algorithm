import java.util.LinkedList;
import java.util.Comparator;
import java.util.Collections;
import java.util.Iterator;

class Solution {
    int n;
    LinkedList list = new LinkedList<Obj>();
    Obj[][][] map;
    
    int dir[][][] = new int[][][] {
        {
            {-1, 0}, {0, 0}, {-1, 1}, {0, 1}
        },
        {
            {-1, 0}, {0, 0}, {1, 0},
        }
    };
    public int[][] solution(int n, int[][] build_frame) {        
        n += 1;
        map = new Obj[2][n][n];
        this.n = n;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                map[0][i][j] = null;
                map[1][i][j] = null;
            }
        }
        
        for(int i = 0; i < build_frame.length; i++) {
            int x = build_frame[i][0];
            int y = build_frame[i][1];
            int a = build_frame[i][2];
            int b = build_frame[i][3];
            if(b == 1) {
                if(map[a][x][y] != null) continue;
             //   System.out.println("ADD " + x +", " + y
             //                      +" "+ (a == Type.BEAM.ordinal() ? "Beam" : "Pillar"));
                Obj obj = new Obj(x, y, a);
                if(obj.check(map)) {
               //     System.out.println("success");
                    list.add(obj);
                    map[a][x][y] = obj;
                } else {
               //     System.out.println("fail");
                    map[a][x][y] = null;   
                }
            }
            else {
              //  System.out.println("DEL " + x +", " + y 
              //                     +" "+ (a == Type.BEAM.ordinal() ? "Beam" : "Pillar"));
                if(map[a][x][y] == null) continue;
                Obj temp = map[a][x][y];
                map[a][x][y] = null;
                boolean res = true;
                /* 그냥 다 테스트
                Collections.sort(list);
                Iterator<Obj> it = list.iterator();
                while(it.hasNext()) {
                    Obj item = it.next();
                    res &= item.check(map);
                } */
                for(int t = 0; t < 2; t++){
                    for(int d = 0; d< dir[a].length; d++){
                        int _x = x + dir[a][d][0];
                        int _y = y + dir[a][d][1];
                        if(_x < 0 || _y < 0 || _x >= n || _y >= n) continue;
                        if(map[t][_x][_y] == null) continue;
                        res &= map[t][_x][_y].check(map);
                        if(res == false) break;
                    }
                    if(res == false) break;
                }
                if(res == false) {
                  //  System.out.println("fail");
                    map[a][x][y] = temp;
                } else {
                 //   System.out.println("success");
                    list.remove(temp);
                }
            }
        }
        Collections.sort(list);
        Iterator<Obj> it = list.iterator();
        int cnt = 0;
        
        int[][] answer = new int[list.size()][3];
        while(it.hasNext()) {
            Obj item = it.next();
            answer[cnt][0] = item.x;
            answer[cnt][1] = item.y;
            answer[cnt][2] = item.type.ordinal();
            cnt++;
        }
        return answer;
    }
}


enum Type {
    PILLAR, BEAM
}
class Obj implements Comparable<Obj> {
    int x;
    int y;
    Type type;
    
    public Obj(int x, int y, int a){
        this.x = x;
        this.y = y;
        type = a == Type.BEAM.ordinal() ? Type.BEAM : Type.PILLAR;
    }
    
    @Override
    public int compareTo(Obj o2) {
        if (x == o2.x) {
            if (y == o2.y) {
                return  type.ordinal() > o2.type.ordinal() ? 1 : -1;
            }
            return y > o2.y ? 1 : -1;
        }
        return x > o2.x ? 1 : -1;
    }
    boolean check(Obj[][][] map) {
        int n = map[0].length;
        // 기둥은 
        if(type == Type.PILLAR) {
            // 바닥 위에 있거나 
            if(y == 0) return true;
            // 보의 한쪽 끝 부분 위에 있거나
            if(map[Type.BEAM.ordinal()][x][y] != null 
               || (x - 1 >= 0 && map[Type.BEAM.ordinal()][x - 1][y] != null)) return true;
            // 또는 다른 기둥 위에 있어야 합니다.
            if(map[Type.PILLAR.ordinal()][x][y - 1] != null) return true;
            return false;
        }
        else if(type == Type.BEAM) {
            // 보는 한쪽 끝 부분이 기둥 위에 있거나, 
            if(map[Type.PILLAR.ordinal()][x][y - 1] != null
               || (x + 1 < n && map[Type.PILLAR.ordinal()][x + 1][y - 1] != null)) return true;
            // 또는 양쪽 끝 부분이 다른 보와 동시에 연결되어 있어야 합니다.
            if((x - 1 >= 0 && map[Type.BEAM.ordinal()][x - 1][y] != null)
               && (x + 1 < n && map[Type.BEAM.ordinal()][x + 1][y] != null)) return true;
            return false;
        }
        System.out.println("??");
        return false;
    }
}