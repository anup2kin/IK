#include <vector>
#include <set>

using namespace std;

vector<double> medianSlidingWindow(vector<int>& nums, int k) {
    if(k > size(nums)) return vector<double>{};

    vector<double> r(size(nums) - k + 1);

    auto comp_for_set = [&](const auto &idx1, const auto &idx2)
    {
        if(nums[idx1] < nums[idx2]) return true;
        // We need to handle collision, else the function will return false
        // and the same value, but a different index will not get inserted.
        else if(nums[idx1] == nums[idx2] && idx1 < idx2) return true;
        else return false;
    };

    // We cannot use the max heap and min heap concepts here since we won't be able to delete the 
    // outgoing number from max or min heap if they are not at the top.
    // We can use a binary tree representable to achieve max and min heap and will be able to delete
    // the outgoing number easily.
    // To store the left part of the window
    set<int, decltype(comp_for_set)> left_part_window(comp_for_set);
    // To store right part of the window
    set<int, decltype(comp_for_set)> right_part_window(comp_for_set);
    for(int i = 0; i < k; i++)
    {
        if(size(left_part_window) == 0) left_part_window.insert(i);
        else if(nums[*rbegin(left_part_window)] < nums[i]) right_part_window.insert(i);
        else left_part_window.insert(i);

        if(size(left_part_window) < size(right_part_window))
        {
            left_part_window.insert(*begin(right_part_window));
            right_part_window.erase(begin(right_part_window));
        }
        else if(size(left_part_window) > size(right_part_window) + 1)
        {
            right_part_window.insert(*rbegin(left_part_window));
            left_part_window.erase(*rbegin(left_part_window));
        }
    }

    if(k % 2 == 1) r[0] = nums[*rbegin(left_part_window)];
    else r[0] = (static_cast<double>(nums[*rbegin(left_part_window)]) 
        + static_cast<double>(nums[*begin(right_part_window)])) / 2.0;

    for(int i = k; i < size(nums); i++)
    {
        // Erase outgoing index
        auto it_left = left_part_window.find(i - k);
        if(it_left != end(left_part_window)) left_part_window.erase(i - k);
        else right_part_window.erase(i - k);

        // **Insert incoming index based on last media**
        if(nums[i] <= r[i - k]) left_part_window.insert(i);
        else right_part_window.insert(i);

        // Balance max and min heap
        if(size(left_part_window) < size(right_part_window))
        {
            left_part_window.insert(*begin(right_part_window));
            right_part_window.erase(begin(right_part_window));
        }

        if(size(left_part_window) > size(right_part_window) + 1)
        {
            right_part_window.insert(*rbegin(left_part_window));
            left_part_window.erase(*rbegin(left_part_window));
        }

        if(k % 2 == 1) r[i - k + 1] = nums[*rbegin(left_part_window)];
        else r[i - k + 1] = (static_cast<double>(nums[*rbegin(left_part_window)]) 
            + static_cast<double>(nums[*begin(right_part_window)])) / 2.0;
    }

    return r;
}
