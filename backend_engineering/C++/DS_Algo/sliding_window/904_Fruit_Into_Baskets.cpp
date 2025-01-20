#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

int totalFruit(vector<int>& fruits) {
    // Variable to keep track of type of fruit and its count
    unordered_map<int,int> map_fruit_type_count;
    int max_fruits_count = 0;
    // Start of the tree from where basket is being filled.
    int left = 0;

    for(int i = 0; i < size(fruits); i++)
    {
        // Increase the count for the fruit type
        ++map_fruit_type_count[fruits[i]];

        // If we now have more than 2 fruit types, we need to drop one type completely.
        while(left <= i && size(map_fruit_type_count) > 2)
        {
            // Drop the fruit type
            --map_fruit_type_count[fruits[left]];
            // If the one fruit type is dropped completely, we need to take it out of the map.
            if(map_fruit_type_count[fruits[left]] == 0) map_fruit_type_count.erase(fruits[left]);
            ++left;
        }

        // Maximum fruits collected so far.
        max_fruits_count = max(max_fruits_count, i - left + 1);
    }

    return max_fruits_count;
}