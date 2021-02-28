import java.util.*;
import java.util.stream.Collectors;

class Solution {
    private List<String> courseMenus = new ArrayList<>();
    private String[] orders;
    private Map<Integer, Map<String, Integer> > ordersOfCourse = new HashMap<>();

    private void makeCombination(int index, int len, String courseMenu, int depth, int select) {
        String order = orders[index];
        if(select > len) return ;
        if(order.length() == depth) {
            if(select<len) return ;
            if(!ordersOfCourse.get(len).containsKey(courseMenu)) {
                ordersOfCourse.get(len).put(courseMenu, 1);
                return ;
            }

            Integer num = ordersOfCourse.get(len).get(courseMenu);
            ordersOfCourse.get(len).replace(courseMenu, num+1);
            return ;
        }

        makeCombination(index, len, courseMenu, depth+1, select);
        makeCombination(index, len, courseMenu + order.charAt(depth), depth+1, select+1);
    }

    private void findMaxCourseMenu(int lenOfCourse) {

        ordersOfCourse.get(lenOfCourse)
                .entrySet().stream().max((o1, o2) -> o1.getValue().compareTo(o2.getValue()))
                .ifPresent(entry -> {
                    if(entry.getValue() < 2) return;
                    ordersOfCourse.get(lenOfCourse).entrySet().stream()
                            .filter(o -> o.getValue().equals(entry.getValue()))
                            .forEach(c -> { courseMenus.add(c.getKey()); });
                });
    }

    public String[] solution(String[] orders, int[] course) {
        String[] answer = {};
        this.orders = orders;

        for (int i = 0; i < this.orders.length; i++) {
            char[] chars = this.orders[i].toCharArray();
            Arrays.sort(chars);
            this.orders[i] = new String(chars);
        }

        for (int courseLen: course) {
            ordersOfCourse.put(courseLen, new HashMap<>());
        }

        for (int index = 0; index < orders.length; index++) {
            for (int courseLen: course) {
                if(courseLen > orders[index].length()) break;
                makeCombination(index, courseLen, "", 0, 0);
            }
        }

        for (int courseLen: course) {
            findMaxCourseMenu(courseLen);
        }

        answer = courseMenus.stream().sorted()
                .collect(Collectors.toList()).toArray(String[]::new);
        return answer;
    }
}