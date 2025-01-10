#include <vector>
#include <limits>

using namespace std;

int minSubArrayLen(int target, vector<int>& nums) {
    int min_len = numeric_limits<int>::max();
    int window_sum = 0;
    // Start of variable length window
    int left = 0;

    for(int i = 0; i < size(nums); i++)
    {
        window_sum += nums[i];

        // Adjust left side of the window if needed until it voilates the boundary condition
        while(left <= i && window_sum >= target)
        {
            // Compute local answer
            min_len = min(min_len, i - left + 1);
            // Reduce the window from the left
            window_sum -= nums[left];
            ++left;
        }
    }

    if(min_len == numeric_limits<int>::max()) return 0;
    else return min_len;
}
