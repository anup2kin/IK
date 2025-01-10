#include <vector>
#include <string>
#include <unordered_map>

using namespace std;


vector<int> findAnagrams(string s, string p) {
    // Similar to https://leetcode.com/problems/permutation-in-string/
    vector<int> r;

    if(size(p) > size(s)) return r;

    int k = size(p);

    // Prepare hash map of required characters with required frequencies from string s1.
    unordered_map<char,int> map_char_freq_req;
    for(auto ch : p) ++map_char_freq_req[ch];

    // Lets Prepare hash map of characters with their frequencies from s2 using window size of k.
    unordered_map<char,int> map_char_freq_have;
    // The variable to keep track of total number of satisfied number of characters
    int total_yes = 0;
    // The variable to store number of satisfied number of characters required.
    int required_yes = size(map_char_freq_req);
    for(int i = 0; i < k; i++)
    {
        // Update have map
        auto it_have = map_char_freq_have.find(s[i]);
        if(it_have == end(map_char_freq_have)) it_have = map_char_freq_have.insert({s[i], 0}).first;
        ++map_char_freq_have[s[i]];

        // Get value from required map
        auto it_req = map_char_freq_req.find(s[i]);
        // If this character is not present is required map, continue with next character in s2
        if(it_req == end(map_char_freq_req)) continue;

        // Update total_yes
        if(it_req->second == it_have->second) ++total_yes;
        else if(it_have->second == it_req->second + 1) --total_yes;
    }

    if(total_yes == required_yes) r.emplace_back(0);;

    for(int i = k; i < size(s); i++)
    {
        // Update have map and total_yes for the character going out of the window
        auto it_have = map_char_freq_have.find(s[i - k]);
        --it_have->second;

        // Get required count for character going out of the window
        auto it_req = map_char_freq_req.find(s[i - k]);
        // If this character is not present in required map, nothing to be done here.
        if(it_req != end(map_char_freq_req))
        {
            // Update total_yes for the characters going out of the window
            if(it_have->second == it_req->second) ++total_yes;
            else if(it_have->second + 1 == it_req->second) --total_yes;
        }

        // If the count of outgoing character reaches 0, remove it from have map
        if(it_have->second == 0) map_char_freq_have.erase(it_have);

        // Update have map with the character coming into the window
        it_have = map_char_freq_have.find(s[i]);
        if(it_have == end(map_char_freq_have)) it_have = map_char_freq_have.insert({s[i], 0}).first;
        ++it_have->second;

        // Get required count for the character coming into the window
        it_req = map_char_freq_req.find(s[i]);
        if(it_req != end(map_char_freq_req))
        {
            // Update total_yes count for the character coming to the window
            if(it_have->second == it_req->second) ++total_yes;
            else if(it_have->second == it_req->second + 1) --total_yes;
        }

        // If size is same and total_yes is same as required, the return true
        if(size(map_char_freq_req) == size(map_char_freq_have) && total_yes == required_yes) r.emplace_back(i - k + 1);
    }

    return r;
}