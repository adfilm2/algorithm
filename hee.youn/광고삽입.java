import java.util.*;

class Solution {

  final static int MAX_TIME = 360000;

  int time2Int(String time) {
    String[] arr = time.split(":");
    return ((Integer.parseInt(arr[0]) * 60) + Integer.parseInt(arr[1])) * 60 + Integer
        .parseInt(arr[2]);
  }

  String int2Time(int time) {
    int second = time % 60;
    time /= 60;
    int min = time % 60;
    time /= 60;
    int hour = time;
    return String.format("%02d:%02d:%02d", hour, min, second);
  }

  int[] viewers = new int[MAX_TIME];
  long[] total = new long[MAX_TIME];
    
  public String solution(String play_time, String adv_time, String[] logs) {
    int finishTime = time2Int(play_time);
    int period = time2Int(adv_time);
    for (int t = 0; t < MAX_TIME; t++) {
        viewers[t] = 0;
        total[t] = 0;
    }
    for (String log : logs) {
      String[] times = log.split("-");
      int start = time2Int(times[0]);
      int end = time2Int(times[1]);
      viewers[start] += 1;
      viewers[end] -= 1;
    }
    viewers[0] = 0;
    total[0] = 0;
    for (int t = 1; t < MAX_TIME; t++) {
      viewers[t] += viewers[t - 1];
      total[t] += total[t - 1] + viewers[t - 1];
    }
    long max = 0;
    int answer = 0;
    for (int t = 0; t <= finishTime - period; t++) {
      long sum = total[t + period] - total[t];
      if (sum > max) {
        max = sum;
        answer = t;
      }
    }
    return int2Time(answer);
  }
}
