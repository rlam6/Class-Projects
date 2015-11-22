#ifndef HASHMAP_HPP
#define HASHMAP_HPP

#include <functional>
#include <string>



class HashMap
{
public:
    typedef std::function<unsigned int(const std::string&)> HashFunction;

    static constexpr unsigned int initialBucketCount = 10;


public:
    HashMap();

    HashMap(HashFunction hasher);

    HashMap(const HashMap& hm);
    ~HashMap();
    HashMap& operator=(const HashMap& hm);


    void add(const std::string& key, const std::string& value);

    void remove(const std::string& key);

    bool contains(const std::string& key) const;

    std::string value(const std::string& key) const;

    unsigned int size() const;

    unsigned int bucketCount() const;

    double loadFactor() const;

    unsigned int maxBucketSize() const;

    unsigned int getBucketSize(unsigned int i) const;

    void incrementSize();

    void decrementSize();

    void clearBucket(int index);

    void assignHashVars(const HashMap& hm);

    void emptyHashTable();

    void assignHashTable(const HashMap& hm);

    void printAll() const;


private:
    struct Node
    {
        std::string key;
        std::string value;
        Node* next;
    };


    HashFunction hasher;


    unsigned int tableSize;
    unsigned int buckets;
    Node** hashTable;

};


#endif // HASHMAP_HPP

