#include<string>
#include<unordered_map>

using namespace std;

string minWindow(string s, string t) 
{
    // This problem is similar to https://leetcode.com/problems/permutation-in-string/description/.
    // In that problem the window was fixed, whereas in this case window can be variable.
    int m = size(s);
    int n = size(t);

    if(m < n) return "";

    unordered_map<char,int> map_req;
    unordered_map<char,int> map_have;
    int total_yes_req = 0;
    int total_yes_have = 0;

    for(int i = 0; i < n; i++) ++map_req[t[i]];
    total_yes_req = size(map_req);

    int left = 0;
    int global_answer_index = -1;
    int global_answer_length = numeric_limits<int>::max();

    for(int i = 0; i < m; i++)
    {
        // Lets handle the character coming into this variable window.
        // If this character is not in the required map, ignore it and move to next
        // character
        auto it_req = map_req.find(s[i]);
        if(it_req == end(map_req)) continue;

        // Lets increase the count of this character in the have hash map
        auto it_have = map_have.find(s[i]);
        if(it_have == end(map_have)) it_have = map_have.insert({s[i], 1}).first;
        else ++it_have->second;

        // Lets increase total yes count if the count now in have for this character is same
        // as in required.
        if(it_have->second == it_req->second) ++total_yes_have;

        // Now begin a manager for index i, my job is to find minimum length that covers
        // all the required characters with required frequency.
        while(left <= i && total_yes_have == total_yes_req)
        {
            // At my index, i have required number of characters with required frequency. Hence,
            // lets update the minimum length and the index
            if(global_answer_length > i - left + 1)
            {
                global_answer_length = i - left + 1;
                global_answer_index = left;
            }

            // Lets decrease the window size by moving left towards right along with adjusting
            // the character frequency in the have hash map
            auto it_req_now = map_req.find(s[left]);
            if(it_req_now != end(map_req))
            {
                auto it_have_now = map_have.find(s[left]);
                --it_have_now->second;
                // If moving this out from the window will make the frequency less than required,
                // we need to reduce the total yes count
                if(it_have_now->second + 1 == it_req_now->second) --total_yes_have;
            }
            
            ++left;
        }
    }

    if(global_answer_index == -1) return "";
    else return s.substr(global_answer_index, global_answer_length);
}