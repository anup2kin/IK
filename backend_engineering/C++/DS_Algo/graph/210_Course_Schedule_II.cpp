#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool findOrder(int course, const vector<vector<int>> &adj_list, vector<bool> &is_visited,
        vector<int> &departure_time, int &timestamp, vector<int> &course_order)
    {
        is_visited[course] = true;

        for(auto &pre_req : adj_list[course])
        {
            if(is_visited[pre_req] == false)
            {
                if(findOrder(pre_req, adj_list, is_visited, departure_time, timestamp, course_order) == false) return false;
            }
            else if(departure_time[pre_req] == -1) return false;
        }

        departure_time[course] = timestamp++;
        course_order.push_back(course);

        return true;
    }
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) 
    {
        vector<vector<int>> adj_list(numCourses);
        for(auto &pre_req:prerequisites)
            adj_list[pre_req[0]].push_back(pre_req[1]);

        vector<bool> is_visited(numCourses, false);
        vector<int> departure_time(numCourses, -1);
        int timestamp = 0;
        vector<int> course_order;
        for(int course = 0; course < numCourses; course++)
        {
            if(is_visited[course] == true) continue;
            
            if(findOrder(course, adj_list, is_visited, departure_time, timestamp, course_order) == false)
                return vector<int>{};
        }

        return course_order;
    }
};