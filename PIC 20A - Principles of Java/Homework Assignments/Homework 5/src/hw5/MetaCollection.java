package hw5;

import java.util.*;

public class MetaCollection<E> extends AbstractCollection<E> {
    // Keep references to added collections in this list
    private final ArrayList<Collection<E>> collectionList;

    public MetaCollection(Collection<E>... c_arr) {
        // takes in a variable number of Collection<E>s; initializes the MetaCollection<E> to be the concatenation of them
        // initialising collectionList
        collectionList = new ArrayList<>();
        // iterating over c_arr to insert each collection into collectionList
        for (Collection<E> coll : c_arr)
            collectionList.add(coll);

    }
    public void addCollection(Collection<E> coll) {
        // adds coll to the MetaCollection<E>
        collectionList.add(coll);
    }

    @Override
    public Iterator<E> iterator() {
        return new JoinedIter();
    }

    @Override
    public int size() {
        // returns the sum of the sizes of the Collection<E>s the MetaCollection<E> consists of
        int totalSize = 0;
        // iterating over collectionList
        for (Collection<E> coll : collectionList)
            totalSize += coll.size();
        return totalSize;
    }

    private class JoinedIter implements Iterator<E> {
        // counter for the iterator (used by hasNext)
        private int itrCounter = 0;

        public boolean hasNext() {
            // return true if there is a next element
            return (itrCounter < size());
        }
        public E next() {
            // return the next element (i.e. element effectively at index itrCounter in the MetaCollection)

            // initialising variable to keep track of elements we've skipped
            int index = 0;

            // iterating over collections
            for (Collection<E> coll : collectionList) {
                // checking if current collection contains the desired element (i.e. itrCounter falls in coll)
                if (coll.size() <= itrCounter - index)
                    // desired index doesn't lie in current collection -> skipping all elements
                    index += coll.size();
                // current collection contains desired element
                else {
                    // finding desired element; iterating over coll
                    for (E element : coll){
                        // desired index found -> increment itrCounter and return element
                        if (index == itrCounter) {
                            itrCounter++;
                            return element;
                        }
                        // desired index not reached yet -> increment index
                        else index++;
                    }
                }
            }
            // could not find next element
            throw new NoSuchElementException();
        }
    }
}
