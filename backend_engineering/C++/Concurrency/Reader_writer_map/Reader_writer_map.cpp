#include <iostream>
#include <shared_mutex>
#include <vector>
#include <unordered_map>

template <typename Key_type, typename Value_type>
class Bucket
{
    std::shared_mutex mtx;
    std::unordered_map<Key_type, Value_type> map;
};

template <typename Key_type, typename Value_type>
class Reader_writer_map
{
    std::shared_mutex mtx;
    const int buckets_size = 10;
    std::vector<Bucket<Key_type, Value_type>> buckets;
};