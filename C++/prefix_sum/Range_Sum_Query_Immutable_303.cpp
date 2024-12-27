#include <vector>

using namespace std;

class NumArray {
    vector<int> prefix_sums;
public:
    NumArray(vector<int>& nums) {
        // We know that many queries will come later; hence, we can do some preprocessing on the
        // input to speed up the response to them. This approach is similar to the cases where we
        // need to do presorting to respond to queries faster in the future.
        // So, here we are enhancing the input to compute and store some derived data and then we
        // we are conquering it.
        // Above method is called Enhance-and-conquer.
        // Hence, prefix some is an example of Enhance-and-conquer.
        prefix_sums.resize(size(nums));

        int prefix_sum = nums[0];
        prefix_sums[0] = nums[0];

        for(int i = 1; i < size(nums); i++)
        {
            prefix_sum += nums[i];
            prefix_sums[i] = prefix_sum;
        }
    }
    
    int sumRange(int left, int right) {
        int prefix_sum_before_left = 0;

        if(left - 1 >= 0) prefix_sum_before_left = prefix_sums[left - 1];

        return prefix_sums[right] - prefix_sum_before_left;
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(left,right);
 */