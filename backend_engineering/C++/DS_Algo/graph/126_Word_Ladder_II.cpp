#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// NOTE: optimize this using indices to reduce memory footprint

class Solution {
    bool is_adjecent(const string &word1, const string &word2){
        if(size(word1) != size(word2)) return false;
        
        int diff_count = 0;
        
        for(auto i = 0; i < size(word1); i++){
            if(word1[i] != word2[i]) ++diff_count;
        }
        
        return diff_count == 1 ? true : false;
    }

    void helper(const string &start_word, const string &target_word, const vector<string> &words,
        vector<vector<string>> &ans){
    unordered_set<string> words_set(begin(words), end(words));    
    unordered_map<string, int> visited_distance;
    
    int min_len = -1;
    queue<vector<string>> q;
    q.push({start_word});
    visited_distance[start_word] = 1;
    
    while(!empty(q)){
        auto current_path = q.front();
        q.pop();
        string current_word = current_path.back();
        
        if(current_word == target_word){
            if(min_len != -1 || size(current_path) <= min_len){
                min_len = size(current_path);
                ans.emplace_back(current_path);
            }
        }
        
        if(min_len != -1 && size(current_path) > min_len) continue;
        
        for(const auto &word : words){
            if(is_adjecent(current_word, word) == false) continue;
            
            if(visited_distance.find(word) == end(visited_distance) || 
                visited_distance[word] >= size(current_path) + 1){
                auto next_path = current_path;
                next_path.emplace_back(word);
                
                q.push(next_path);
                visited_distance[word] = size(next_path);
            }
        }
    }
}
public:
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<string>> ans;

        helper(beginWord, endWord, wordList, ans);

        return ans;
    }
};