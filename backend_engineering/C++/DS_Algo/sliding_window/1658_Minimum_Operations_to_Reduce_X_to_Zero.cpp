#include <vector>
#include <numeric>

using namespace std;

int minOperations(vector<int>& nums, int x) {
    // Finding the number of operations means finding the elements from the beginning and/or end.
    // Now, these elements' sum should equal x. Since the sum of these elements should
    // be x, the sum of the rest of the subarray leaving these elements will be the sum of all
    // elements - x. It looks like the problem now is finding the subarray with a sum equal to the
    // sum of all elements - x with the maximum length possible. Size(nums) - size (sub-array with
    // sum (i...j) will give the minimum number of operations required.
    // A brute-force approach to solving this would be to find all the i and j and then find the
    // maximum length of the subarray. The brute force approach will be an O (n^3) solution that
    // could be optimized to O(n) using prefix sum. The prefix sum algorithm will use a hash table
    // to store the prefix sum and the index at which the prefix sum was found.
    // Note: We didn't use this approach for the previous problem with the prefix sum because the number in those
    // problems could be -ve as well; hence, we will have multiple points where the sum will be the same.
    // Let's think of this in terms of another decrease and conquer approach.
    // After removing the minimum elements (whose sums equal x), the total subarray sum is k. 
    // Now let's ask How the ith manager can contribute to the result. Let's assume that the ith manager
    // knows the sum of numbers from an index left, to the left of i, till i - 1. If ith manager adds
    // itself to this sum, there are 3 possibilities:
    // 1. Sum is still less than k. In this case ith manager just needs to pass on the information of
    //   total sum till ith index to i + 1 manager.
    // 2. Sum is equal to k. In this case ith manager can find the length of the subarray that sums to k.
    //   This length will be i - left + 1.
    // 3. Sum is greater than k.
    // In case of case 2 and 3, now it is ith manager's responsibility to find the appropriate position
    // for the left pointer, so the total sum of the subarray will be less than k at ith index.
    // Also, for case 2, ith manager will update maximum length of the subarray depending upon the value of i - left + 1.
    
    // It is possible that there are no subarrays possible. Also, it could be possible that all the elements need to be
    // removed so that they add to x. In this case, there will not be any subarray, and hence, the length will be 0.
    // We need to differentiate between the above 2 cases; hence, in the first case, we need to return -1.
    // Because of the above reasons, we need to keep the value of max_length to -1.
    int max_length = -1;
    long long window_sum = 0;
    int left = 0;
    long long target = accumulate(begin(nums), end(nums), 0) - x;

    for(int i = 0; i < size(nums); i++)
    {
        window_sum +=  nums[i];
	// The condition has > target since the boundary is "sum should not be greater than the target."
        while(left <= i && window_sum > target)
        {
            window_sum -= nums[left];
            ++left;
        }

        if(window_sum == target) max_length = max(max_length, i - left + 1);
    }

    if(max_length == -1) return -1;
    else return size(nums) - max_length;
}
