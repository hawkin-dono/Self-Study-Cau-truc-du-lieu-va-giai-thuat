// Checking if a binary tree is height balanced in C++

#include <iostream>
using namespace std;

class Node {
public:
    int value;
    Node *left;
    Node *right;
    int height;

    Node(int value) {
        this->value = value;
        left = nullptr;
        right = nullptr;
        height = 1;
    }

};

class BalancedTree {
private:
    Node *root;
    
public:
    BalancedTree() {
        root == nullptr;
    }

    BalancedTree(Node *node) {
        root = node;
    }

    BalancedTree(int value) {
        root = new Node(value);
        root->left = nullptr;
        root->right = nullptr;
    }
    
    bool checkHeightBalance(Node *root, int *height) {
    
        int leftHeight = 0, rightHeight = 0;
        int l = 0, r = 0;

        if (root == NULL) {
            *height = 0;
            return 1;
        }

        l = checkHeightBalance(root->left, &leftHeight);
        r = checkHeightBalance(root->right, &rightHeight);

        *height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;

        if (std::abs(leftHeight - rightHeight >= 2))
            return 0;

        else
            return l && r;
    }

    Node *search(Node *node, int value) {
        if(node == nullptr || node->value == value) {
            return node;
        } else if(value < node->value) {
            return search(node->left, value);
        } else{
            return search(node->right, value);
        }
    }
    
    // tim chieu cao cua 1 node
    int height(Node *N) {
        if (N == nullptr)
            return 0;
        return N->height;
    }

    // tim chenh lech chieu cao giua cay con ben trai va cay con ben phai
    int getBalanceFactor(Node *N) {
        if (N == nullptr) return 0;
        return height(N->left) - height(N->right);
    }
    Node *rightRotate(Node *x) {
        Node *y = x->left;
        Node *rcY = y->right;
        y->right = x;
        x->left = rcY;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    Node *leftRotate(Node *x) {
        Node *y = x->right;
        Node *lcY = y->left;
        y->left = x;
        x->right = lcY;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;  
        return y;
    }
    void insert(int value) {
        root = insertNode(root, value);
    }
    // Insert a node
    Node *insertNode(Node *node, int value) {
        // Find the correct postion and insert the node
        if (node == NULL)
            return (new Node(value));
        if (value < node->value)
            node->left = insertNode(node->left, value);
        else if (value > node->value)
            node->right = insertNode(node->right, value);
        else
            return node;

        // Update the balance factor of each node and
        // balance the tree
        node->height = 1 + max(height(node->left), height(node->right));
        int balanceFactor = getBalanceFactor(node);
        if (balanceFactor > 1) {
            if (value < node->left->value) {
                return rightRotate(node);

            } else if (value > node->left->value) {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        }
        if (balanceFactor < -1) {
            if (value > node->right->value) {
                return leftRotate(node);
            } else if (value < node->right->value) {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }
        return node;
    }

    // Node with minimum value of right subtree
    Node *nodeWithMimumValue(Node *node) {
        Node *current = node;
        while (current->left != NULL)
            current = current->left;
        return current;
    }

    void Delete(int value) {
        root = deleteNode(root, value);
    }
    // Delete a node
    Node *deleteNode(Node *root, int value) {
        // Find the node and delete it
        if (root == NULL)
            return root;
        if (value < root->value)
            root->left = deleteNode(root->left, value);
        else if (value > root->value)
            root->right = deleteNode(root->right, value);
        else {
            if ((root->left == NULL) || (root->right == NULL)) {
                Node *temp = root->left ? root->left : root->right;
                if (temp == NULL) {
                    temp = root;
                    root = NULL;
                } else
                    *root = *temp;
                free(temp);
            } else {
                Node *temp = nodeWithMimumValue(root->right);
                root->value = temp->value;
                root->right = deleteNode(root->right, temp->value);
            }
        }

        if (root == NULL)
            return root;

        // Update the balance factor of each node and
        // balance the tree
        root->height = 1 + max(height(root->left), height(root->right));
        int balanceFactor = getBalanceFactor(root);
        if (balanceFactor > 1) {
            if (getBalanceFactor(root->left) >= 0) {
                return rightRotate(root);
            } else {
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }
        }
        if (balanceFactor < -1) {
            if (getBalanceFactor(root->right) <= 0) {
                return leftRotate(root);
            } else {
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }
        }
        return root;
    }

    void preorder() {
        preorderTraversal(root);
    }
    void preorderTraversal(Node* node) {
        if (node != nullptr) {
            std::cout << node->value << " ";
            preorderTraversal(node->left);
            preorderTraversal(node->right);
        }
    }

    void inorder() {
        inorderTraversal(root);
    }
    void inorderTraversal(Node* node) {
        if (node != nullptr) {
            inorderTraversal(node->left);
            std::cout << node->value << " ";
            inorderTraversal(node->right);
        }
    }

    void postorder() {
        postorderTraversal(root);
    }
    void postorderTraversal(Node* node) {
        if (node != nullptr) {
            postorderTraversal(node->left);
            postorderTraversal(node->right);
            std::cout << node->value << " ";
        }
    }

};

int main() {
    BalancedTree *avlTree = new BalancedTree(1);
    avlTree->insert(2);
    avlTree->insert(3);
    avlTree->insert(4);
    avlTree->insert(5);
    avlTree->insert(6);
    avlTree->insert(7);
    avlTree->insert(8);
    avlTree->insert(9);
    avlTree->insert(10);
    avlTree->preorder();
    cout << endl;

    avlTree->Delete(2);
    avlTree->Delete(3);
    avlTree->Delete(5);
    avlTree->preorder();


    
}