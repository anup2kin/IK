#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
    void helper(TreeNode *root, vector<vector<int>> &ans){
        bool left_to_right = true;
        queue<TreeNode*> q;
        q.push(root);

        while(!empty(q)){
            int size_q = size(q);
            ans.emplace_back();

            for(int i = 0; i < size_q; i++){
                auto node = q.front();
                q.pop();

                ans.back().emplace_back(node->val);

                if(node->left != nullptr) q.push(node->left);
                if(node->right != nullptr) q.push(node->right);
            }

            if(left_to_right == true) left_to_right = false;
            else{
                reverse(begin(ans.back()), end(ans.back()));
                left_to_right = true;
            }
        }
    }
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if(root != nullptr) helper(root, ans);
        return ans;
    }
};