#include <iostream>
using namespace std;

// AVL Tree node
class AVLNode {
public:
    int key;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int key) : key(key), left(nullptr), right(nullptr), height(1){}
};


class AVLTree{
    AVLNode *root = nullptr;

public:
    // Function to get the height of a node
    int getHeight(AVLNode* node) {
        return node ? node->height : 0;
    }

    // Function to get the balance factor of a node
    int getBalanceFactor(AVLNode* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    // Right Rotation (LL Rotation)
    AVLNode* rightRotate(AVLNode* root) {
        AVLNode* newRoot = root->left;
        AVLNode* rightSubtreeOfNewRoot = newRoot->right;

        // Perform rotation
        newRoot->right = root;
        root->left = rightSubtreeOfNewRoot;

        // Update heights
        root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
        newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

        return newRoot;
    }

    // Left Rotation (RR Rotation)
    AVLNode* leftRotate(AVLNode* root) {
        AVLNode* newRoot = root->right;
        AVLNode* leftSubtreeOfNewRoot = newRoot->left;

        // Perform rotation
        newRoot->left = root;
        root->right = leftSubtreeOfNewRoot;

        // Update heights
        root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
        newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

        return newRoot;
    }

    void insert(int key){
        root = insert(root, key);
    }

    // Insert function for AVL tree
    AVLNode* insert(AVLNode* root, int key) {
        if (!root) return new AVLNode(key);

        if (key < root->key)
            root->left = insert(root->left, key);
        else if (key > root->key)
            root->right = insert(root->right, key);
        else
            return root; // Duplicate keys are not allowed

        // Update height
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        // Get balance factor
        int balanceFactor = getBalanceFactor(root);

        // Perform rotations if needed
        if (balanceFactor > 1 && key < root->left->key) // Left Heavy (LL Rotation)
            return rightRotate(root);

        if (balanceFactor < -1 && key > root->right->key) // Right Heavy (RR Rotation)
            return leftRotate(root);

        if (balanceFactor > 1 && key > root->left->key) { // Left-Right Case (LR Rotation)
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balanceFactor < -1 && key < root->right->key) { // Right-Left Case (RL Rotation)
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    int getMinValue(){
        auto node = getMinValueNode(root);
        return node->key;
    }
    // Function to find the node with the smallest key in a subtree
    AVLNode* getMinValueNode(AVLNode* root) {
        AVLNode* currentNode = root;
        while (currentNode->left)
            currentNode = currentNode->left;
        return currentNode;
    }

    void deleteNode(int key){
        root = deleteNode(root, key);
    }

    // Delete function for AVL tree
    AVLNode* deleteNode(AVLNode* root, int key) {
        if (!root) return root;

        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            if (!root->left || !root->right) {
                AVLNode* temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp;
                delete temp;
            } else {
                AVLNode* temp = getMinValueNode(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (!root) return root;

        // Update height
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        // Get balance factor
        int balanceFactor = getBalanceFactor(root);

        // Perform rotations if needed
        if (balanceFactor > 1 && getBalanceFactor(root->left) >= 0) // Left Heavy (LL Rotation)
            return rightRotate(root);

        if (balanceFactor > 1 && getBalanceFactor(root->left) < 0) { // Left-Right Case (LR Rotation)
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balanceFactor < -1 && getBalanceFactor(root->right) <= 0) // Right Heavy (RR Rotation)
            return leftRotate(root);

        if (balanceFactor < -1 && getBalanceFactor(root->right) > 0) { // Right-Left Case (RL Rotation)
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    // Function to perform in-order traversal of the AVL tree
    void inOrderTraversal(){
        inOrderTraversal(root);
    }
    void inOrderTraversal(AVLNode* root) {
        if (root) {
            inOrderTraversal(root->left);
            cout << root->key << " ";
            inOrderTraversal(root->right);
        }
    }
};

// Driver code
int main() {
    AVLTree avl_tree;

    avl_tree.insert(10);
    avl_tree.insert(20);
    avl_tree.insert(30);
    avl_tree.insert(40);
    avl_tree.insert(50);
    avl_tree.insert(60);

    cout << "In-order traversal of AVL tree: ";
    avl_tree.inOrderTraversal();
    cout << endl;

    avl_tree.deleteNode(30);
    cout << "In-order traversal after deleting 30: ";
    avl_tree.inOrderTraversal();
    cout << endl;

    return 0;
}