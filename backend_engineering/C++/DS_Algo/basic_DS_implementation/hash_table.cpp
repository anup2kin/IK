#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <optional>

/*
    Key points:
    1. Key, value pair (a Node structure)
    2. A vector of linked list (buckets)
    3. A hash function to compute index value.
*/

using namespace std;

struct Node{
    string key;
    int value;

    Node(const string &k, const int &v): key(k), value(v){}
};

class Hash_table{
private:
    const int TABLE_SIZE = 10;
    vector<list<Node>> table;

    int get_hash(const string &key){
        return hash<string>()(key) % TABLE_SIZE;
    }

public:
    Hash_table(): table(TABLE_SIZE){}
    void put(const string &key, const int &value){
        size_t idx = get_hash(key);

        for(auto &node : table[idx]){
            if(node.key == key){
                node.value = value;
                return;
            }
        }

        table[idx].emplace_back(key, value);
    }

    optional<int> get(const string &key){
        size_t idx = get_hash(key);

        for(auto &node : table[idx]){
            if(node.key == key) return node.value;
        }

        return nullopt;
    }

    void remove(const string &key){
        size_t idx = get_hash(key);
        auto &bucket = table[idx];

        for(auto it = begin(bucket); it != end(bucket); it++){
            if(it->key == key){
                bucket.erase(it);
                return;
            }
        }
    }
};

int main() {
    Hash_table ht;

    // Insert key-value pairs
    ht.put("apple", 100);
    ht.put("banana", 200);

    // Retrieve values
    optional<int> val1 = ht.get("apple");
    optional<int> val2 = ht.get("banana");
    optional<int> val3 = ht.get("grape"); // Not present

    if (val1) cout << "apple -> " << *val1 << endl;
    else cout << "apple -> Not Found" << endl;

    if (val2) cout << "banana -> " << *val2 << endl;
    else cout << "banana -> Not Found" << endl;

    if (val3) cout << "grape -> " << *val3 << endl;
    else cout << "grape -> Not Found" << endl;

    return 0;
}