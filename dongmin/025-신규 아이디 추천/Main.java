import java.util.Locale;

/**
 * String의 lastIndexOf는 존재하지 않으면 -1을 반환한다.
 * 따라서 비어있는 문자열에서 어떤 문자를 찾고 (문자열길이-1) 과 같다는 조건문을 적으면
 * true로 판단한다.
 *
 * [정규표현식]
 * 정규표현식에서 . 자체는 임의의 한 문자를 의미하므로
 * 실제 점 패턴을 찾고자 하면 \\.을 써야 한다.
 * String의 교체 메소드로 replaceFirst와 replaceAll만 정규표현식을 사용한다.
 * */

class Solution {
    public String solution(String new_id) {
        StringBuilder answer = new StringBuilder(new_id);
        answer = new StringBuilder(answer.toString().toLowerCase(Locale.ROOT));
        StringBuilder buffer = new StringBuilder();

        for (char ch :
                answer.toString().toCharArray()) {
            if(Character.isAlphabetic(ch) || Character.isDigit(ch) || ch == '-' || ch == '_' || ch == '.') {
                buffer.append(ch);
            }
        }

        answer = new StringBuilder(buffer.toString());
        answer = new StringBuilder(answer.toString().replaceAll("\\.\\.+", "."));
        if(answer.toString().indexOf('.') == 0) {
            answer = new StringBuilder(answer.toString().replaceFirst(".", ""));
        }

        int lastIndex = answer.toString().lastIndexOf('.');
        if(answer.length() > 0 && lastIndex == answer.length()-1) {
            answer = new StringBuilder(answer.substring(0, answer.length() - 1));
        }

        if(answer.toString().length() == 0) answer.append("a");
        if(answer.length() >= 16) {
            answer = new StringBuilder(answer.substring(0, 15));
        }

        if(answer.toString().lastIndexOf('.') == answer.length()-1) {
            answer = new StringBuilder(answer.substring(0, answer.length() - 1));
        }

        int len = answer.length();
        if(len <= 2) {
            while(answer.length() != 3)
                answer.append(answer.charAt(len - 1));
        }

        return answer.toString();
    }
}