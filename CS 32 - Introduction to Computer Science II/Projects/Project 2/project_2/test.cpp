#include "Map.h"
#include <iostream>
#include <string>
#include <cassert>
using namespace std;

string map_info(const Map& m);
void test();
void combine_test();
void reassign_test();

int main() {
    test();
    combine_test();
    reassign_test();
}

void reassign_test() {
    Map result;
    result.insert("Jack", 84); // non-empty result map

    Map m;
    
    // calling reassign on empty map m and non-empty map result
    reassign(m, result); 
    assert(result.size() == 0); // result should be empty

    // calling reassign on map m with single entry and non-empty map result
    m.insert("Fred", 123);
    reassign(m, result);
    assert(result.size() == 1 && map_info(result) == "Fred 123 ");
    
    // calling reassign on map m with two entries and non-empty map result
    m.insert("Ethel", 456);
    reassign(m, result); // exchange Fred and Ethel's values
    assert(result.size() == 2 && map_info(result) == "Fred 456 Ethel 123 ");
    
    // calling reassign on map m with four entries and non-empty map result
    m.insert("Lucy", 789); m.insert("Ricky", 321);
    reassign(m, result);
    assert(result.size() == 4 && map_info(result) == "Fred 456 Ethel 789 Lucy 321 Ricky 123 ");

    // calling reassign on map m with four entries (where two entries have same value) and non-empty map result
    m.update("Lucy", 456);
    reassign(m, result);
    assert(result.size() == 4 && map_info(result) == "Fred 456 Ethel 456 Lucy 321 Ricky 123 ");

    // calling reassign on map m with itsel to check whether the result map (in this case, m itself) is modified correctly
    reassign(m, m);
    assert(result.size() == 4 && map_info(result) == "Fred 456 Ethel 456 Lucy 321 Ricky 123 ");

    cerr << "All reassign tests passed successfully." << endl;
}

void combine_test() {

    // Testing combine
    Map m1;
    m1.insert("Fred", 123); m1.insert("Ethel", 456); m1.insert("Lucy", 789);
    Map m2;
    m2.insert("Lucy", 789); m2.insert("Ricky", 321);
    Map result;
    result.insert("Jack", 129);
    assert(combine(m1, m2, result)); // no pairs with conflicting values -> combine returns true

    assert(result.size() == 4 && map_info(result) == "Fred 123 Ethel 456 Lucy 789 Ricky 321 ");

    // testing case where m1 and m2 have conflicting (key, value) pairs
    m2.update("Lucy", 654); // updating value associated with "Lucy" so it's no longer 789
        // values associated with Lucy are now different in m1 and m2
    assert(!combine(m1, m2, result));

    assert(result.size() == 3 && map_info(result) == "Fred 123 Ethel 456 Ricky 321 ");

    cerr << "All combine tests passed successfully." << endl;

}


void test()
{
    // testing default constructor 
    Map constructor_test;
    assert(constructor_test.size() == 0); // when constructed, map is empty

    // testing copy constructor
    Map test; test.insert("Fred", 3.29); test.insert("Ethel", 3.93);
        // creating a map
    Map test_copy = test;
        // creating a new map test_copy with copy constructor
    assert(test_copy.size() == 2 && map_info(test_copy) == "Fred 3.29 Ethel 3.93 ");
        // checking whether test_copy was initialised correctly

    // testing operator =
    Map test_equal;
    test_equal = test;
    assert(test_equal.size() == 2 && map_info(test_equal) == "Fred 3.29 Ethel 3.93 ");
    // testing aliasing; test_equal should remain the same
    test_equal = test_equal;
    assert(test_equal.size() == 2 && map_info(test_equal) == "Fred 3.29 Ethel 3.93 ");


    // testing empty function and size function
    Map empty_test;
    assert(empty_test.empty() && empty_test.size() == 0); // m is empty, has size 0
    assert(empty_test.insert("abc", 1.5)); // preliminary test of insert; should return true
    assert(!empty_test.empty() && empty_test.size() == 1); // m is no longer empty, has size 1

    // testing insert function
    Map insert_test;
    for (int i = 0; i != 10; i++)
        assert(insert_test.insert(to_string(i), i)); // creates a map of first ten number strings and corresponding values
    assert(insert_test.erase("0")); // preliminary test of erase; should return true
    assert(!insert_test.insert("1", int('1')));
    // can't insert because "1" is already in map

// testing update function
    Map update_test;
    update_test.insert("test key", 1.21);
    assert(update_test.update("test key", 85)); // updates value associated with test key and returns true
    assert(!update_test.update("some other key", 85)); // "some other key" not in map, returns false

    // testing insertOrUpdate function
    Map insertOrUpdate_test;
    for (int i = 0; i != 10; i++)
        insertOrUpdate_test.insertOrUpdate(to_string(i), i); // creates a map of first ten number strings and corresponding values
    double updated_value;
    assert(insertOrUpdate_test.insertOrUpdate("1", -1) && insertOrUpdate_test.get("1", updated_value) && updated_value == -1);
    // first test updates "1" value to -1 and returns true
    // second test changes updated_value to value associated with "1" (which should now be -1) and returns true
    // third test checks whether updated value is -1
    assert(insertOrUpdate_test.insertOrUpdate("abc", 1)); // "abc" not in list, and therefore can be added -> returns true

    // testing erase function
    Map erase_test;
    erase_test.insert("abc", 1);
    assert(!erase_test.erase("xyz")); // should return false, since "xyz" not in map
    assert(erase_test.erase("abc") && erase_test.size() == 0 && !erase_test.contains("abc"));
    // erase "abc" -> size of erase_test is 0, and erase_test no longer contains "abc"

// testing contains function
    Map contains_test;
    contains_test.insert("abc", 1);
    assert(contains_test.contains("abc") && !contains_test.contains("xyz"));
    // "abc" in map, "xyz" not

// testing get functions
    Map get_test;
    // testing two-argument get function
    get_test.insert("Fred", 3.29);
    get_test.insert("Ethel", 3.93);
    get_test.insert("Jack", 3.12);
    double value;
    assert(get_test.get("Fred", value) && value == 3.29); // value modified to "Fred" value 3.29
    assert(get_test.get("Ethel", value) && value == 3.93); // value modified to "Ethel" value to 3.92
    assert(!get_test.get("Lucy", value));   // "Lucy" not in map, get returns false
    assert(get_test.erase("Jack")); // additional test of erase
    // testing three argument get function
    get_test.insert("Lucy", 3.88);
    assert(map_info(get_test) == "Fred 3.29 Ethel 3.93 Lucy 3.88 ");
        // checking whether each key and value was detected
    Map get_test2;
    string key = "this should not be changed"; double val = -1;
    for (int i = -1; i != 100; i++)
        get_test2.get(i, key, val); // since the map is empty, key and val should be unchanged by the get function
    assert(key == "this should not be changed" && val == -1);

// testing swap function
    Map swap_test1;
    swap_test1.insert("Fred", 2.956);
    Map swap_test2;
    swap_test2.insert("Ethel", 3.538);
    swap_test2.insert("Lucy", 2.956);
    swap_test1.swap(swap_test2); // swap m1 and m2
    
    assert(swap_test1.size() == 2 && map_info(swap_test1) == "Ethel 3.538 Lucy 2.956 " &&
        swap_test2.size() == 1 && map_info(swap_test2) == "Fred 2.956 ");
    // testing whether maps were swapped successfuly

    swap_test1.swap(swap_test1);
    assert(map_info(swap_test1) == "Ethel 3.538 Lucy 2.956 ");
    // test1 should remain unchanged


    cerr << "All tests passed successfully." << endl;
}

string map_info(const Map& m) {
        // returns a string with all the key value pairs in format "key1 value1 key2 value2... "
    string map_info;
    for (int i = 0; i != m.size(); i++) {
        KeyType key; ValueType value;
        m.get(i, key, value);
        string str_value = to_string(value);
        str_value.erase(str_value.find_last_not_of('0') + 1, string::npos); // to get rid of trailing zeros when converting double to string
        str_value.erase(str_value.find_last_not_of('.') + 1, string::npos); // to get rid of trailing period when converting double to string
        
        map_info += key + " " + str_value + " ";
    }
    return map_info;
}