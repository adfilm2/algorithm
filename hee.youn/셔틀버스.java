import java.util.*;

class Solution {
    
    int bus = 9 * 60;
    int[] arrive;
    public String solution(int n, int t, int m, String[] timetable) {
        String answer = "";
        arrive = new int[timetable.length];
        for(int i = 0; i < timetable.length; i++){
            String[] arr = timetable[i].split(":");
            arrive[i] = 60 * Integer.parseInt(arr[0]) + Integer.parseInt(arr[1]);
        }
        Arrays.sort(arrive);
        int able = 0;
        int h = 0;
        for(int i = 1; i <= n; i++) {
            int passengers = 0;
            for(; h < arrive.length && passengers < m; h++){
                if(arrive[h] > bus) break;
                passengers++;
            }
            if(passengers == m) {
                able = arrive[h - 1] - 1;
            } else {
                able = bus;
            }
            bus += t;
        }
        
        int hour = able / 60 ;
        String hourStr = hour < 10 ? ("0"+hour) : (""+hour);
        int minute = able % 60;
        String minuteStr = minute < 10 ? ("0"+minute) : (""+minute);
        return hourStr+":"+minuteStr;
    }
}