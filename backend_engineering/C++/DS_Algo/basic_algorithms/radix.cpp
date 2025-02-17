#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void bucket_sort(vector<int> &nums, int division){
    vector<vector<int>> buckets(10);

    for(auto num : nums){
        int idx = (abs(num) / division) % 10;
        buckets[idx].emplace_back(num);
    }

    vector<int> negatives;
    vector<int> positives;

    for(auto bucket : buckets){
        for(auto num : bucket){
            if(num < 0) negatives.emplace_back(num);
            else positives.emplace_back(num);
        }
    }

    nums.clear();
    reverse(begin(negatives), end(negatives));
    nums.insert(nums.end(), negatives.begin(), negatives.end());
    nums.insert(nums.end(), positives.begin(), positives.end());
}

void radix_sort(vector<int> &nums){
    auto comp_abs = [](int n1, int n2){
        if(abs(n1) < abs(n2)) return true;
        else return false;
    };

    int abs_max_element = *max_element(begin(nums), end(nums), comp_abs);
    int division = 1;
    while(abs_max_element != 0){
        abs_max_element /= 10;
        bucket_sort(nums, division);
        division *= 10;
    }
}

int main() {
    vector<int> nums = {170, 45, 75, -90, -802, 24, 2, 66};

    cout << "Before sorting: ";
    for (int num : nums) cout << num << " ";
    cout << endl;

    radix_sort(nums);

    cout << "After sorting: ";
    for (int num : nums) cout << num << " ";
    cout << endl;

    return 0;
}