#include <string>
#include <unordered_map>

using namespace std;

bool checkInclusion(string s1, string s2) {
    if(size(s1) > size(s2)) return false;

    int k = size(s1);

    // Prepare the hash map of required characters with required frequencies from string s1.
    unordered_map<char,int> map_char_freq_req;
    for(auto ch : s1) ++map_char_freq_req[ch];

    //Let's Prepare a hash map of characters with their frequencies from s2 using the window size of k.
    unordered_map<char,int> map_char_freq_have;
    // The variable to keep track of the total number of satisfied characters
    int total_yes = 0;
    // The variable to store the number of satisfied characters required.
    int required_yes = size(map_char_freq_req);
    for(int i = 0; i < k; i++)
    {
        // Update have the map
        auto it_have = map_char_freq_have.find(s2[i]);
        if(it_have == end(map_char_freq_have)) it_have = map_char_freq_have.insert({s2[i], 0}).first;
        ++map_char_freq_have[s2[i]];

        // Get value from required map
        auto it_req = map_char_freq_req.find(s2[i]);
        // If this character is not present is the required map, continue with the next character in s2
        if(it_req == end(map_char_freq_req)) continue;

        // Update total_yes
        if(it_req->second == it_have->second) ++total_yes;
        else if(it_have->second == it_req->second + 1) --total_yes;
    }

    if(total_yes == required_yes) return true;

    for(int i = k; i < size(s2); i++)
    {
        // Update have map and total_yes for the character going out of the window
        auto it_have = map_char_freq_have.find(s2[i - k]);
        --it_have->second;

        // Get the required count for the character going out of the window
        auto it_req = map_char_freq_req.find(s2[i - k]);
        // If this character is not present in the required map, nothing is to be done here.
        if(it_req != end(map_char_freq_req))
        {
            // Update total_yes for the characters going out of the window
            if(it_have->second == it_req->second) ++total_yes;
            else if(it_have->second + 1 == it_req->second) --total_yes;
        }

        // If the count of the outgoing character reaches 0, remove it from the have map
        if(it_have->second == 0) map_char_freq_have.erase(it_have);

        // Update the have map with the character coming into the window
        it_have = map_char_freq_have.find(s2[i]);
        if(it_have == end(map_char_freq_have)) it_have = map_char_freq_have.insert({s2[i], 0}).first;
        ++it_have->second;

        // Get the required count for the character coming into the window
        it_req = map_char_freq_req.find(s2[i]);
        if(it_req != end(map_char_freq_req))
        {
            // Update total_yes count for the character coming to the window
            if(it_have->second == it_req->second) ++total_yes;
            else if(it_have->second == it_req->second + 1) --total_yes;
        }

        // If the size is the same and total_yes is the same as required, then return true
        if(size(map_char_freq_req) == size(map_char_freq_have) && total_yes == required_yes) return true;
    }

    return false;
}
