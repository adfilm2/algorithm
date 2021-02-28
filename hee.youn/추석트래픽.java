import java.util.*;
import java.text.SimpleDateFormat; 
import java.util.Date;

class Solution {
    
    ArrayList<Record> list = new ArrayList<Record>();
    ArrayList<Long> possable = new ArrayList<Long>();
    HashMap<Long, Boolean> duplicatedCheck = new HashMap<>();
    public int solution(String[] lines) throws Exception {
        int answer = 0;
        for(String line : lines) {
            Record record = new Record(line);
            list.add(record);
            if(!duplicatedCheck.containsKey(record.startTime)) {
                duplicatedCheck.put(record.startTime, true);
                possable.add(record.startTime);   
            }
            if(!duplicatedCheck.containsKey(record.endTime)) {
                duplicatedCheck.put(record.endTime, true);
                possable.add(record.endTime);
            }
        }
        Collections.sort(list);
        Collections.sort(possable);
        
        int h = 0;
        for(int i = 0; i < possable.size(); i++) {
            long start = possable.get(i);
            long end = start + 999;
            while(h < list.size() && list.get(h).endTime < start) h++;
            int cnt = 0;
            for(int j = h; j < list.size(); j++) {
                Record cur = list.get(j);
                if(cur.startTime > end) break;
                if(cur.endTime < start) continue;
                cnt++;
            }
            if(answer < cnt) {
                answer = cnt;   
            }
        }
        return answer;
    }
}
class Record implements Comparable<Record>{
    long endTime;
    long startTime;
    public Record(String line) throws Exception {
        String[] arr = line.split(" ");
        
        SimpleDateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss.SSS");
        Date date = sdf.parse(arr[0]+" "+arr[1]);
        float duration = Float.parseFloat(arr[2].substring(0, arr[2].length() - 1));
        
        this.endTime = date.getTime();
        this.startTime = endTime - (int)(duration * 1000) + 1;
    }
    @Override
    public int compareTo(Record record){
        if(startTime == record.startTime){
            return (int)(endTime - record.endTime);
        }
        return (int)(startTime - record.startTime);
    }
    @Override
    public String toString(){
        return startTime + "->"+endTime;
    }
}