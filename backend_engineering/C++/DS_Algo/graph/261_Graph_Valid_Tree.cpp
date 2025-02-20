#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool dfs(int source, const vector<vector<int>> &adj_list, vector<bool> &visited, vector<int> &parent)
    {
        visited[source] = true;

        for(auto neighbor : adj_list[source])
        {
            if(visited[neighbor] == false)
            {
                parent[neighbor] = source;
                if(dfs(neighbor, adj_list, visited, parent) == false) return false;
            }
            else if(neighbor != parent[source]) return false;
        }

        return true;
    }

    bool bfs(int source, const vector<vector<int>> &adj_list, vector<bool> &visited, vector<int> &parent){
        queue<int> q;
        q.push(source);
        visited[source] = true;

        while(!empty(q)){
            int vertex = q.front();
            q.pop();

            for(const auto &n : adj_list[vertex]){
                if(visited[n] == false){
                    q.push(n);
                    visited[n] = true;
                    parent[n] = vertex;
                }
                else if(n != parent[vertex]){
                    return false;
                }
            }
        }

        return true;
    }

    bool validTree(int n, vector<vector<int>>& edges) {
        vector<vector<int>> adj_list(n);
        for(auto &edge : edges)
        {
            adj_list[edge[0]].emplace_back(edge[1]);
            adj_list[edge[1]].emplace_back(edge[0]);
        }

        int componenet = 0;
        vector<bool> visited(n, false);
        vector<int> parent(n, -1);
        for(int vertex = 0; vertex < n; vertex++)
        {
            if(visited[vertex] == true) continue;
            ++componenet;
            if(componenet > 1) return false;
            if(bfs(vertex, adj_list, visited, parent) == false) return false;
        }

        return true;
    }
};