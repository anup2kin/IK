#include <vector>
#include <numeric>
using namespace std;

int numOfSubarrays(vector<int>& arr, int k, int threshold) {
    int count_of_subarrays = 0;

    // Base case
    double window_sum = accumulate(begin(arr), begin(arr) + k, 0);
    if(window_sum / k >= threshold) ++count_of_subarrays;

    for(int i = k; i < size(arr); i++)
    {
        // Work to be done by ith manager
        window_sum += arr[i];
        window_sum -= arr[i - k];
        if(window_sum / k >= threshold) ++count_of_subarrays;
    }

    return count_of_subarrays;
}