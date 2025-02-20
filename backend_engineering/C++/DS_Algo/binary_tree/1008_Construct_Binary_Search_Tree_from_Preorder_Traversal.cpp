class Solution {
public:
    TreeNode* helper(const vector<int> &preorder, int min_val, int max_val, int &idx)
    {
        if(idx == size(preorder)) return nullptr;

        int val = preorder[idx];
        if(val < min_val || val > max_val) return nullptr;
        
        TreeNode *root = new TreeNode(val);
        idx = idx + 1;

        root->left = helper(preorder, min_val, val, idx);
        root->right = helper(preorder, val, max_val, idx);

        return root;
    }
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        int idx = 0;
        return helper(preorder, numeric_limits<int>::min(), numeric_limits<int>::max(), idx);
    }
};