import java.util.Arrays;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Objects;
import java.util.Queue;

class Solution {

  short[][] board;

  final static short[][] dir = new short[][]{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

  boolean isValid(short r, short c) {
    return r >= 0 && r < 4 && c >= 0 && c < 4;
  }

  class History {

    short r;
    short c;
    long mapBit;
    short count;
    short remain;
    boolean entered;
    short enterR;
    short enterC;
    History prev;

    public History(short r, short c, long mapBit, short remain) {
      this(r, c, mapBit, remain, (short) 0, false, (short) -1, (short) -1);
    }

    public History(short r, short c, long mapBit, short remain, short count, boolean entered,
        short enterR,
        short enterC) {
      this.r = r;
      this.c = c;
      this.mapBit = mapBit;
      this.remain = remain;
      this.count = count;
      this.entered = entered;
      this.enterR = enterR;
      this.enterC = enterC;
    }

    public History hit() {
      if (!entered) {
        return null;
      }
      if (enterR == r && enterC == c) {
        return null;
      }
      if (get(r, c) == 0) {
        return null;
      }
      if (get(enterR, enterC) != get(r, c)) {
        return null;
      }
      History ret = copy();
      ret.remain -= 1;
      ret.set(r, c, (short) 0);
      ret.set(enterR, enterC, (short) 0);
      ret.count += 1;
      ret.entered = false;
      ret.enterR = -1;
      ret.enterC = -1;
      return ret;
    }

    short get(short r, short c) {
      long shifted = mapBit >> ((r * 4 + c) * 3);
      short ret = (short) (shifted & 7);
      return ret;
    }

    void set(short r, short c, short v) {
      long filter = ((long) 1 << 48) | (long) 7 << ((r * 4 + c) * 3);
      mapBit &= ~filter;
      long shifted = ((long) 1 << 48) | (long) v << ((r * 4 + c) * 3);
      mapBit = mapBit | shifted;
    }

    public History enter() {
      if (entered) {
        return null;
      }
      if (get(r, c) == 0) {
        return null;
      }
      History ret = copy();
      ret.entered = true;
      ret.enterR = r;
      ret.enterC = c;
      ret.count += 1;
      return ret;
    }

    public History move(short d) {
      short nr = (short) (r + dir[d][0]);
      short nc = (short) (c + dir[d][1]);
      if (!isValid(nr, nc)) {
        return null;
      }
      History ret = copy();
      ret.r = nr;
      ret.c = nc;
      ret.count += 1;
      return ret;
    }

    public History ctrlMove(short d) {
      short nr = (short) (r + dir[d][0]);
      short nc = (short) (c + dir[d][1]);
      short moved = 1;
      while (isValid(nr, nc) && get(nr, nc) == 0) {
        nr += dir[d][0];
        nc += dir[d][1];
        moved++;
      }
      if (!isValid(nr, nc)) {
        nr -= dir[d][0];
        nc -= dir[d][1];
        moved -= 1;
      }
      if (moved < 2) {
        return null;
      }
      History ret = copy();
      ret.r = nr;
      ret.c = nc;
      ret.count += 1;
      return ret;
    }

    public History copy() {
      History ret = new History(r, c, mapBit, remain, count, entered, enterR, enterC);
      ret.prev = this;
      return ret;
    }

    @Override
    public String toString() {
      String ret = "History{" +
          "r=" + r +
          ", c=" + c +
          ", count=" + count +
          ", remain=" + remain +
          ", entered=" + entered +
          ", enterR=" + enterR +
          ", enterC=" + enterC + "\n";
      for (short i = 0; i < 4; i++) {
        for (short j = 0; j < 4; j++) {
          if (i == r && j == c) {
            ret += "C ";
          } else {
            ret += get(i, j) + " ";
          }
        }
        ret += "\n";
      }
      ret += "}";

      return ret;
    }

    @Override
    public boolean equals(Object o) {
      if (this == o) {
        return true;
      }
      if (o == null || getClass() != o.getClass()) {
        return false;
      }
      History history = (History) o;
      return mapBit == history.mapBit &&
          enterR == history.enterR &&
          enterC == history.enterC &&
          r == history.r &&
          c == history.c;
    }

    @Override
    public int hashCode() {
      return Long.hashCode(mapBit);
    }
  }

  Queue<History> queue = new LinkedList<>();
  HashMap<History, Boolean> visit = new HashMap<>();

  void work(History history) {
    if (history != null && !visit.containsKey(history)) {
      if (history.count > 16) {
        return;
      }
      queue.offer(history);
      visit.put(history, true);
    }
  }

  int bfs(short startR, short startC, short[][] board, short total) {
    short min = 17;
    visit.clear();

    long mapBit = 1;
    for (short i = 3; i >= 0; i--) {
      for (short j = 3; j >= 0; j--) {
        mapBit = (mapBit << 3) + board[i][j];
      }
    }

    History start = new History(startR, startC, mapBit, total);
    queue.add(start);
    visit.put(start, true);
    while (!queue.isEmpty()) {
      History cur = queue.poll();
      if (cur.remain == 0) {
        History head = cur;
        while (head.prev != null) {
          System.out.println(head);
          head = head.prev;
        }
        return cur.count;
      }
      work(cur.hit());
      work(cur.enter());
      for (short d = 0; d < 4; d++) {
        work(cur.ctrlMove(d));
        work(cur.move(d));
      }
    }
    return min;
  }

  public int solution(int[][] board, int r, int c) {
    short[] cnt = new short[7];
    for (short i = 0; i < 7; i++) {
      cnt[i] = 0;
    }
    this.board = new short[4][4];
    for (short i = 0; i < 4; i++) {
      for (short j = 0; j < 4; j++) {
        this.board[i][j] = (short) board[i][j];
        cnt[board[i][j]] = 1;
      }
    }
    short total = 0;
    for (short i = 1; i < 7; i++) {
      total += cnt[i];
    }
    return bfs((short) r, (short) c, this.board, total);
  }
}

