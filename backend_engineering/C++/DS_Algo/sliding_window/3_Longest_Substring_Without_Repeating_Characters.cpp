#include<iostream>
#include<string>
#include<unordered_map>

using namespace std;

int lengthOfLongestSubstring(string s) {
    // Inspired from https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/description/
    unordered_map<char,int> map_char_count;
    int max_length = 0;
    int left = 0;

    for(int i = 0; i < size(s); i++)
    {
        ++map_char_count[s[i]];

        while(left <= i && map_char_count[s[i]] > 1)
        {
            --map_char_count[s[left]];
            ++left;
        }

        max_length = max(max_length, i - left + 1);
    }

    return max_length;
}