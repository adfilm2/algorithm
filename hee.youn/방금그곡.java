import java.util.*;
import java.util.regex.*;

class Solution {
    class Music {
        final String title;
        final String info;
        final int diff;
        public Music(String string) {
            String[] musicinfos = string.split(",");
            int start = time2Int(musicinfos[0]);
            int end = time2Int(musicinfos[1]);
            this.diff = end - start;
            
            this.title = musicinfos[2];
            
            String info = musicinfos[3];
            int len = info.length();
            
            int h = 0;
            StringBuilder builder = new StringBuilder();
            for(int time = 0; time < diff; time++){
                builder.append(info.charAt(h));
                h = (h + 1) % len;
                if(info.charAt(h) == '#') {
                    builder.append(info.charAt(h));
                    h = (h + 1) % len;
                }
            }
            this.info = builder.toString();
        }
        private int time2Int(String time){
            String[] data = time.split(":");
            return Integer.parseInt(data[0]) * 60 + Integer.parseInt(data[1]);
        }
        @Override
        public String toString(){
            return "Music("+title+"/"+info+")";
        }
        
    }
    public String solution(String m, String[] musicinfos) {
        Music answer = null;
        String p = ".*"+m+"[^#].*";
        String p2 = ".*"+m+"$";
        for(int i = 0; i < musicinfos.length; i ++) {
            Music music = new Music(musicinfos[i]);
            System.out.println(music);
            if(!music.info.matches(p) && !music.info.matches(p2)) continue;
            if(answer == null) {
                answer = music;
                continue;
            }   
            if(answer.diff >= music.diff) continue;
            answer = music;   
        }
        if(answer == null) {
            return "(None)";
        }
        return answer.title;
    }
}
