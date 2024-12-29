#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int subarraysDivByK(vector<int>& nums, int k) {
        // Similar to https://leetcode.com/problems/subarray-sum-equals-k/description/
        // Can we compute a subarray that have sum divisible by k and ending at an index i?
        // We have A[j...i] = A[0...i] - A[0...j - 1]
        // Now, If A[j...i] is multiple of k, (A[0...i] - A[0...j - 1]) will also be multiple of k.
        // This also means, A[0...i] % k == A[0...j - 1] % k.
        // => prefix[i] % k = prefix[j - 1] % k i.e. remainder will be the same in both the cases.
        // Hence, we need to hash value based on the remainder of the prefix sum.

        int count = 0;
        // We need to keep track of prefix mod in this question instead of prefix sum
        int prefix_mod= 0;
        // Hash map containing remainder as key and count of prefixes having this remainder as value.
        unordered_map<int,int> map_prefix_mod_count;
        map_prefix_mod_count[0] = 1;

        for(int i = 0; i < size(nums); i++)
        {
            // Calculate prefix mod at index i and mod it by k.
            // By doing %, prefix sum value will remained capped at k - 1.
            // nums[i] can be negative taking mod of negative number will yeild negative number.
            // To map it correctly to k, we need to add k to it.
            prefix_mod = (prefix_mod + ((nums[i] % k) + k)) % k;

            // Find if hash map contains the prefix(i) % k
            if(map_prefix_mod_count.find(prefix_mod) != end(map_prefix_mod_count))
                count += map_prefix_mod_count[prefix_mod];
            
            // Add my prefix(i) % k to the hash map.
            ++map_prefix_mod_count[prefix_mod];
        }

        return count;
    }
};