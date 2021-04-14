import java.util.*;

class Solution {
    
    int N;
    int[] numbers;
    char[] operators;
    
    final static int MAX = 0;
    final static int MIN = 1;
    
    int calculate(char c, int a, int b) {
        return c == '+' ? a + b : a - b;
    }
    
    int[][][] dynamic;
    
    int max, min;
    void update(int value){
        if(max < value) {
            max = value;
        }
        if(min > value) {
            min = value;
        }
    }
    public int solution(String arr[]) {
        
        int size = arr.length;
        N = size / 2;
        numbers = new int[N + 1];
        operators = new char[N];
        numbers[0] = Integer.parseInt(arr[0]);
        
        int sum = numbers[0];
        for(int i = 1; i < arr.length; i+=2) {
            operators[i / 2] = arr[i].charAt(0);
            numbers[1 + i/2] = Integer.parseInt(arr[i + 1]);
            sum = calculate(operators[i/2], sum, numbers[1 + i/2]);
        }
        dynamic = new int[2][N][N];
        for(int i = 0; i < N; i++) {
            dynamic[MAX][i][i] = dynamic[MIN][i][i] = calculate(operators[i], numbers[i], numbers[i + 1]);
        }
        
        for(int diff = 1; diff < N; diff++){
            for(int i = 0; i < N - diff; i++) {
                int j = i + diff;
                
                max = min = calculate(operators[i], numbers[i], dynamic[MAX][i + 1][j]);
                update(calculate(operators[i], numbers[i], dynamic[MIN][i + 1][j]));
                for(int k = i + 1; k <= j - 1; k++) {
                    for(int kk = 0; kk < 4; kk++){
                        int result = calculate(operators[k], dynamic[kk / 2][i][k - 1], dynamic[kk % 2][k + 1][j]);   
                        update(result);
                    }
                }
                update(calculate(operators[j], dynamic[MAX][i][j - 1], numbers[j + 1]));
                update(calculate(operators[j], dynamic[MIN][i][j - 1], numbers[j + 1]));
                
                dynamic[MAX][i][j] = max;
                dynamic[MIN][i][j] = min;
            }
        }
        
        return dynamic[MAX][0][N-1];
    }
}
