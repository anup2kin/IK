#include<vector>
#include<deque>

using namespace std;

int longestSubarray(vector<int>& nums, int limit) {
    // The absolute difference between any two elements should be less than or equal to the limit.
    // This also can be translated as the difference between the maximum and minimum element
    // in the subarray should be less than or equal to the limit.
    // The tricky part is to maintain all the elements in the sorted order so that
    // We can find the difference between max and min in that window in O(1). Another tricky part is
    // to update the max and min when an element is going out of the window and when
    // an element is coming into the window. This can be done by using a binary search tree with index
    // as key and sorting based on value.
    // Using a tree will be a log n operation for insertion/deletion. How can we speed this up more?
    // We can use a deque to maintain max and another deque to maintain min in the sliding window.
    // This is the same trick we used to find the maximum in a fixed sliding window problem.

    deque<int> max_dq;
    deque<int> min_dq;
    int max_length = 0;
    int left = 0;

    for(int i = 0; i < size(nums); i++)
    {
        //Insert in the max deque once the back of the deque contains a value greater than
        // at index i or it is empty
        while(!empty(max_dq) && nums[max_dq.back()] < nums[i]) max_dq.pop_back();
        max_dq.push_back(i);

        //Insert in the min deque once the back of the deque contains a value less than 
        // at index i or it is empty
        while(!empty(min_dq) && nums[min_dq.back()] > nums[i]) min_dq.pop_back();
        min_dq.push_back(i);


        // Check if absolute value is till <= limit
        while(left <= i && nums[max_dq.front()] - nums[min_dq.front()] > limit)
        {
            // Erase the element going out of the window.
            if(max_dq.front() == left) max_dq.pop_front();
            if(min_dq.front() == left) min_dq.pop_front();

            ++left;
        }

        max_length = max(max_length, i - left + 1);
    }

    return max_length;
}