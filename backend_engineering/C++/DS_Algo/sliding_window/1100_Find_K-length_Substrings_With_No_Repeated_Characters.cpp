#include <string>
#include <unordered_map>

using namespace std;

int numKLenSubstrNoRepeats(string s, int k) {
    if(k > size(s)) return 0;
    
    // base case
    unordered_map<char,int> map_chars_seen_count;
    int count = 0;
    for(int i = 0; i < k; i++) ++map_chars_seen_count[s[i]];
    if(size(map_chars_seen_count) == k) ++count;

    for(int i = k; i < size(s); i++)
    {
        // Update map based on the character going out of the window.
        auto it = map_chars_seen_count.find(s[i - k]);
        if(it->second == 1) map_chars_seen_count.erase(it);
        else --it->second;
        // Update map based on the character coming into the window.
        ++map_chars_seen_count[s[i]];
        // Update substring count
        if(size(map_chars_seen_count) == k) ++count;
    }

    return count;
}
