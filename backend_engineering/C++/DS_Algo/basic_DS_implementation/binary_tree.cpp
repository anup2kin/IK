#include <iostream>
#include <optional>

using namespace std;

class TreeNode{
public:
    int key;

    TreeNode *left = nullptr;
    TreeNode *right = nullptr;

    TreeNode(int key, TreeNode *left = nullptr, TreeNode *right = nullptr)
        :key(key), left(left), right(right){}
};

class Tree{
    TreeNode *root = nullptr;

public:
    optional<int> search(int key){
        if(root == nullptr) return nullopt;

        auto cur_node = root;
        while(cur_node != nullptr){
            if(key == cur_node->key) return key;
            else if(key < cur_node->key) cur_node = cur_node->left;
            else cur_node = cur_node->right;
        }

        return nullopt;
    }

    void insert(int key){
        auto new_node = new TreeNode(key);

        if(root == nullptr){
            root = new_node;
            return;
        }

        auto cur_node = root;
        TreeNode *parent = nullptr;

        while(cur_node != nullptr){
            if(key == cur_node->key) return;

            parent = cur_node;

            if(key < cur_node->key){
                cur_node = cur_node->left;
            }
            else{
                cur_node = cur_node->right;
            }
        }

        if(key < parent->key) parent->left = new_node;
        else parent->right = new_node;
    }

    optional<int> find_min(){
        if(root == nullptr) return nullopt;

        auto cur_node = root;
        while(cur_node->left != nullptr){
            cur_node = cur_node->left;
        }

        return cur_node->key;
    }

    optional<int> find_max(){
        if(root == nullptr) return nullopt;

        auto cur_node = root;
        while(cur_node->right != nullptr){
            cur_node = cur_node->right;
        }

        return cur_node->key;
    }

    optional<int> successor(int key){
        if(root == nullptr) return nullopt;

        TreeNode *succ = nullptr;
        auto cur_node = root;

        while(cur_node != nullptr){
            if(key == cur_node->key){
                if(cur_node->right == nullptr){
                    if(succ == nullptr) nullopt;
                    else return succ->key;
                }
                else break;
            }

            if(key < cur_node->key){
                succ = cur_node;
                cur_node = cur_node->left;
            }
            else{
                cur_node = cur_node->right;
            }
        }

        succ = cur_node->right;
        while(succ->left != nullptr){
            succ = succ->left;
        }

        return succ->key;
    }

    optional<int> predecessor(int key){
        if(root == nullptr) return nullopt;

        TreeNode *pred = nullptr;
        auto cur_node = root;

        while(cur_node != nullptr){
            if(key == cur_node->key){
                if(cur_node->left == nullptr){
                    if(pred == nullptr) nullopt;
                    else return pred->key;
                }
                else break;
            }

            if(key < cur_node->key){
                cur_node = cur_node->left;
            }
            else{
                pred = cur_node;
                cur_node = cur_node->right;
            }
        }

        pred = cur_node->left;
        while(pred->right != nullptr){
            pred = pred->left;
        }

        return pred->key;
    }

    void erase(int key){
        if(root == nullptr) return;

        // Search the node and also find its parent
        TreeNode *parent = nullptr;
        auto cur_node = root;
        while(cur_node != nullptr){
            if(key == cur_node->key){
                break;
            }

            parent = cur_node;

            if(key < cur_node->key){
                cur_node = cur_node->left;
            }
            else{
                cur_node = cur_node->right;
            }
        }

        // Case 0: The node is not found
        if(cur_node == nullptr) return;

        // Case 1: The node is the leaf node
        if(cur_node->left == nullptr && cur_node->right == nullptr)
        {
            // If this node is root node
            if(parent == nullptr){
                delete root;
                root = nullptr;
            }
            else{
                // If the node to be delete is the left child of the parent
                if(cur_node == parent->left){
                    parent->left = nullptr;
                }
                // if the node to be deleted is the right child of the parent
                else{
                    parent->right = nullptr;
                }

                // Delete the node
                delete cur_node;
                cur_node = nullptr;
            }

            return;
        }

        // Case 2: When the node to be delete has just one child subtree
        TreeNode *child = nullptr;
        if(cur_node->left != nullptr && cur_node->right == nullptr){
            if(cur_node == parent->left) child = cur_node->left;
            else child = cur_node->left;
        }
        else if(cur_node->left == nullptr && cur_node->right != nullptr){
            if(cur_node == parent->left) child = cur_node->right;
            child = cur_node->right;
        }

        if(child != nullptr){
            // If the parent is null, then the child will become the root
            if(parent == nullptr){
                root = child;
            }
            else{
                if(cur_node == parent->left) parent->left = child;
                else parent->right = child;
            }
            delete cur_node;
            return;
        }

        // Case 3: When the node to be delete has both the children, we need to find successor
        auto suc = cur_node->right;
        parent = cur_node;
        while(suc->left != nullptr){
            parent = suc;
            suc = suc->left;
        }

        // Copy the value of successor to the node to the node to be delete.
        cur_node->key = suc->key;

        // Take care of the right child of the suc by attaching them to the parent of suc
        if(suc == parent->left) parent->left = suc->right;
        else parent->right = suc->right;

        // delete the suc node.
        delete suc;
        suc = nullptr;
    }

    void print_level_order(){
        cout << "======= LEVEL ORDER TRAVERSAL ========" << endl;
        if(root == nullptr) return;

        queue<TreeNode*> q;
        q.push(root);
        int level = 0;

        while(!empty(q)){
            cout << level << ". ";
            size_t size_q = size(q);

            for(int i = 0; i < size_q; i++)
            {
                auto node = q.front();
                q.pop();
                cout << node->key << ", ";

                if(node->left != nullptr) q.push(node->left);
                if(node->right != nullptr) q.push(node->right);
            }

            ++level;
            cout << endl;
        }
    }

    void print_preorder(){
        cout << "================ PERFORMING PREORDER TRAVERSAL=============" << endl;
        
        if(root == nullptr){
            return;
        }

        print_preorder(root);

        cout << endl;
    }

    void print_inorder(){
        cout << "================ PERFORMING INORDER TRAVERSAL=============" << endl;
       
       if(root == nullptr){
            return;
        }

        print_inorder(root);

        cout << endl;
    }

    void print_postorder(){
        cout << "================ PERFORMING POSTORDER TRAVERSAL=============" << endl;
        if(root == nullptr){
            return;
        }

        print_postorder(root);

        cout << endl;
    }
private:
    void print_preorder(TreeNode *root){
        cout << root->key << " ";
        if(root->left != nullptr) print_preorder(root->left);
        if(root->right != nullptr) print_preorder(root->right);
    }

    void print_inorder(TreeNode *root){
        if(root->left != nullptr) print_inorder(root->left);
        cout << root->key << " ";
        if(root->right != nullptr) print_inorder(root->right);
    }

    void print_postorder(TreeNode *root){
        if(root->left != nullptr) print_inorder(root->left);
        if(root->right != nullptr) print_inorder(root->right);
        cout << root->key << " ";
    }
};

int main() {
    Tree tree;
    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.insert(5);
    tree.insert(15);
    tree.insert(25);
    tree.insert(35);

    cout << endl;
    tree.print_level_order();
    cout << endl;
    tree.print_preorder();
    cout << endl;
    tree.print_inorder();
    cout << endl;
    tree.print_postorder();
    cout << endl;

    optional<int> min_value = tree.find_min();
    if (min_value) cout << "Min value: " << *min_value << endl;
    else cout << "Not found" << endl;

    optional<int> max_value = tree.find_max();
    if (max_value) cout << "Max value: " << *max_value << endl;
    else cout << "Not found" << endl;

    optional<int> search_value = tree.search(7);
    if (search_value) cout << "Found: " << *search_value << endl;
    else cout << "Not found" << endl;

    optional<int> succ = tree.successor(15);
    cout << "Successor of 15: " << (succ ? to_string(*succ) : "None") << endl;

    optional<int> pred = tree.predecessor(25);
    cout << "Predecessor of 25: " << (pred ? to_string(*pred) : "None") << endl;

    cout << "Min before deletion: " << *tree.find_min() << endl;
    cout << "Max before deletion: " << *tree.find_max() << endl;

    tree.erase(20);
    optional<int> new_min = tree.find_min();
    optional<int> new_max = tree.find_max();
    cout << "Min after deletion: " << (new_min ? to_string(*new_min) : "None") << endl;
    cout << "Max after deletion: " << (new_max ? to_string(*new_max) : "None") << endl;

    return 0;
}