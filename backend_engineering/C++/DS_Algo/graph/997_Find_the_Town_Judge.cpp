#include <iostream>
#include <vector>

using namespace std;

/*
    solution works by first creating two vectors, in_degree and out_degree. 
    The in_degree vector keeps track of the number of people who trust a given person, 
    while the out_degree vector keeps track of the number of people who a given person trusts.
    We then iterate over the trust vector and update the in_degree and out_degree vectors accordingly.
    Finally, we iterate over the in_degree vector and look for a person who has an in_degree of N - 1 
    (which means that everyone trusts them) and an out_degree of 0 (which means that they trust no one). 
    If we find such a person, we return their index. Otherwise, we return -1.
*/
class Solution {
public:
    int findJudge(int n, vector<vector<int>>& trust) 
    {
        vector<int> in_degree(n + 1, 0);
        vector<int> out_degree(n + 1, 0);

        for(auto edge:trust)
        {
            ++out_degree[edge[0]];
            ++in_degree[edge[1]];
        }

        for(int i = 1; i <= n; i++)
            if(out_degree[i] == 0 && in_degree[i] == n - 1) return i;

        return -1;
    }
};