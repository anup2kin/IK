class Solution {
public:

    /*
    We are given an array with numbers in non-decreasing order.
    Inorder traversal of a BST gives us elements in non-decreasing order.
    In inorder traversal, we keep moving (i.e. visit) to the left until we hit the leaf node or null left node.
    Then, we return and visit the parent node and then go to the right node.
    
    This pattern means the traversal will have the mid element of the sorted array as the root node, and the left subtree 
    will be constructed using the left part of the sorted array ending right before the sorted array's midway. 
    Similarly, the right subtree will be constructed using the right part of the sorted array starting right after the mid 
    and ending to the end of the array.
*/
    
    
    TreeNode* sorted_list_to_bst(ListNode *&node, int start, int end)
    {
        if(start > end) return nullptr;

        int mid = start + (end - start)/2;
        TreeNode *left_node = sorted_list_to_bst(node, start, mid - 1);
        TreeNode *tree_node = new TreeNode(node->val);
        
        tree_node->left = left_node;
        node = node->next;
        
        tree_node->right = sorted_list_to_bst(node, mid + 1, end);

        return tree_node;
    }

    TreeNode* sortedListToBST(ListNode* head) 
    {
        if(head == nullptr) return nullptr;

        int size_list = 0;
        for(ListNode *node = head; node != nullptr; node = node->next)
            ++size_list;
        
        return sorted_list_to_bst(head, 0, size_list - 1);
    }
};