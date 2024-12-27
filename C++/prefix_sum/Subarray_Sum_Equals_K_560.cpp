#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        // So prefix_sum(i) is the prefix sum at index i.
        // If we know prefix_sum(j - 1) and subtract it with prefix_sum(i), we will get the
        // sum of numbers from index j to i in the array.
        // This means nums[0...i] - nums[0..j - 1] = nums[j..i].
        // Now, we are looking for a subarray that sums to k. This means nums[j..i] should k
        // for it to be a valid subarray. Here, j is 0 <= j <= i. This means many subarrays can
        // end at the ith index (starting from 0 to i - 1) with sum k.
        // This means perfix_sum(i) - prefix_sum(j - 1) = k => prefix_sum(i) - k = prefix_sum(j - 1).
        // Let's say we already have prefix_sum(j - 1) stored in a hash map. We can find prefix_sum(j - 1)
        // in O(1) operation. 
        // This prefix sum(j - 1) is a cumulative sum and can be stored in a hash table.
        // So there are 4 main steps here:
        // 1. Calculate prefix sum at index i.
        // 2. Get prefix_sum(i) - k count from hashmap.
        // 3. If present in the hashmap, increase the global count variable with the count from the hash map.
        // 4. Add this prefix to the hashmap.

        int count = 0;
        int prefix_sum = 0;
        // map to store prefix sum found and its count
        unordered_map<int,int> map_prefix_sum_j_count;

        // When j corresponds to an emtpy array i.e. when whole array is being considered as a subarray
        map_prefix_sum_j_count[0] = 1;

        for(int i = 0; i < size(nums); i++)
        {
            // Calculate prefix_sum(i)
            prefix_sum += nums[i];

            // Find if we already have prefix_sum(j - 1) i.e prefix_sum(i) - k in the hash table and accordingly
            // increase the count of subarray that sums to k
            // update local answer
            if(map_prefix_sum_j_count.find(prefix_sum - k) != end(map_prefix_sum_j_count))
                count += map_prefix_sum_j_count[prefix_sum - k];

            // Add my prefix as well to the hash map if not present.
            // Else, increase the count.
            // This will be used by manager above me.
            ++map_prefix_sum_j_count[prefix_sum];
        }

        return count;
    }
};