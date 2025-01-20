#include <iostream>
#include <shared_mutex>
#include <vector>
#include <unordered_map>
#include <functional>

/*
    key points:
    1. This is read-heavy data structure. Hence, we should use reader-writer lock i.e. shared mutex.
    1. Do not have global lock for writting since this will lock the entire data structure.
    2. Use lock stripping to have granular writting capability by using bucket.
*/

template <typename Key_type, typename Value_type>
class Bucket
{
public:
    void put(const Key_type &key, const Value_type &value){
        // Acquire exlusive lock on the bucket for writting
        std::unique_lock<std::shared_mutex> lock(mtx);
        map[key] = value;
    }

    std::optional<Value_type> get(const Key_type &key){
        // Acquire reader lock on the bucket
        std::shared_lock<std::shared_mutex> lock(mtx);

        auto it = map.find(key);

        if(it != end(map)) return it->second;
        else return std::nullopt;
    }

private:
    std::shared_mutex mtx;
    std::unordered_map<Key_type, Value_type> map;
};

template <typename Key_type, typename Value_type>
class Reader_writer_map
{
public:
    Reader_writer_map(): buckets(buckets_size){
    }

    void put(Key_type key, Value_type value){
        // Acquire reader lock on the whole data structure.
        std::shared_lock<std::shared_mutex> buckets_reader_lock(mtx);

        Bucket<Key_type, Value_type> &b = buckets[get_hash(key) % buckets_size];

        b.put(key, value);
    }

    std::optional<Value_type> get(Key_type key){
        // Acquire reader lock on the whole data structure
        std::shared_lock<std::shared_mutex> buckets_reader_lock(mtx);

        Bucket<Key_type, Value_type> &b = buckets[get_hash(key) % buckets_size];

        return b.get(key);
    }

private:
    int get_hash(const Key_type& key){
        return std::hash<Key_type>()(key);
    }

    std::shared_mutex mtx;
    const int buckets_size = 10;
    std::vector<Bucket<Key_type, Value_type>> buckets;
};


int main() {
    Reader_writer_map<int, std::string> map;

    // Add some key-value pairs
    map.put(1, "Value1");
    map.put(2, "Value2");

    // Retrieve and print values
    auto value = map.get(1);
    if (value) {
        std::cout << "Key 1: " << *value << std::endl;
    }

    value = map.get(3);
    if (!value) {
        std::cout << "Key 3 not found!" << std::endl;
    }

    return 0;
}