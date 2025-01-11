#include <vector>

using namespace std;

int longestOnes(vector<int>& nums, int k) {
    int max_length = 0;
    int window_zeros_count = 0;
    int left = 0;

    for(int i = 0; i < size(nums); i++)
    {
        // Increase the count of zeros that can be flipped to 1
        if(nums[i] == 0) ++window_zeros_count;
        
        // Number of zeros now is greater than k and hence we need to adjust left
        // pointer to the appropriate index
        while(left <= i && window_zeros_count > k)
        {
            if(nums[left] == 0) --window_zeros_count;
            ++left;
        }

        // Since we are here, number of zeros in this window is <= k.
        // Calculate length of subarray that can have continuous 1s after flipping
        // window_zeros_count 0s to 1.
        max_length = max(max_length, i - left + 1);
    }

    return max_length;
}
