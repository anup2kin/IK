#include <stdio.h>
#include <stdlib.h>

int min(int n1, int n2){
    if(n1 < n2) return n1;
    else return n2;
}

int max(int n1, int n2){
    if(n1 > n2) return n1;
    else return n2;
}

typedef struct AVLTreeNode{
    int val;
    struct AVLTreeNode *left;
    struct AVLTreeNode *right;
    int height;
} AVLTreeNode;

// Function to get height of the node
int get_height(AVLTreeNode *node){
    if(node == NULL) return 0;
    else return node->height;
}

// Function to get balance factor of the node
int get_balance_factor(AVLTreeNode *node){
    if(node == NULL) return 0;
    else return get_height(node->left) - get_height(node->right);
}

// Right rotation LL case
AVLTreeNode* rotate_right(AVLTreeNode *root){
    AVLTreeNode *newRoot = root->left;
    AVLTreeNode *rightSubtreeOfNewRoot = newRoot->right;

    // Perform right rotation
    newRoot->right = root;
    root->left = rightSubtreeOfNewRoot;

    // Update heights
    root->height = max(get_height(root->left), get_height(root->right)) + 1;
    newRoot->height = max(get_height(newRoot->left), get_height(newRoot->right)) + 1;

    return newRoot;
}

// Left rotation RR case
AVLTreeNode* rotate_left(AVLTreeNode *root){
    AVLTreeNode *newRoot = root->right;
    AVLTreeNode *leftSubtreeOfNewRoot = newRoot->left;

    // Perform left rotation
    newRoot->left = root;
    root->right = leftSubtreeOfNewRoot;

    // Update height
    root->height = max(get_height(root->left), get_height(root->right)) + 1;
    newRoot->height = max(get_height(newRoot->left), get_height(newRoot->right)) + 1;

    return newRoot;
}

AVLTreeNode* insert(AVLTreeNode *root, int val){
    if(root == NULL){
        AVLTreeNode *newNode = (AVLTreeNode *) malloc (sizeof(AVLTreeNode));
        newNode->val = val;
        newNode->left = NULL;
        newNode->right = NULL;
        return newNode;
    }

    if(val < root->val) root->left = insert(root->left, val);
    else if(val > root->val) root->right = insert(root->right, val);
    else return root;

    // Update the height
    root->height = max(get_height(root->left), get_height(root->right)) + 1;

    // Get the balance factor
    int balanceFactor = get_balance_factor(root);

    // LL case, rotate right
    if(balanceFactor > 1 && val < root->left->val) return rotate_right(root);

    // RR case, rotate left
    if(balanceFactor < -1 && val > root->right->val) return rotate_left(root);

    // LR case, rotate left (parent) and then rotate right (ancenstor)
    if(balanceFactor > 1 && val > root->left->val){
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }

    // RL case, rotate right (parent) and then rotate left (ancestor)
    if(balanceFactor < -1 && val < root->right->val){
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }

    return root;
}

int get_min_value(AVLTreeNode *root){
    if(root == NULL) return -1;

    AVLTreeNode *cur_node = root;
    while(cur_node->left != NULL){
        cur_node = cur_node->left;
    }

    return cur_node->val;
}

AVLTreeNode* get_min_value_node(AVLTreeNode *root){
    if(root == NULL) return NULL;

    AVLTreeNode *cur_node = root;
    while(cur_node->left != NULL){
        cur_node = cur_node->left;
    }

    return cur_node;
}

int get_max_value(AVLTreeNode *root){
    if(root == NULL) return -1;

    AVLTreeNode *cur_node = root;
    while(cur_node->right != NULL){
        cur_node = cur_node->right;
    }

    return cur_node->val;
}

AVLTreeNode* get_max_value_node(AVLTreeNode *root){
    if(root == NULL) return NULL;

    AVLTreeNode *cur_node = root;
    while(cur_node->right != NULL){
        cur_node = cur_node->right;
    }

    return cur_node;
}

AVLTreeNode* delete_node(AVLTreeNode *root, int val){
    if(root == NULL) return root;

    if(val < root->val) root->left = delete_node(root->left, val);
    else if(val > root->val) root->right = delete_node(root->right, val);
    else{
        // Case 1: Leaf node case
        if(root->left == NULL && root->right == NULL){
            AVLTreeNode *node_to_delete = root;
            root = NULL;
            free(node_to_delete);
            node_to_delete = NULL;
        }
        else{
            // Case 2: Only one child case
            AVLTreeNode *child = NULL;
            if(root->left != NULL && root->right == NULL) child = root->left;
            else if(root->left == NULL && root->right != NULL) child = root->right;

            if(child != NULL){
                *root = *child;
                free(child);
                child = NULL;
            }
            // Case 3: Has both child
            else{
                AVLTreeNode * suc = get_min_value_node(root->right);
                root->val = suc->val;
                root->right = delete_node(root->right, val);
            }
        }
    }

    if(root == NULL) return root;

    // Update height
    root->height = max(get_height(root->left), get_height(root->right)) + 1;

    // Get balance factor
    int balanceFactor = get_balance_factor(root);

    // Left Heavy (LL Rotation)
    if(balanceFactor > 1 && get_balance_factor(root->left) >= 0) return rotate_right(root);

    // Left-Right Case (LR Rotation)
    if(balanceFactor > 1 && get_balance_factor(root->left) < 0){
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }

    // Right Heavy (RR Rotation)
    if(balanceFactor < 1 && get_balance_factor(root->right) <= 0) return rotate_left(root);

    // Right-Left case (RL Rotation)
    if(balanceFactor < 1 && get_balance_factor(root->right) > 0){
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }

    return root;
}

void preorder(AVLTreeNode *root){
    if(root == NULL){
        printf("\nTree is empty!\n");
        return;
    }

    printf("%d, ", root->val);
    if(root->left != NULL) preorder(root->left);
    if(root->right != NULL) preorder(root->right);
}

void inorder(AVLTreeNode *root){
    if(root == NULL){
        printf("\nTree is empty!\n");
        return;
    }

    if(root->left != NULL) inorder(root->left);
    printf("%d, ", root->val);
    if(root->right != NULL) inorder(root->right);
}

void postorder(AVLTreeNode *root){
    if(root == NULL){
        printf("\nTree is empty!\n");
        return;
    }

    if(root->left != NULL) postorder(root->left);
    if(root->right != NULL) postorder(root->right);
    printf("%d, ", root->val);


}

int main() { 
    AVLTreeNode *root = NULL; 
    
    // Constructing tree given in the above figure 
    root = insert(root, 10); 
    root = insert(root, 20); 
    root = insert(root, 30); 
    root = insert(root, 40); 
    root = insert(root, 50); 
    root = insert(root, 25); 
    
    /* The constructed AVL Tree would be 
              30 
            /   \ 
          20     40 
         /  \      \ 
       10   25     50 
    */
    printf("\n========== Inorder traversal ===========\n"); 
    inorder(root); 
    
    int val_to_delete = 10;

    root = delete_node(root, val_to_delete);
    printf("\nDeleted node with value [%d]\n", val_to_delete);

    printf("\n========== Inorder traversal ===========\n"); 
    inorder(root);

    return 0; 
} 