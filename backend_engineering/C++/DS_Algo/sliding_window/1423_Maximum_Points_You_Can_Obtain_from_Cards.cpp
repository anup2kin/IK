#include<iostream>
#include<vector>
#include<numeric>

using namespace std;

int maxScore(vector<int>& cardPoints, int k) {
    // In one step, we can take one card from the beginning or from the end of the row. We can to take
    // exactly k cards. This means we should be left with size(cardPoints) - k elements from the
    // cardPoints array. This means we need to find a subarray of size size(cardPoints) - k, which has
    // minimum some possible to maximize the total points for the k cards.
    // We can use fixed sliding window pattern here.       

    // Detemine window size
    int window_size = size(cardPoints) - k;
    int window_points = accumulate(begin(cardPoints), begin(cardPoints) + window_size, 0);;
    int min_points_so_far = window_points;
    
    // Initialize the min_points_so_far to the value of first window.
    min_points_so_far = window_points;

    for(int i = window_size; i < size(cardPoints); i++)
    {
        // Take care of card coming into the window
        window_points += cardPoints[i];
        // Take care of card going out of the window.
        window_points -= cardPoints[i - window_size];
        // Update min points so far
        min_points_so_far = min(min_points_so_far, window_points);
    }

    // The max points using k card will be sum of all elements in cardPoints - min_points_so_far
    return accumulate(begin(cardPoints), end(cardPoints), 0) - min_points_so_far;
}