#include "Map.h"

// globals: DEFAULT_MAX_ITEMS, KeyType and ValueType defined in Map.h

Map::Map() 
    : m_size(0) {}
    // Create an empty map (i.e., one with no key/value pairs)
    

bool Map::empty() const { return (size() == 0); }
    // Return true if the map is empty, otherwise false.


int Map::size() const { return m_size; }
    // Return the number of key/value pairs in the map.


bool Map::insert(const KeyType& key, const ValueType& value) {
    // If key is not equal to any key currently in the map, and if the key/value pair can be added to the map, then do so and return true.
    // Otherwise, make no change to the map and return false 
        // (indicating that either the key is already in the map, or the map has a fixed capacity and is full).

    // can't add another key or key is already in map
    if (size() == DEFAULT_MAX_ITEMS || contains(key) == true)
        return false;
            
    // haven't yet returned false -> key isn't in map and can be added
    m_pairs[m_size] = Pair(key, value); // creating new Pair object in the m_size index of the pairs array
    m_size++; // incrementing m_size
    return true;
}

bool Map::update(const KeyType& key, const ValueType& value) {
    // If key is equal to a key currently in the map, then make that key no longer map to the value it currently maps to, but instead map to
    // the value of the second parameter; return true in this case. Otherwise, make no change to the map and return false.

    // checking for key in map
    int index = pair_index(key); // index of pair with given key
    if (index != -1){
        m_pairs[index].m_value = value; // changing value
        return true;
    }

    // no key found -> returning false
    return false;
};

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
    // If key is equal to a key currently in the map, then make that key no longer map to the value that it currently maps to, but instead map to
        // the value of the second parameter; return true in this case. 
    // If key is not equal to any key currently in the map and if the key/value pair can be added to the map, then do so and return true. 
    // Otherwise, make no change to the map and return false 
        // (indicating that the key is not already in the map and the map has a fixed capacity and is full).

    if (update(key, value)) // if updating was successful, return true
        return true;

    return insert(key, value); // insert returns true if key can be added (and adds key), false if it cannot
            
}

bool Map::erase(const KeyType& key) {
    // If key is equal to a key currently in the map, remove the key/value pair with that key from the map and return true.
    // Otherwise, make no change to the map and return false.

    // checking for key in map
    int index = pair_index(key);
    if (index != -1) { // key found
        for (int i = index; i + 1 != DEFAULT_MAX_ITEMS - 1; i++)
            m_pairs[i] = m_pairs[i + 1]; // moves all successive elements of the array to the left
        m_size--; // decrementing size
        return true;
    }

    // no key found
    return false;
}

bool Map::contains(const KeyType& key) const {
    // Return true if key is equal to a key currently in the map, otherwise false.
    
    // checking for key in map
    if (pair_index(key) != -1) // key found
        return true;

    // key not found
    return false;
}

bool Map::get(const KeyType& key, ValueType& value) const {
    // If key is equal to a key currently in the map, set value to the value in the map which that key maps to, and return true.
    // Otherwise, make no change to the value parameter of this function and return false.
    
    //checking for key in map
    int index = pair_index(key); // index of pair with given key
    if (index != -1) { // key found
        value = m_pairs[index].m_value; // changing value
        return true;
    }

    // no key found
    return false;
}

bool Map::get(int i, KeyType& key, ValueType& value) const {
    // If 0 <= i < size(), copy into the key and value parameters the key and value of one of the key/value pairs in the map and return true.
    // Otherwise, leave the key and value parameters unchanged and return false.  (See below for details about this function.)
    
    // i in bounds -> update key and value
    if (i >= 0 || i < size()) {
        key = m_pairs[i].m_key;
        value = m_pairs[i].m_value;
        return true;
    }
    else return false; // i out of bounds
}

void Map::swap(Map& other) {
    // Exchange the contents of this map with the other one.

    int initial_this_size = m_size;
    int initial_other_size = other.m_size;

    for (int i = 0; i != m_size && i != other.m_size; i++) { // iterating over maps to swap the common number of elements
        // swapping Pair objects
        Pair temp = m_pairs[i]; // temporarily stores pair from this map
        m_pairs[i] = other.m_pairs[i]; // replaces pair from this map
        other.m_pairs[i] = temp; // replaces pair from other map
    }
    
    // one of the maps has run out -> need to add remaining elements from one map to second

    if (m_size > other.m_size) // this map is larger
        for (int i = other.m_size; i != m_size; i++)
            other.insert(m_pairs[i].m_key, m_pairs[i].m_value); // inserting extra m_keys from this map to other map
    if (m_size < other.m_size) // other map is larger
        for (int i = m_size; i != other.m_size; i++)
            insert(other.m_pairs[i].m_key, other.m_pairs[i].m_value); // inserting extra m_keys from other map to this map

    // swapping sizes
    m_size = initial_other_size;
    other.m_size = initial_this_size;

}
// ------------------------------------------------------------------------------------
// Auxiliary member functions

int Map::pair_index(const KeyType& key) const {
    // returns key index if key in m_pairs; returns -1 otherwise

    // searching for key and returning index if found
    for (int i = 0; i != size(); i++)
        if (m_pairs[i].m_key == key)
            return i;

    // key not found
    return -1;
}