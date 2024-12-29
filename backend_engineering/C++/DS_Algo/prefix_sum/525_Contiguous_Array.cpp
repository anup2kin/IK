#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    int findMaxLength(vector<int>& nums) {
        int max_len = 0;
        unordered_map<int,int> map_excess_deficiency_ones_min_idx;
        map_excess_deficiency_ones_min_idx[0] = -1;
        
        int count_one = 0;
        int count_zero = 0;
        for(int i = 0; i < size(nums); i++)   
        {
            if(nums[i] == 1) ++count_one;
            else ++count_zero;

            auto it = map_excess_deficiency_ones_min_idx.find(count_one - count_zero);
            if(it != end(map_excess_deficiency_ones_min_idx))
                max_len = max(max_len, i - it->second);
            
            it = map_excess_deficiency_ones_min_idx.find(count_one - count_zero);
            if(it == end(map_excess_deficiency_ones_min_idx))
                map_excess_deficiency_ones_min_idx[count_one - count_zero] = i;
        }

        return max_len;
    }
};