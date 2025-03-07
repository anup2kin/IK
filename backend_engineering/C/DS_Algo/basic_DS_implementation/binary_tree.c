#include <stdio.h>
#include <stdlib.h>

typedef struct BinaryTreeNode{
    int val;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
} BinaryTreeNode;

void insert(BinaryTreeNode **root, int val){
    BinaryTreeNode *new_node = (BinaryTreeNode*) malloc (sizeof(BinaryTreeNode));
    new_node->val = val;
    new_node->left = NULL;
    new_node->right = NULL;

    if(*root == NULL){
        *root = new_node;
        return;
    }

    BinaryTreeNode *parent_node = NULL;
    BinaryTreeNode *cur_node = *root;
    while(cur_node != NULL){
        if(cur_node->val == val){
            free(new_node);
            return;
        }

        parent_node = cur_node;

        if(val < cur_node->val){
            cur_node = cur_node->left;
        }
        else{
            cur_node = cur_node->right;
        }
    }

    if(val < parent_node->val){
        parent_node->left = new_node;
    }
    else{
        parent_node->right = new_node;
    }
}

int find_min(BinaryTreeNode *root){
    if(root == NULL){
        return -1;
    }

    BinaryTreeNode *cur_node = root;
    while(cur_node->left != NULL){
        cur_node = cur_node->left;
    }

    return cur_node->val;
}

int find_max(BinaryTreeNode *root){
    if(root == NULL){
        return -1;
    }

    BinaryTreeNode *cur_node = root;
    while(cur_node->right != NULL){
        cur_node = cur_node->right;
    }

    return cur_node->val;
}

int find_successor(BinaryTreeNode *root, int val){
    if(root == NULL) return -1;

    BinaryTreeNode *suc = NULL;
    BinaryTreeNode *cur_node = root;
    while(cur_node != NULL){
        if(cur_node->val == val){
            if(cur_node->right == NULL){
                if(suc != NULL) return suc->val;
                else return -1;
            }
            else break;
        }

        if(val < cur_node->val){
            suc = cur_node;
            cur_node = cur_node->left;
        }
        else{
            cur_node = cur_node->right;
        }
    }

    if(cur_node == NULL){
        return -1;
    }

    suc = cur_node->right;
    while(suc->left != NULL){
        suc = suc->left;
    }

    return suc->val;
}

int find_predecessor(BinaryTreeNode *root, int val){
    if(root == NULL) return -1;

    BinaryTreeNode *pred = NULL;
    BinaryTreeNode *cur_node = root;
    while(cur_node != NULL){
        if(cur_node->val == val){
            if(cur_node->left == NULL){
                if(pred != NULL) return pred->val;
                else return -1;
            }
            else break;
        }

        if(val < cur_node->val){
            cur_node = cur_node->left;
        }
        else{
            pred = cur_node;
            cur_node = cur_node->right;
        }
    }

    if(cur_node == NULL) return -1;

    pred = cur_node->left;
    while(pred->right != NULL){
        pred = pred->right;
    }

    return pred->val;
}

void erase(BinaryTreeNode **root, int val){
    if(*root == NULL) return;

    BinaryTreeNode *parent = NULL;
    BinaryTreeNode *cur_node = *root;
    while(cur_node != NULL){
        if(val == cur_node->val) break;
        
        parent = cur_node;

        if(val < cur_node->val) cur_node = cur_node->left;
        else cur_node = cur_node->right;
    }

    // case 0: val not found
    if(cur_node == NULL) return;

    // case 1: val is leaf node
    if(cur_node->left == NULL && cur_node->right == NULL){
        if(parent == NULL){
            free(*root);
            *root = NULL;
        }
        else{
            if(cur_node == parent->left) parent->left = NULL;
            else parent->right = NULL;
            free(cur_node);
            cur_node = NULL;
        }

        return;
    }

    // case 2: val has only one child
    BinaryTreeNode *child = NULL;
    if(cur_node->left != NULL && cur_node->right == NULL){
        child = cur_node->left;
    }
    else if(cur_node->left == NULL && cur_node->right != NULL){
        child = cur_node->right;
    }

    if(child != NULL){
        if(parent == NULL) *root = child;
        else{
            if(cur_node == parent->left) parent->left = child;
            else parent->right = child;
        }

        free(cur_node);
        return;
    }

    // case 3: val has both children
    parent = cur_node;
    BinaryTreeNode *suc = cur_node->right;
    while(suc->left != NULL){
        parent = suc;
        suc = suc->left;
    }
    cur_node->val = suc->val;
    if(suc == parent->left) parent->left = suc->right;
    else parent->right = suc->right;

    free(suc);
    suc = NULL;
}

void preOrderTraversal(BinaryTreeNode *root){
    if(root == NULL){
        printf("Tree is empty\n");
        return;
    }

    printf("%d, ", root->val);
    if(root->left != NULL) preOrderTraversal(root->left);
    if(root->right != NULL) preOrderTraversal(root->right);
}

void inOrderTraversal(BinaryTreeNode *root){
    if(root == NULL){
        printf("Tree is empty\n");
        return;
    }

    if(root->left != NULL) inOrderTraversal(root->left);
    printf("%d, ", root->val);
    if(root->right != NULL) inOrderTraversal(root->right);
}

void postOrderTraversal(BinaryTreeNode *root){
    if(root == NULL){
        printf("Tree is empty\n");
        return;
    }

    if(root->left != NULL) postOrderTraversal(root->left);
    if(root->right != NULL) postOrderTraversal(root->right);
    printf("%d, ", root->val);
}

int main() {
    BinaryTreeNode *root = NULL;

    // Insert values
    insert(&root, 50);
    insert(&root, 30);
    insert(&root, 70);
    insert(&root, 20);
    insert(&root, 40);
    insert(&root, 60);
    insert(&root, 80);

    printf("BST before deletion:\n");
    inOrderTraversal(root);
    printf("\n");

    // Delete a node
    erase(&root, 50);

    printf("BST after deleting 50:\n");
    inOrderTraversal(root);
    printf("\n");

    // Find min, max, successor, and predecessor
    printf("Min: %d\n", find_min(root));
    printf("Max: %d\n", find_max(root));
    printf("Successor of 40: %d\n", find_successor(root, 40));
    printf("Predecessor of 40: %d\n", find_predecessor(root, 40));

    return 0;
}