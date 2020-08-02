// Map.cpp

#include "Map.h"
#include <iostream>
using namespace std;

Map::Map()
    : m_size(0), m_head(nullptr), m_tail(nullptr)
{}

Map::~Map() {
    // user-defined destructor
    while (m_head != nullptr)
        erase(m_head->m_key);
}

Map::Map(const Map& other) {
    // user-defined copy constructor
    m_size = 0;
        // m_size is incremeneted to other.m_size as elements are added

    m_head = nullptr; m_tail = nullptr; 
        // initialising m_head and m_tail so elements are inserted appropriately
    
    // copying linked list element-by-element
    for (int i = 0; i != other.m_size; i++) {
        KeyType key;
        ValueType val;
        other.get(i, key, val); // copies next Pair's data into key, val
        insert(key, val); // inserts key, value into Map
    }
}

Map& Map::operator=(const Map& other) {
    // user-defined operator
    if (this != &other) {
        Map temp = other; // initialise a Map temp with other's information
        this->swap(temp); // swap information in this map with information in temp 
    } // temp is deleted when we exit loop, leaving this as a copy of other
    return *this;
}

int Map::size() const { return m_size; }

bool Map::empty() const { return size() == 0; }

bool Map::contains(const KeyType& key) const { return find(key) != nullptr; }

bool Map::insert(const KeyType& key, const ValueType& value) {
    return doInsertOrUpdate(key, value, true /* insert */, false /* no update */);
}

bool Map::update(const KeyType& key, const ValueType& value) {
    return doInsertOrUpdate(key, value, false /* no insert */, true /* update */);
}

bool Map::insertOrUpdate(const KeyType& key, const ValueType& value) {
    return doInsertOrUpdate(key, value, true /* insert */, true /* update */);
}

bool Map::erase(const KeyType& key) {
    Pair* p_pair = find(key);
    
    if (p_pair == nullptr)  // not found
        return false;

    // found; removing p_pair from the linked list

    // linking the two elements adjacent to p_pair
    if (p_pair == m_head) // first element in list
        m_head = p_pair->m_next;
    else // not the first element in list (we can therefore follow p_pair->m_prev)
        p_pair->m_prev->m_next = p_pair->m_next;

    if (p_pair == m_tail) // last element in list
        m_tail = p_pair->m_prev; 
    else // not the last element in list (we can therefore follow p_pair->m_next)
        p_pair->m_next->m_prev = p_pair->m_prev;

    // deleting p_pair and decrementing m_size
    delete p_pair;
    m_size--;

    return true;
}

bool Map::get(const KeyType& key, ValueType& value) const
{
    Pair* p_pair = find(key);
    if (p_pair == nullptr)  // not found
        return false;

    value = p_pair->m_value;
    return true;
}

bool Map::get(int i, KeyType& key, ValueType& value) const
{
    if (i < 0 || i >= m_size)
        return false;

    // finding "i"th pair
    Pair* p_pair; int j = 0;
    for (p_pair = m_head; j != i; p_pair = p_pair->m_next)
        j++;
        // note: when p_pair is initialised to m_head, we know m_head is not a null pointer (and equivalently, the list is not empty),
            // since if m_head were a null pointer, m_size would be 0 and (i < 0 || i >= m_size) would always evaluate true 
            // and we would've returned false
        // p_pair is therefore initialised with a valid pointer
        // we also know p_pair exits the loop with a valid value, because we followed p_pair at most m_size times (j != i <= m_size times), 
            // we therefore end with a pointer to either the last object or some object before it

    key = p_pair->m_key;
    value = p_pair->m_value;
    return true;
}

void Map::swap(Map& other)
{
    // Swap heads
    Pair* temp = m_head;
    m_head = other.m_head;
    other.m_head = temp;

    // Swap tails
    temp = m_tail;
    m_tail = other.m_tail;
    other.m_tail = temp;

    // Swap sizes
    int t = m_size;
    m_size = other.m_size;
    other.m_size = t;
}

Map::Pair* Map::find(const KeyType& key) const {
    // Search for the key over the linked list and return a pointer if correct pair found
    Pair* p_pair;
    for (p_pair = m_head; p_pair != nullptr && p_pair->m_key != key; p_pair = p_pair->m_next)
        ;
    return p_pair; // either returns pointer to correct Pair or nullptr
}

bool Map::doInsertOrUpdate(const KeyType& key, const ValueType& value,
    bool mayInsert, bool mayUpdate)
{
    Pair* p_pair = find(key);
    if (p_pair != nullptr)  // found
    {
        if (mayUpdate)
            p_pair->m_value = value;
        return mayUpdate;
    }
    if (!mayInsert)  // not found, and not allowed to insert
        return false;

    // inserting pair at end of list
    p_pair = new Pair;
    // initialising data members of new pair
    p_pair->m_key = key;
    p_pair->m_value = value;
    p_pair->m_next = nullptr; // end of list

    if (m_head == nullptr) { // p_pair is first element in previously no-element list
        p_pair->m_prev = nullptr;
        m_head = p_pair;
    }
    else { // p_pair is not the first element
        p_pair->m_prev = m_tail;
        m_tail->m_next = p_pair;
            // m_tail cannot be nullptr, since when first element was added, m_tail was initialised to pointer to that element
    }
    // updating m_tail and incrementing m_size
    m_tail = p_pair;
    m_size++;

    return true;
}

// -------------------------------------------------------------------------------------------
// Auxiliary functions

bool combine(const Map& m1, const Map& m2, Map& result) {
    
    bool return_value = true; // stays true unless we find a key in both m1 and m2 with different values

    result = m1; // initialising result with m1
        // all keys in m1 now in result
        // keys only in m1, or keys in both m1 and m2 with the same values, will stay in m1
        // keys in both m1 and m2 with different values will later be removed

    // iterating through m2
    for (int i = 0; i != m2.size(); i++) {
        KeyType key;
        ValueType val;
        m2.get(i, key, val); // (key, val) now a key-value pair from m2

        // m1 doesn't have key -> key appears only in m2
        if (!m1.contains(key))
            result.insert(key, val);
        // m1 already has key -> key appears in both m1 and m2
        else {
            ValueType m1_val;
            m1.get(key, m1_val); // m1_val stores the value associated with the key in m1
            if (m1_val != val) { // values in m1 and m2 are different -> key should not be in result, and we need to return false
                result.erase(key);
                return_value = false;
            }
        }
    }

    return return_value;
}

void reassign(const Map& m, Map& result) {
    // when reassign returns, result must contain, for each pair p1 in m, a pair with p1's key mapping to a value copied from a different pair p2 in m, 
        // and no other pair in result has its value copied from p2

    Map result_map; // creates an empty map to temporarily store the result 
        // this deals with both the case of result not being an empty map (since we'll replace result with result_map later),
        // and the case where m and result are the same map (since we then don't have to worry about how we're modifying m in the implementation)

    // iterating over all elements of m1 returned by get to change their values
    for (int i = 0; i != m.size(); i++) {
        
        // finding current key and value
        KeyType current_key; ValueType current_val;
        m.get(i, current_key, current_val);

        // finding next key and next value
        KeyType next_key; ValueType next_val;

        // if not last element returned by get, we can get next element by using i + 1
        if (i != m.size() - 1)
            m.get(i + 1, next_key, next_val);
        // if last element returned by get, the next element should be the the first element returned by get (using 0)
        else
            m.get(0, next_key, next_val);

        result_map.insert(current_key, next_val); // inserting the current key with the next value in result_map
    }

    // overwriting result with the desired result_map
    result = result_map;
}