#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        // First solve https://leetcode.com/problems/subarray-sum-equals-k/description/
        // Then solve https://leetcode.com/problems/subarray-sums-divisible-by-k/description/
        // This is in the same pattern. Instead of storing count in the hash map, we need to store
        // the minimum index (i.e. the first index where that prefix sum was seen)

        // Variable to keep track of maximum lenght seen so far with sum up to k
        int max_length = 0;
        // Variable to keep calculating running sum.
        long long prefix_sum = 0;
        // Map to keep track of prefix sum and at what index it was seen first.
        unordered_map<long long,int> map_prefix_sum_min_idx;
        // Base case when the left yellow part or prefix_sum(j - 1) when j is 0 i.e. empty array.
        map_prefix_sum_min_idx[0] = -1;

        for(int i = 0; i < size(nums); i++)
        {
            prefix_sum += nums[i];

            // Check if prefix_sum(i) - k = prefix(j - 1) is in the hash map
            auto it = map_prefix_sum_min_idx.find(prefix_sum - k);
            // If found in the hash map, update new max_length
            if(it != end(map_prefix_sum_min_idx))
                max_length = max(max_length, i - it->second);
            
            // Now update the hash map with this prefix sum only if this prefix sum has not been
            // seen yet. This will ensure the minimum index value where this prefix was seen and
            // hence will help in calculating the maximum length of the subarray
            if(map_prefix_sum_min_idx.find(prefix_sum) == end(map_prefix_sum_min_idx))
                map_prefix_sum_min_idx.insert({prefix_sum, i});
        }

        return max_length;
    }
};
