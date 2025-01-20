#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

int subarraysWithKDistinct(vector<int>& nums, int k) {
    // The brute force solution will be to start from the first element and keep moving towards the
    // right and maintain a hash table to keep count of each number. Once the hash table size reaches
    // k, we will increase the global answer by 1. The global answer will be increased till the point
    // where the size of the hash table is exactly k. Once it becomes greater than k, we can now start
    // from index 1 and follow the same procedure as done for 1st element. This will be the O(n^2)
    // algorithm.
    // Can we optimize this to an O(n) solution?
    // Let's assume we are at the ith index. If standing at the ith index, how can the 'ith manager'
    // calculate the number of subarrays with exactly k distinct elements in O(1) time? Let's see what
    // the '(i-1) th manager' can provide information to the 'ith manager '. The '(i-1) th manager' will
    // have three possibilities at its index. 
    // 1. It will have subarrays for which the number of distinct elements will be >k
    // 2. It will have subarrays for which the number of distinct elements will be =k
    // 3. It will have subarrays for which the number of distinct elements will be <k
    // So how many good subarrays are there including i-1th index? A 'good subarray' is a subarray that
    // contains exactly k distinct elements. It will be (index after which the number of distinct elements
    // are < k - index after which the number of distinct elements are = k). Let's call the index after
    // which the number of distinct elements is k as 'left_greater_equal', emphasizing the index right
    // after which the number of distinct elements is exactly equal to k. Also, let's call the index after
    // which the number of distinct elements is less than k as 'left_equal_less', emphasizing the index right
    // after which the number of distinct elements is less than k.
    // Now once 'ith manager' gets this information, it needs to adjust 'left_greater_equal' and 'left_equal_less'.
    // Once it is adjusted, it can find the answer to the question 'how many good subarrays are there that end
    // at index i' in O(1) time.
    
    // Hash map to maintain the number and its frequency till the point where the number of distinct elements
    // as equal or less than k. If it is equal to k, it will be adjusted to less than k
    unordered_map<int,int> map_el;
    // Hash map to maintain the number and its frequency till the point where the number of distinct elements are
    // greater or equal to k. If it is greater than k, it will be adjusted to equal to k
    unordered_map<int,int> map_ge;
    
    // Index from where the number of distinct elements is less than k. If equal to k, it will be adjusted.
    int left_el = 0;
    // Index after which the number of distinct elements is k. If more than k, it will be adjusted.
    // In another words, this is the index before which the number of distinct elements is greater than k.
    int left_ge = 0;
    
    int count = 0;
    for(int i = 0; i < size(nums); i++)
    {
        // Add the incoming number to the hash map containing distinct numbers starting from the index equal to or less
        // to k distinct numbers
        ++map_el[nums[i]];
        // Adjust the index for equal to or less than k distinct numbers based on the hash map containing distinct
        // numbers equal to or less than k distinct numbers
        while(left_el <= i && size(map_el) == k)
        {
            --map_el[nums[left_el]];
            if(map_el[nums[left_el]] == 0) map_el.erase(nums[left_el]);
            ++left_el;
        }

        // Add the incoming number to the hash map containing distinct nubmers starting from the index greater than or equal
        // to k distinct nubmers
        ++map_ge[nums[i]];
        // Adjust the index for greater than or equal to k distinct numbers based on the hash map containing distinct
        // numbers greater than or equal to k distinct numbers
        while(left_ge <= i && size(map_ge) > k)
        {
            --map_ge[nums[left_ge]];
            if(map_ge[nums[left_ge]] == 0) map_ge.erase(nums[left_ge]);
            ++left_ge;
        }

        // Add the number of good subarrays that ends at i to the global answer.
        count += left_el - left_ge;
    }

    return count;
}