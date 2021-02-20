import java.util.regex.*;

class MyString {
    String data;
    public MyString(String data){
        this.data = data;
    }
    MyString replaceAll(String regex, String replacement) {
        data = data.replaceAll(regex, replacement);
        return this;
    }
    MyString toLowerCase() {
        data = data.toLowerCase();
        return this;
    }
    MyString isEmptyThenPuta() {
        data = data.length() == 0 ? "a" : data;
        return this;
    }
    MyString limit15() {
        data = data.substring(0, Math.min(15, data.length()));
        return this;
    }
    MyString expandLastElement(String format) {
        String lastElement = data.charAt(data.length() - 1) + "";
        data = String.format(format, data)
            .replaceAll(" ",lastElement);
        return this;
    }
    @Override
    public String toString() {
        return data;
    }
}
class Solution {
    public String solution(String new_id) {
        return (new MyString(new_id)).toLowerCase()
            .replaceAll("[^[[a-z]|[0-9]|[-]|[_]|[.]]]", "")
            .replaceAll("[.]{1,}", ".")
            .replaceAll("^[.]|[.]$", "")
            .isEmptyThenPuta()
            .limit15()
            .replaceAll("[.]$", "")
            .expandLastElement("%-3s").toString();
    }
}