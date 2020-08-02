// Code for Problem 7

import java.util.ArrayList;
import java.util.EmptyStackException;

public class MyStack<E> {

    // private field to track stack
    private ArrayList<E> stack;

    // constructor
    public MyStack() { stack = new ArrayList<>(); }

    public int size() { return stack.size(); }

    public void push_back(E e) { stack.add(e); }

    public E pop_back() throws EmptyStackException {
        // checking if stack is empty
        if (size() == 0)
            throw new EmptyStackException();
        // stack isn't empty -> remove and retrieve last element
        else return stack.remove(size() - 1);
    }

    public E peek() {
        // checking if stack is empty
        if (size() == 0)
            return null;
        // stack isn't empty -> return last element
        else return stack.get(size() - 1);
    }
}