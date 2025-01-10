#include <vector>
#include <deque>

using namespace std;


vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    // We will use deque to maintain the max element in a window
    // Why? Because we cannot access every location in a max heap, deletion and insertion will be done in log K.
    // Also, in the max heap, we will have elements that are not needed at all.
    // Deque can be used in this case. We have seen cases of using deque to maintain max and min in O(1)
    // amortized time.
    deque<int> dq;
    vector<int> r(size(nums) - k + 1);

    // Base case
    for(int i = 0; i < k; i++)
    {
        // We want to maintain the max element as the deque. Hence,
        // if we find an element less than the current element at the back, we will keep popping back
        // the element and then insert the index
        while(!empty(dq) && nums[dq.back()] < nums[i]) dq.pop_back();
        // Insert the index.
        dq.push_back(i);
    }

    // Add to the result
    r[0] = nums[dq.front()];

    for(int i = k; i < size(nums); i++)
    {
        //Let's take care of the index going out of the current window.
        // The front of the deque will have the maximum element and if applicable
        // the element going out of the window.
        if(dq.front() == i - k) dq.pop_front();
        // If the back of the deque element is smaller than the element at the current index, it can 
        // be eliminated (since they are now used to be kept in the deque).
        // Hence, let's keep popping up until the deque is empty or the element at the back is greater than
        // or equal to the element at the current index.
        while(!empty(dq) && nums[dq.back()] < nums[i]) dq.pop_back();
        //Let's insert the current index in the deque.
        dq.push_back(i);
        // Add to the result.
        r[i - k + 1] = nums[dq.front()];
    }

    return r;
}
