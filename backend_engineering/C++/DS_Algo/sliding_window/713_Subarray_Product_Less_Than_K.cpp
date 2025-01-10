#include <vector>

using namespace std;

int numSubarrayProductLessThanK(vector<int>& nums, int k) {
    // Brute force solution 1: We can choose i and j in nC2 ways and then calculate the product of each
    // subarray to find the count of subarrays whose product is less than k. This algorithm will take
    // O(n^2) to find all the subarrays and then the O(n) operation to find a product of each subarray.
    // Hence, this algorithm will be O(n^3) algorithm.
    // The above algorithm can be optimized by adopting the prefix-product approach. With this approach,
    // the time complexity will be O(n2).
    // Now, let's ask a question at index i. What if index i knows that there is a left pointer from where
    // product of elements till i - 1 is less than k? Well, if i knows this answer, then it can multiply
    // itself to the product calculated by i - 1, and if the product now is less than k, then the total
    // number of subarrays that has product less than k and end at i will be equal to the i - left + 1.
    // All the indices can use this same approach. Now, if index i finds that the product is greater than
    // or equal to k after multiplying itself, it's his job to find the right-left pointer from where the
    // product will be less than k ending at index i.

    int count = 0;
    int window_product = 1;
    int left = 0;

    for(int i = 0; i < size(nums); i++)
    {
        window_product = window_product * nums[i];

        // If the window product is greater or equal to k, then this manager has to Take
        // care of adjusting the left pointer so that the product of the numbers in the window
        // becomes less than k.
        while(left <= i && window_product >= k)
        {
            // Take care of the element going out of the window
            window_product = window_product / nums[left];
            // Move the window towards the left
            ++left;
        }

        // How many subarrays with products less than k and end at index i?
        // Add this to the global count.
        count += (i - left + 1);
    }

    return count;
}
