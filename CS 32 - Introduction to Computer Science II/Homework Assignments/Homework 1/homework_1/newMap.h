#ifndef NEWMAP_H
#define NEWMAP_H

#include <string>

// type aliases
using KeyType = int;
using ValueType = std::string;

// global constants
const int DEFAULT_MAX_ITEMS = 240;

class Map
{
public:
    Map(int n = DEFAULT_MAX_ITEMS);   // Create an map with n positions (i.e., one with no key/value pairs)
        // if no n specified, create a map with max DEFAULT_MAX_ITEMS items
    ~Map(); // user-defined destructor 
    Map(const Map& other); // user-defined copy constructor
    Map& operator=(const Map& other);

    bool empty() const;  // Return true if the map is empty, otherwise false.
        // does not modify map

    int size() const;    // Return the number of key/value pairs in the map.
        // does not modify map

    bool insert(const KeyType& key, const ValueType& value);
    // If key is not equal to any key currently in the map, and if the
    // key/value pair can be added to the map, then do so and return true.
    // Otherwise, make no change to the map and return false (indicating
    // that either the key is already in the map, or the map has a fixed
    // capacity and is full).

    bool update(const KeyType& key, const ValueType& value);
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value it currently maps to, but instead map to
    // the value of the second parameter; return true in this case.
    // Otherwise, make no change to the map and return false.

    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    // If key is equal to a key currently in the map, then make that key no
    // longer map to the value that it currently maps to, but instead map to
    // the value of the second parameter; return true in this case.
    // If key is not equal to any key currently in the map and if the
    // key/value pair can be added to the map, then do so and return true.
    // Otherwise, make no change to the map and return false (indicating
    // that the key is not already in the map and the map has a fixed
    // capacity and is full).

    bool erase(const KeyType& key);
    // If key is equal to a key currently in the map, remove the key/value
    // pair with that key from the map and return true.  Otherwise, make
    // no change to the map and return false.

    bool contains(const KeyType& key) const;
        // does not modify map
    // Return true if key is equal to a key currently in the map, otherwise
    // false.

    bool get(const KeyType& key, ValueType& value) const;
        // does not modify map
    // If key is equal to a key currently in the map, set value to the
    // value in the map which that key maps to, and return true.  Otherwise,
    // make no change to the value parameter of this function and return
    // false.

    bool get(int i, KeyType& key, ValueType& value) const;
        // does not modify map
    // If 0 <= i < size(), copy into the key and value parameters the
    // key and value of one of the key/value pairs in the map and return
    // true.  Otherwise, leave the key and value parameters unchanged and
    // return false.  (See below for details about this function.)

    void swap(Map& other);
    // Exchange the contents of this map with the other one.

    // -----------------------------------------------------------------------------
    private:

        // Pair structure declaration
        struct Pair {
            // contains Key, Value pair
            public:
                Pair(KeyType k, ValueType v)
                    :m_key(k), m_value(v) {};

                Pair(){}; // creating default constructor

                KeyType m_key;
                ValueType m_value;
        };

        // private data members
        int m_size; // number of defined objects - we don't look past this
        Pair* m_pairs; // dynamically-allocated array of Pair objects
            // (since any elements past index sz - 1 will be unitialised with junk keys/values
        int m_maxSize; // size of dynamic array

        // private member functions
        int pair_index(const KeyType& key) const;
};

#endif