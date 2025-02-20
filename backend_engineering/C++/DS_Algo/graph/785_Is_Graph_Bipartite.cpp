#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /*
    bool bfs(int source_vertex, const vector<vector<int>> &graph, 
        vector<bool> &is_visited, vector<int> &parents, vector<int> &levels)
    {
        queue<int> q;
        is_visited[source_vertex] = true;
        q.push(source_vertex);

        while(!empty(q))
        {
            int vertex = q.front();
            q.pop();

            for(auto &neighbor:graph[vertex])
            {
                if(is_visited[neighbor] == false)
                {
                    is_visited[neighbor] = true;
                    parents[neighbor] = vertex;
                    levels[neighbor] = levels[vertex] + 1;

                    q.push(neighbor);
                }
                else if((neighbor != parents[vertex]) && (levels[neighbor] == levels[vertex]))
                        return true;
            }
        }

        return false;
    }
    bool isBipartite(vector<vector<int>>& graph) 
    {
        int node_count = size(graph);
        vector<bool> is_visited(node_count, false);
        vector<int> parents(node_count, -1);
        vector<int> levels(node_count, 0);

        for(int vertex = 0; vertex < node_count; vertex++)
        {
            if(is_visited[vertex] == true)
                continue;
            
            if(bfs(vertex, graph, is_visited, parents, levels) == true)
                return false;
        }

        return true;
    }
    */
    bool dfs(int source_vertex, const vector<vector<int>> &graph, 
        vector<bool> &is_visited, vector<int> &parents, vector<bool> &color)
    {
        is_visited[source_vertex] = true;

        for(auto &neighbor:graph[source_vertex])
        {
            if(is_visited[neighbor] == false)
            {
                is_visited[neighbor] = true;
                parents[neighbor] = source_vertex;
                color[neighbor] = !color[source_vertex];

                if(dfs(neighbor, graph, is_visited, parents, color) == true) return true;
            }
            else if((neighbor != parents[source_vertex]) && (color[neighbor] == color[source_vertex]))
                    return true;
        }

        return false;
    }
    bool isBipartite(vector<vector<int>>& graph) 
    {
        int node_count = size(graph);
        vector<bool> is_visited(node_count, false);
        vector<int> parents(node_count, -1);
        vector<bool> color(node_count, false);

        for(int vertex = 0; vertex < node_count; vertex++)
        {
            if(is_visited[vertex] == true) continue;
            
            if(dfs(vertex, graph, is_visited, parents, color) == true) return false;
        }

        return true;
    }
};