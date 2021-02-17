import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int r = scanner.nextInt();
        int c = scanner.nextInt();
        int k = scanner.nextInt();

        List<List<Integer> > array = new ArrayList<>();
        for (int i = 0; i < 3; i++) {
            List<Integer> row = new ArrayList<>();
            for (int j = 0; j < 3; j++) {
                int el = scanner.nextInt();
                row.add(el);
            }
            array.add(row);
        }

        Solution solution = new Solution();
        solution.solve(r,c,k, array);
    }
}

class Solution {

    public void solve(int r, int c, int k, List<List<Integer> > array) {

        int t=0;
        for (t = 0; t < 101; t++) {
            if((r-1<array.size()&&c-1<array.get(0).size()) && array.get(r-1).get(c-1) == k) break;
            if(array.size() >= array.get(0).size()) doRopeation(array);
            else doCoperation(array);
        }

        if(t==101) t=-1;
        System.out.print(t);
    }

    public void doRopeation(List<List<Integer> > array) {

        List<List<Integer> > newArray = new ArrayList<>();
        int maxLen = 0;

        for (int r = 0; r < array.size(); r++) {

            List<Integer> row = new ArrayList<>();
            List<KeyCounter> keyCounters = new ArrayList<>();
            Map<Integer, KeyCounter> counter = new TreeMap<>();
            for (int c = 0; c < array.get(r).size(); c++) {
                int el = array.get(r).get(c);
                if(el == 0) continue;
                if(!counter.containsKey(el)) {
                    counter.put(el, new KeyCounter(el, 1));
                    continue;
                }

                KeyCounter oldValue = counter.get(el);
                counter.replace(el, new KeyCounter(el, oldValue.counter+1));
            }

            for (Integer key :counter.keySet()) {
                keyCounters.add(counter.get(key));
            }

            Collections.sort(keyCounters);
            keyCounters.forEach(keyCounter -> {
                if(row.size()>=100) return;
                row.add(keyCounter.key);
                row.add(keyCounter.counter);
            });

            int len = row.size();
            if(len > maxLen) maxLen = len;
            newArray.add(row);
        }

        for (List<Integer> row :newArray) {
            int len = row.size();
            if (row.size() >= 100) return;
            if (len == maxLen) continue;
            for (int i = 0; i < maxLen - len; i++) {
                row.add(0);
            }
        }

        copyArray(array, newArray);
    }

    public void doCoperation(List<List<Integer> > array) {

        List<List<Integer> > newArray = new ArrayList<>();
        int maxLen = 0;

        int colLen = array.get(0).size();
        for (int c = 0; c < colLen; c++) {

            List<Integer> row = new ArrayList<>();
            List<KeyCounter> keyCounters = new ArrayList<>();
            Map<Integer, KeyCounter> counter = new TreeMap<>();
            int rowLen = array.size();
            for (List<Integer> integers : array) {
                int el = integers.get(c);
                if (el == 0) continue;
                if (!counter.containsKey(el)) {
                    counter.put(el, new KeyCounter(el, 1));
                    continue;
                }

                KeyCounter oldValue = counter.get(el);
                counter.replace(el, new KeyCounter(el, oldValue.counter + 1));
            }

            for (Integer key :counter.keySet()) {
                keyCounters.add(counter.get(key));
            }

            Collections.sort(keyCounters);
            keyCounters.forEach(keyCounter -> {
                if(row.size()>=100) return;
                row.add(keyCounter.key);
                row.add(keyCounter.counter);
            });

            int len = row.size();
            if(len > maxLen) maxLen = len;
            newArray.add(row);
        }

        for (List<Integer> row :newArray) {
            int len = row.size();
            if (row.size() >= 100) return;
            if (len == maxLen) continue;
            for (int i = 0; i < maxLen - len; i++) {
                row.add(0);
            }
        }

        List<List<Integer>> rotated = rotateArray(newArray);
        copyArray(array, rotated);
    }

    public List<List<Integer> > rotateArray(List<List<Integer> > array) {

        List<List<Integer> > changedArray = new ArrayList<>();
        for (int c = 0; c < array.get(0).size(); c++) {
            List<Integer> colToRow = new ArrayList<>();
            for (List<Integer> integers : array) {
                colToRow.add(integers.get(c));
            }
            changedArray.add(colToRow);
        }

        return changedArray;
    }

    public void copyArray(List<List<Integer> > dst, List<List<Integer> > src) {
        dst.clear();
        dst.addAll(src);
    }
}

class KeyCounter implements Comparable<KeyCounter> {
    int key;
    int counter;

    public KeyCounter(int key, int counter) {
        this.key = key;
        this.counter = counter;
    }

    @Override
    public int compareTo(KeyCounter o) {
        if(this.counter != o.counter) return this.counter - o.counter;
        return this.key - o.key;
    }
}