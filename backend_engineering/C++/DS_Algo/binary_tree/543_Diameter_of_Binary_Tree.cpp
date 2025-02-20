class Solution {
    int helper(TreeNode *root, int &max_diameter){
        if(root->left == nullptr && root->right == nullptr) return 0;

        int my_diameter = 0;
        int left_height = 0;
        if(root->left != nullptr){
            left_height = helper(root->left, max_diameter);
            my_diameter += left_height + 1;
        }
        int right_height = 0;
        if(root->right != nullptr){
            right_height = helper(root->right, max_diameter);
            my_diameter += right_height + 1;
        }

        max_diameter = max(max_diameter, my_diameter);
        
        return max(left_height, right_height) + 1;
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int max_diameter = 0;
        if(root != nullptr) helper(root, max_diameter);
        return max_diameter;
    }
};