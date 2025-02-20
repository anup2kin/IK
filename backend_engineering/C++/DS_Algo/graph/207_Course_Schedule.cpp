#include<iostream>
#include<vector>

using namespace std;

class Solution {
public:
    bool canFinish(int start_course, const vector<vector<int>> &adj_list, vector<bool> &is_visited,
        vector<int> &departure_time, int &timestamp)
    {
        is_visited[start_course] = true;

        for(auto &pre_req_course : adj_list[start_course])
        {
            if(is_visited[pre_req_course] == false)
            {
                if(canFinish(pre_req_course, adj_list, is_visited, departure_time, timestamp) == false) return false;
            }
            else if(departure_time[pre_req_course] == -1) return false;
        }
        
        departure_time[start_course]= timestamp++;
        return true;
    }
    
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) 
    {
        vector<vector<int>> adj_list(numCourses);
        for(auto &prereq:prerequisites)
            adj_list[prereq[0]].push_back(prereq[1]);

        int timestamp = 0;
        vector<bool> is_visited(numCourses, false);
        vector<int> departure_time(numCourses, -1);

        for(int course = 0; course < numCourses; course++)
        {
            if(is_visited[course] == true) continue;
            if(canFinish(course, adj_list, is_visited, departure_time, timestamp) == false) return false;
        }

        return true;
    }
};