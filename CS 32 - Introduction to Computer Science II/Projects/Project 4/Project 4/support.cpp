#include "support.h"
#include <string>
#include <functional>

//using namespace std;

unsigned int hash(const std::string& key) {
	std::hash<std::string> strHash;			// creates a string hasher
	return strHash(key);				// hashes key and returns
}