#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

int maximumUniqueSubarray(vector<int>& nums) {
    // Solve https://leetcode.com/problems/longest-substring-without-repeating-characters/description/ first.
    unordered_map<int,int> map_num_count;
    int window_sum = 0;
    int max_sum = 0;
    int left = 0;

    for(int i = 0; i < size(nums); i++)
    {
        window_sum += nums[i];
        ++map_num_count[nums[i]];

        while(left <= i && map_num_count[nums[i]] > 1)
        {
            window_sum = window_sum - nums[left];
            --map_num_count[nums[left]];
            ++left;
        }

        max_sum = max(max_sum, window_sum);
    }

    return max_sum;
}