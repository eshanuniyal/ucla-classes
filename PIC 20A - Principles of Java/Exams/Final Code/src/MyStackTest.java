// Code for testing solution to Problem 7

public class MyStackTest {
    public static void stackTest (String [] args) {
        MyStack<Integer> stack = new MyStack<>();
        stack.push_back(1);
        stack.push_back(2);
        stack.push_back(3);
        System.out.println(stack.pop_back());   // output 3
        System.out.println(stack.peek());   // output 2
        System.out.println(stack.peek());   // output 2
        System.out.println(stack.peek());   // output 2
        System.out.println(stack.pop_back());   // output 2
        System.out.println(stack.pop_back());   // output 1
        stack.push_back(1);
        stack.push_back(2);
        stack.push_back(3);
        System.out.println(stack.pop_back());   // output 3
        stack.push_back(4);
        stack.push_back(5);
        System.out.println(stack.pop_back());   // output 5
        System.out.println(stack.pop_back());   // output 4
        System.out.println(stack.pop_back());   // output 2
        System.out.println(stack.pop_back());   // output 1
        System.out.println(stack.pop_back());   // throws EmptyStackException
    }
}