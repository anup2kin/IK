#include <vector>

using namespace std;

class Solution {
    const int MOD = 1e9 + 7;
public:
    int numOfSubarrays(vector<int>& arr) {
        // Inspired from https://leetcode.com/problems/maximum-size-subarray-sum-equals-k/description/
        // Brute force approach. 
        // Let's start with index 0. If the number at index 0 is odd, let's increase the number of odd arrays by 1.
        // Now, let's add the number at index 1. If the sum is odd, then we should increase the number of odd
        // arrays by 1. We need to do this until we reach the end of the array. Now, after this, we have the number
        // of subarrays that sum to an odd number involving index 0.
        // Let's do the above, but now start from index 1 to find all the sub-arrays involving index 1. But notice
        // that we are calculating the running sum again, which we did in step 1. Finding a sum involving a starting
        // index with others will result in order O(n) for each index. We can cut this down if the running sum is
        // calculated just once. How will this help? Well, let's say we are at index i, and we want to know the sum
        // from index j to i (where j <= i); we can do prefix_sum(i) - prefix_sum(j - 1). This will reduce the lookup
        // to O(1).
        // Now, following the same path, let's ask a question. How is index i going to contribute to the total result?
        // Well, if the prefix_sum(i) is even, then since prefix_sum(j...i) has to be odd, prefix_sum(j - 1) will be
        // odd as well. This means that if index i knows how many odd subarrays are there from index i - 1, it can be
        // part of those odd numbers of arrays.
        // If prefix_sum(i) is odd, then since prefix_sum(j...i) has to be odd, prefix_sum(j - 1) will be even. 
        
        int count = 0;
        long long prefix_sum = 0;
        // If prefix is empty and suffix adds to odd, the event count needs to be 1.
        // Count of an even prefixes at an index i
        int even_count = 1;
        // Count of an odd prefixes at an index i
        int odd_count = 0;

        for(int i = 0; i < size(arr); i++)
        {
            prefix_sum = prefix_sum + arr[i];

            // If prefix_sum is even, then i can be part of all the odd arrays
            if(prefix_sum % 2 == 0) count += odd_count;
            // If prefix_sum is odd, then i can  be part of all the even arrays
            else count += even_count;

            count = count % MOD;

            // Now add this prefix_sum array to odd or even sub array count.
            if(prefix_sum % 2 == 0) ++even_count;
            else ++odd_count;
        }

        return count;
    }
};