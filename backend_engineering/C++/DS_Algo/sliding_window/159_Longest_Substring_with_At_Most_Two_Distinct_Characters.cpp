#include<iostream>
#include<string>
#include<unordered_map>

using namespace std;

int lengthOfLongestSubstringTwoDistinct(string s) {
    // Inspired from https://leetcode.com/problems/max-consecutive-ones-iii/description/
    unordered_map<char,int> map_char_count;
    int max_length = 0;
    int left = 0;

    for(int i = 0; i < size(s); i++)
    {
        ++map_char_count[s[i]];

        while(left <= i && size(map_char_count) > 2)
        {
            --map_char_count[s[left]];
            if(map_char_count[s[left]] == 0) map_char_count.erase(s[left]);
            ++left;
        }

        max_length = max(max_length, i - left + 1);
    }

    return max_length;
}

