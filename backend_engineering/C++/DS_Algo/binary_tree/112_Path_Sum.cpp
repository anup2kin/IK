class Solution {
public:
    void helper(TreeNode *node, int &target_sum, bool &has_path_sum){
        target_sum -= node->val;

        if(node->left == nullptr && node->right == nullptr){
            if(target_sum == 0) has_path_sum = true;
        }
        else{
            if(node->left != nullptr){
                helper(node->left, target_sum, has_path_sum);
                if(has_path_sum == true) return;
            }

            if(node->right != nullptr){
                helper(node->right, target_sum, has_path_sum);
                if(has_path_sum == true) return;
            }
        }

        target_sum += node->val;
    }

    bool hasPathSum(TreeNode* root, int targetSum) {
        if(root == nullptr) return false;

        bool has_path_sum = false;
        helper(root, targetSum, has_path_sum);
        return has_path_sum;
    }
};