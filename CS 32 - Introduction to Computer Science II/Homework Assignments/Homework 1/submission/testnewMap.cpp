#include "newMap.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

int main()
{
    // testing constructor function
    Map constructor_test;
    assert(constructor_test.size() == 0); // when constructed, map is empty
    Map constructor_test2(0);
    assert(!constructor_test2.insert("a", 1)); // cannot insert because maxSize is 0

    // testing empty function and size function
    Map empty_test(DEFAULT_MAX_ITEMS);
    assert(empty_test.empty() && empty_test.size() == 0); // m is empty, has size 0
    assert(empty_test.insert("abc", 1.5)); // preliminary test of insert; should return true
    assert(!empty_test.empty() && empty_test.size() == 1); // m is no longer empty, has size 1
    
    // testing insert function
    Map insert_test(5);
    for (int i = 0; i != 5; i++)
        assert(insert_test.insert(string(1, char(65 + i)), i)); // creates a map of first five letters A, B, C, D, E
    assert(insert_test.size() == 5 && !insert_test.insert("abc", 1920)); 
        // should not be able to add another element, now that Map is fully populated
    assert(insert_test.erase("A")); // preliminary test of erase; should return true
    assert(insert_test.size() == 4 && !insert_test.insert("B", 1));
        // map is no longer fully populated, but can't insert because "B" is already in map

    // testing update function
    Map update_test(2);
    update_test.insert("test key", 1.21);
    assert(update_test.update("test key", 85)); // updates value associated with test key and returns true
    assert(!update_test.update("some other key", 85)); // "some other key" not in map, returns false

    
    // testing insertOrUpdate function
    Map insertOrUpdate_test(100);
    for (int i = 0; i != 100; i++)
        insertOrUpdate_test.insertOrUpdate(to_string(i), i); // fully populates map with 100 elements
    double updated_value;
    assert(insertOrUpdate_test.insertOrUpdate("1" , -1) && insertOrUpdate_test.get("1", updated_value) && updated_value == -1); 
        // first test updates "1" value to -1 and returns true
        // second test changes updated_value to value associated with "1" (which should now be -1) and returns true
        // third test checks whether updated value is -1
    assert(!insertOrUpdate_test.insertOrUpdate("abc", 1)); // "abc" not in list, and can't be added -> returns false
    assert(insertOrUpdate_test.erase("1")); // clears one spot in the map; preliminary test of erase
    assert(insertOrUpdate_test.insertOrUpdate("abc", 1)); // "abc" not in list, and space in map -> "abc" added, returns false
    
    // testing erase function
    Map erase_test(5);
    erase_test.insert("abc", 1);
    assert(!erase_test.erase("xyz")); // should return false, since "xyz" not in map
    assert(erase_test.erase("abc") && erase_test.size() == 0 && !erase_test.contains("abc")); 
        // erase "abc" -> size of erase_test is 0, and erase_test no longer contains "abc"
    
    // testing contains function
    Map contains_test(5);
    contains_test.insert("abc", 1);
    assert(contains_test.contains("abc") && !contains_test.contains("xyz"));
        // "abc" in map, "xyz" not
    
    // testing get functions
    Map get_test(10);
    // testing two-argument get function
    get_test.insert("Fred", 3.29);
    get_test.insert("Ethel", 3.93);
    double value;
    assert(get_test.get("Fred", value) && value == 3.29); // value modified to "Fred" value 3.29
    assert(get_test.get("Ethel", value) && value == 3.93); // value modified to "Ethel" value to 3.92
    // testing three argument get function
    get_test.insert("Lucy", 3.88);
    string keys; double value_total = 0;
    for (int i = 0; i != 3; i++) {
        string key; double value;
        assert(get_test.get(i, key, value));
        keys += key + " "; 
        value_total += value;
    }
    assert(keys == "Fred Ethel Lucy " && value_total == 3.29 + 3.93 + 3.88);
        // checking whether each key and value was detected
    
    // testing swap function
    Map swap_test1(1); // can only hold one item ("Fred")
    swap_test1.insert("Fred", 2.956);
    Map swap_test2(2); // can only hold two items ("Ethel" and "Lucy")
    swap_test2.insert("Ethel", 3.538);
    swap_test2.insert("Lucy", 2.956);
    swap_test1.swap(swap_test2); // swap m1 and m2 (capacities are also swapped)
    assert(swap_test1.size() == 2 && swap_test1.contains("Ethel") && swap_test1.contains("Lucy") &&
        swap_test2.size() == 1 && swap_test2.contains("Fred"));
        // testing whether maps were swapped successfuly

    cerr << "All tests passed successfully." << endl;

    
}