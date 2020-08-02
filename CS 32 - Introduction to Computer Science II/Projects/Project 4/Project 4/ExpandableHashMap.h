// ExpandableHashMap.h

// Skeleton for the ExpandableHashMap class template.  You must implement the first six
// member functions.

#ifndef EXPANDABLE_HASH_MAP_H
#define EXPANDABLE_HASH_MAP_H

#include <list>
#include <vector>

// ##################################################################################################################
// GLOBAL CONSTANTS
// ##################################################################################################################

const int DEFAULT_BUCKETS = 8;					// default number of buckets in an empty map
const double DEFAULT_MAX_LOAD_FACTOR = 0.5;		// default maximum load factor of a map
const int REHASH_FACTOR = 2;					// factor by which to increase number of buckets when rehashing a map

// ##################################################################################################################
// EXPANDABLEHASHMAP CLASS DECLARATION
// ##################################################################################################################

template<typename KeyType, typename ValueType>
class ExpandableHashMap {

	public:

		ExpandableHashMap(double maximumLoadFactor = 0.5);
		~ExpandableHashMap();
		void reset();
		int size() const;
		void associate(const KeyType& key, const ValueType& value);

		  // for a map that can't be modified, return a pointer to const ValueType
		const ValueType* find(const KeyType& key) const;

		  // for a modifiable map, return a pointer to modifiable ValueType
		ValueType* find(const KeyType& key)
		{
			return const_cast<ValueType*>(const_cast<const ExpandableHashMap*>(this)->find(key));
		}

		  // C++11 syntax for preventing copying and assignment
		ExpandableHashMap(const ExpandableHashMap&) = delete;
		ExpandableHashMap& operator=(const ExpandableHashMap&) = delete;

	private:
		
		// implementing a node with key value pairs
		struct Node {

			// constructor
			Node(const KeyType& key, const ValueType& value)
				: m_key(key), m_value(value) {}

			// key and value
			KeyType m_key;
			ValueType m_value;
		};
		
		// private member functions
		void clearHashMap();														// properly clear the hash map
		unsigned int getBucketNumber(const KeyType& key, int tableSize) const;		// get bucket number of passed-in key given size of table
		void rehashMap();															// rehash the map into a larger map
		
		// private data members
		std::vector<std::list<Node*>> m_table;	// a vector of linked lists containing pointers to Node objects
		int m_nElements;							// number of elements in map
		double m_maxLoadFactor;						// the maximum load factor for the hash map
};

// ##################################################################################################################
// MEMBER FUNCTION IMPLEMENTATIONS
// ##################################################################################################################

// CONSTRUCTOR
template<typename KeyType, typename ValueType>
ExpandableHashMap<KeyType, ValueType>::ExpandableHashMap(double maximumLoadFactor)
	: m_nElements(0) {
	
	if (maximumLoadFactor > 0)
		m_maxLoadFactor = maximumLoadFactor;
	else
		m_maxLoadFactor = DEFAULT_MAX_LOAD_FACTOR;

	// creating a hash map with 8 empty buckets, and swapping the hash map
	std::vector<std::list<Node*>> m_actualTable(DEFAULT_BUCKETS);
	m_table.swap(m_actualTable);
}

// DESTRUCTOR
template<typename KeyType, typename ValueType>
ExpandableHashMap<KeyType, ValueType>::~ExpandableHashMap() {

	// clear hash map
	clearHashMap();
}

// RESET THE HASH MAP
template<typename KeyType, typename ValueType>
void ExpandableHashMap<KeyType, ValueType>::reset() {

	// clear hash map
	clearHashMap();

	// resetting hash map to have eight empty buckets
	std::vector<std::list<Node*>> m_actualTable(DEFAULT_BUCKETS);
	m_table.swap(m_actualTable);

}

// RETURN THE SIZE OF THE MAP
template<typename KeyType, typename ValueType>
int ExpandableHashMap<KeyType, ValueType>::size() const {
    return m_nElements;  // Delete this line and implement this function correctly
}

// ASSOCIATE A NEW KEY-VALUE PAIR IN THE MAP
template<typename KeyType, typename ValueType>
void ExpandableHashMap<KeyType, ValueType>::associate(const KeyType& key, const ValueType& value) {
	// The associate method associates one item (key) with another (value).
	// If no association currently exists with that key, this method inserts a new association into the hashmap with that key/value pair.
	// If there is already an association with that key in the hashmap, then the item associated with that key is replaced by the second parameter (value).
	// Thus, the hashmap must contain no duplicate keys.
	
	// finding bucket association should belong in
	unsigned int bucketN = getBucketNumber(key, m_table.size());

	// iterating over bucket to check whether key already exists
	for (auto itr = m_table[bucketN].begin(); itr != m_table[bucketN].end(); itr++)
		// key found -> update value and return
		if ((*itr)->m_key == key) {
			(*itr)->m_value = value;
			return;
		}

	// key not in bucket -> insert new association and increment number of elements of map
	m_table[bucketN].push_back(new Node(key, value));
	m_nElements++;

	// checking whether a rehashing is required
	if (m_nElements / m_table.size() > m_maxLoadFactor)
		rehashMap();
}

template<typename KeyType, typename ValueType>
const ValueType* ExpandableHashMap<KeyType, ValueType>::find(const KeyType& key) const {
	// If no association exists with the given key, return nullptr; otherwise, return a pointer to the value associated with that key.
	// This pointer can be used to examine that value, and if the hashmap is allowed to be modified, to modify that value directly within the map

	// finding bucket association should belong in
	unsigned int bucketN = getBucketNumber(key, m_table.size());

	// iterating over bucket to see whether key already exists
	for (auto itr = m_table[bucketN].begin(); itr != m_table[bucketN].end(); itr++)
		// key found
		if ((*itr)->m_key == key)
			return &(*itr)->m_value;

	// no key/association found -> return nullptr
    return nullptr;
}

// ##################################################################################################################
// AUXILIARY MEMBER FUNCTIONS
// ##################################################################################################################

template<typename KeyType, typename ValueType>
void ExpandableHashMap<KeyType, ValueType>::clearHashMap() {
	// properly clears the hash map

	// iterating over m_table to delete all linked lists
	for (int i = 0; i != m_table.size(); i++)

		// linked list isn't empty -> call delete on elements in linked list
		if (m_table[i].size() != 0)
			for (auto itr = m_table[i].begin(); itr != m_table[i].end(); itr++)
				delete (*itr);

	// clearing hash map (also automatically frees memory occupied by lists, which now just have dangling pointers)
	m_table.clear();

	// resetting m_nElements
	m_nElements = 0;
}

template<typename KeyType, typename ValueType>
unsigned int ExpandableHashMap<KeyType, ValueType>::getBucketNumber(const KeyType& key, int tableSize) const {
	// returns the number of the bucket key belongs in

	unsigned int hash(const KeyType& k);  // prototype of hash function
	unsigned int h = hash(key); // hashing key
	
	return h % tableSize; // returning bucket number
}

template<typename KeyType, typename ValueType>
void ExpandableHashMap<KeyType, ValueType>::rehashMap() {
	// rehashes map

	// creating a new vector to store the new map; new map is twice as large as old map, and is initialised with nullptrs
	int newSize = 2 * m_table.size();
	std::vector<std::list<Node*>> newTable(newSize);

	// iterating over hash table to insert all associations into new map
	for (int i = 0; i != m_table.size(); i++)

		// iterating over list to insert all associations in list into new map
		for (auto itr = m_table[i].cbegin(); itr != m_table[i].cend(); itr++) {
	
			// finding bucket number of new association
			unsigned int bucketN = getBucketNumber((*itr)->m_key, newSize);
			// inserting pointer to current node
			newTable[bucketN].push_back(*itr);
		}


	m_table.swap(newTable);
}

#endif