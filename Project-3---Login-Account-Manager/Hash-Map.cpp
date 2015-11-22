#include "Hash-Map.hpp"
#include <string>
#include <iostream>

namespace 
{
	unsigned int defaultHasher(std::string const& s) {
		// add up all the ASCII values of the string and return the sum
		unsigned int result = 0;
		for (int i = 0; i < s.length(); i++){
			char c = s[i];
			result += c;
		}
		return result;
	}
}

HashMap::HashMap()
	: hasher{defaultHasher}, tableSize{0}, buckets{initialBucketCount}, hashTable{new Node*[initialBucketCount]}
{
	// Initialize Hash Table with nullpointers
	emptyHashTable();
}

HashMap::HashMap(HashFunction hasher)
	: hasher{hasher}, tableSize{0}, buckets{initialBucketCount}, hashTable{new Node*[initialBucketCount]}
{
	// Initialize Hash Table with nullpointers
	emptyHashTable();
}

HashMap::HashMap(const HashMap& hm)
	: hasher{hm.hasher}, tableSize{hm.tableSize}, buckets{hm.buckets}
{	
	// Copy the new hash table onto current one
	assignHashTable(hm);
}

HashMap::~HashMap()
{
	// clear each bucket from the hash table
	for (int i = 0; i < bucketCount(); i++){
		clearBucket(i);
	}

	// deallocate entire hash table, set table size accordingly back to 0
	delete[] hashTable;
	tableSize = 0;
}

HashMap& HashMap::operator=(const HashMap& hm){
	if (this != &hm){
		// Delete all aspects of old HashMap before assigning everything else
		this->~HashMap();

		// Assign new variables and hash tables to current Hash Map
		assignHashVars(hm);
		assignHashTable(hm);
	}
	return *this;
}

void HashMap::add(const std::string& key, const std::string& value)
{
	if (not contains(key)){
		unsigned int index = hasher(key) % bucketCount();
		// Adding the new node into beginning of bucket index
		Node* node = new Node{key, value, hashTable[index]};
		hashTable[index] = node;

		// Increment table size
		incrementSize();
	}

	// // When bucket list is starting to get too full, create new larger bucket list, replace older one
	if (loadFactor() > 0.8){

		// Initialize new bucket list with null pointers, and length of new bucket list
		unsigned int newBuckets = buckets*2 + 1;
		Node** newHashTable = new Node*[newBuckets];
		for (int i = 0; i < newBuckets; i++){
			newHashTable[i] = nullptr;
		}
		
		// Reorder all keys properly to their hash index with new bucket list length
		for (int i = 0; i < buckets; i++){
			Node* old = hashTable[i];

		 	// Adding node to bucket
			while(old != nullptr){
				unsigned int index = hasher(old->key) % newBuckets;
				newHashTable[index] = new Node{old->key, old->value, newHashTable[index]};
				old = old->next;
			}
		}

		// Delete all the old buckets, including entire bucket list
		this->~HashMap();

		// Reassign buckets to new set of buckets, and amount of buckets
		buckets = newBuckets;
		hashTable = newHashTable;
	}
}

bool HashMap::contains(const std::string& key) const{
	// find node in the hash table
	for (int i = 0; i < bucketCount(); i++){
		Node* current = hashTable[i];

		// return true if key is found inside a node
		while (current != nullptr){
			if (current->key == key){
				return true;
			}
			current = current->next;
		}
	}
	return false;
}

void HashMap::remove(const std::string& key){
	if (contains(key)){

		// Find which index this key particularly belongs in
		unsigned int i = hasher(key) % bucketCount();

		Node* current = hashTable[i];
		Node* previous = current;

		// If the first node in the bucket contains the key, delete it and put whatever was next in the front
		if (hashTable[i] != nullptr and hashTable[i]->key == key){
			Node* old = hashTable[i]->next;
			delete current;
			hashTable[i] = old;
			decrementSize();
			return;
		} 
		// Find the node in the bucket which it equals the key and delete it
		while (current != nullptr){
			if (current->key == key){
				previous->next = current->next;
				delete current;

				// Decrement table size 
				decrementSize();
				return;
			}
			previous = current;
			current = current->next;
		}
		
	}
}

std::string HashMap::value(const std::string& key) const{
	// get index of where key is
	unsigned int keyIndex = hasher(key) % buckets;

	// return value if key is found inside a node
	Node* current = hashTable[keyIndex];
	while (current != nullptr){
		if (current->key == key){
			return current->value;
		}
		current = current->next;
	}
	return "";
}

unsigned int HashMap::size() const{
	// return the size of the hash table
	return tableSize;
}

unsigned int HashMap::bucketCount() const{
	// return amount of buckets
	return buckets;
}

double HashMap::loadFactor() const{
	// return average size of bucket size per bucket
	return size() / double(bucketCount());
}

unsigned int HashMap::maxBucketSize() const{
	unsigned int result = 0;
	unsigned int currentCount;

	// add up every bucket size and return the result
	for (unsigned int i = 0; i < bucketCount(); i++){
		currentCount = getBucketSize(i);
		if (currentCount > result){
			result = currentCount;
		}
	}
	return result;
}

unsigned int HashMap::getBucketSize(unsigned int i) const{
	Node* current = hashTable[i];
	unsigned int currentCount = 0;
	while (current != nullptr){
		currentCount++;
		current = current->next;
	}
	return currentCount;

}

void HashMap::incrementSize(){
	tableSize++;
}

void HashMap::decrementSize(){
	tableSize--;
}

void HashMap::clearBucket(int i){
	Node* current = hashTable[i];

	// recursively delete every node inside a bucket and set that bucket to be null in the end
	if (current != nullptr){
		hashTable[i] = hashTable[i]->next;
		delete current;
		clearBucket(i);
	}
}

void HashMap::emptyHashTable(){
	// make every bucket a nullptr in hash table
	for (int i = 0; i < buckets; i++){
		hashTable[i] = nullptr;
	}
}

void HashMap::assignHashTable(const HashMap& hm){
	// create new hash table
	Node** newHashTable = new Node*[buckets];

	// initialize new hash table
	for (int i = 0; i < hm.buckets; i++){
		newHashTable[i] = nullptr;
	}

	// assign each node in old hash table to new hash table
	for (int i = 0; i < hm.buckets; i++){
		Node* old = hm.hashTable[i];

		while (old != nullptr){
			Node* node = new Node{old->key, old->value, newHashTable[i]};
			newHashTable[i] = node;
			old = old->next;
		}
	}
	// reassign old hash table to the new one
	hashTable = newHashTable;
}

void HashMap::assignHashVars(const HashMap& hm){
	// reassign all member variables from new hash table to old one
	tableSize = hm.size();
	buckets = hm.bucketCount();
	hasher = hm.hasher;
}

void HashMap::printAll() const{
	for (int i = 0; i < bucketCount(); i++){

		// print each node in format this format if it is not a null ptr
		// (key, value) -> (nextKey, nextValue) -> nullptr
		if (hashTable[i]){
			std::cout << "At index " << i << ". the value is ";
			Node* current = hashTable[i];
			while (current != nullptr){
				std::cout << "(" << current->key << ", " << current->value << ") -> ";
				current = current->next;
			}
			std::cout << current << std::endl;
		}
		else{
			std::cout << "At index " << i << ". the value is " << hashTable[i] << std::endl;
		}
	}

}
