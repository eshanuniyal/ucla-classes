// Problem 9

import java.util.ArrayList;

public class SortingTest {
    public static void main(String[] args) {
        // given code
        ArrayList<String> str_arr = new ArrayList<>();
        // add Strings into ArrayList
        str_arr.add("mmjmjbmmm");
        str_arr.add("kgkbjjbbgbbjb");
        str_arr.add("bbmmjmb");
        str_arr.add("bjggjggkjmkmj");
        str_arr.add("bjggjggkjmkmj");


        // start writing code here
        // given ordering: k < m < g < j < b

        // algorithm: find smallest element in array, and make it swap places with the first element
        // then find smallest element in subarray (ignoring first element) and make that swap places with the second element
        // if length of the array is n, iterate n - 1 times

        // creating array list of given characters in order
        ArrayList<Character> ordering = new ArrayList<>();
        ordering.add('k'); ordering.add('m'); ordering.add('g');
        ordering.add('j'); ordering.add('b');

        // iterating three (=str_arr.size() - 1) times (as per algorithm above)
        for (int i = 0; i < str_arr.size() - 1; i++) {
            // by default, we assume first element in subarray is smallest
            String smallestString = str_arr.get(i);     // default smallest string (per given ordering)
            int smallestStringIndex = i;    // index of default smallest string
            // iterating over the rest of the subarray
            for (int j = i + 1; j != str_arr.size(); j++) {
                String currentString = str_arr.get(j);
                // checking if current string is smaller than the currently-known smallest string
                // iterating over current string till it differs from smallest string (or either string runs out)
                int index = 0;
                while (index + 1 <= smallestString.length()
                        && index + 1 <= currentString.length()
                        && smallestString.charAt(index) == currentString.charAt(index))
                    index++;
                // if either string ran out, that means one of the strings is a substring of the other
                // the shorter string is therefore smaller
                if (index == currentString.length() || index == smallestString.length()) {
                    // checking if current string is shorter
                    if (currentString.length() < smallestString.length()) {
                        // updating smallestString and smallestStringIndex
                        smallestString = currentString;
                        smallestStringIndex = j;
                    }   // if current string is longer, we don't need to do anything
                }
                // neither string ran out -> compare characters at index
                else {
                    // finding indices of differing character in the ordering ArrayList
                    // since these characters have to be different (exiting condition of while loop)
                        // one is greater than the other
                    int smallestStringCharIndex = ordering.indexOf(smallestString.charAt(index));
                    int currentStringCharIndex = ordering.indexOf(currentString.charAt(index));
                    // checking if current string is smaller
                    if (currentStringCharIndex < smallestStringCharIndex) {
                        smallestString = currentString;
                        smallestStringIndex = j;
                    }
                }
            }
            // swapping element at index i with the smallest string
            String stringToSwap = str_arr.get(i);
            str_arr.set(i, smallestString);
            str_arr.set(smallestStringIndex, stringToSwap);
        }
    }
}