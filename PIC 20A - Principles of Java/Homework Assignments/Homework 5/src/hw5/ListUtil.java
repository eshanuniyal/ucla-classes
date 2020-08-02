package hw5;

import java.util.Collection;
import java.util.ArrayList;
import java.util.function.Predicate;

public class ListUtil {
    public static <E> ArrayList<E> merge(Collection<? extends E> c1, Collection<? extends E> c2) {
        // returns an ArrayList that contains all the elements of c1 and c2
        // creating ArrayList
        ArrayList<E> mergedArr = new ArrayList<>();
        // adding all elements from c1 and c2 into mergedArr
        mergedArr.addAll(c1);
        mergedArr.addAll(c2);
        // returning mergedArr
        return mergedArr;
    }
    public static <E> ArrayList<E> select(Collection<? extends E> coll, Predicate<? super E> pred) {
        // returns an ArrayList<E> that contains all elements of coll for which pred.test evaluates to true
        // creating ArrayList
        ArrayList<E> trueArr = new ArrayList<>();
        // iterating through coll
        for (E elem : coll)
            // checking predicate
            if (pred.test(elem))
                // inserting element
                trueArr.add(elem);
        // returning trueArr
        return trueArr;
    }
}
