#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int prefix_mod = 0;
        unordered_map<int,int> map_mod_min_idx;
        map_mod_min_idx[0] = -1;

        for(int i = 0; i < size(nums); i++)
        {
            prefix_mod = (prefix_mod + nums[i]) % k;

            auto it = map_mod_min_idx.find(prefix_mod);
            if(it != end(map_mod_min_idx))
                if(i - it->second >= 2) return true;

            if(it == end(map_mod_min_idx)) map_mod_min_idx[prefix_mod] = i;
        }

        return false;
    }
};