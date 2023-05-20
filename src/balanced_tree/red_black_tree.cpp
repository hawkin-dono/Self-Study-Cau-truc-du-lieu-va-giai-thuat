// Implementing Red-Black Tree in C++

#include <iostream>

using namespace std;

class Node
{
public:
    int value;
    Node *left;
    Node *right;
    Node *parent;
    bool color;

    Node() {
        this->value = 0;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
        this->color = false;
    }
    Node(int value) {
        this->value = value;
        this->left = nullptr;
        this->right = nullptr;
        this->parent = nullptr;
        this->color = false;
    }

    std::string getColor() {
        if (this->color) {
		    return "true";
        }
	    return "false";
    }

    bool hasRedChild() {
        if (this->left != nullptr && !this->left->color) {
            return true;
        }
        if (this->right != nullptr && !this->right->color) {
            return true;
        }
        return false;
    }

    void swapColor() {
        this->color = !(this->color);
    }

    bool isOnLeft() {
        if(parent == nullptr) return false;
        return this == parent->left;
    }

    Node *sibling() {
        if(this == nullptr || this->parent == nullptr) {
            return nullptr;
        }
        if(this == parent->left) {
            return parent->right;
        }
        else return parent->left;
    }

    void moveDown(Node *nParent) {
        if (parent != NULL) {
            if (isOnLeft()) {
                parent->left = nParent;
            } else {
                parent->right = nParent;
            }
        }
        nParent->parent = parent;
        parent = nParent;
    }


};


class RBT {
private:
    Node* root;

    Node *search(Node *node, int value) {
        if(node == nullptr || node->value == value) {
            return node;
        } else if(value < node->value) {
            return search(node->left, value);
        } else{
            return search(node->right, value);
        }
    }

    Node *leftRotate(Node *x) {
        Node *y = x->right;
        Node *lcY = y->left;
        y->left = x;
        x->right = lcY;

        x->parent = y;
        if(lcY != nullptr) {
            lcY->parent = x;
        }
        return y;
    }

    void leftRotateDelete(Node *x) {
        // new parent will be node's right child
        Node *y = x->right;
    
        // update root if current node is root
        if (x == root)
        root = y;
    
        x->moveDown(y);
    
        // connect x with new parent's left element
        x->right = y->left;
        // connect new parent's left element with node
        // if it is not null
        if (y->left != NULL)
        y->left->parent = x;
    
        // connect new parent with x
        y->left = x;
    }

    Node *rightRotate(Node *x) {
        Node *y = x->left;
        Node *rcY = y->right;
        y->right = x;
        x->left = rcY;

        x->parent = y;
        if(rcY != nullptr) {
            rcY->parent = x;
        }
        return y;
    }

    void rightRotateDelete(Node *x) {
        // new parent will be node's left child
        Node *y = x->left;
    
        // update root if current node is root
        if (x == root)
            root = y;
    
        x->moveDown(y);
    
        // connect x with new parent's right element
        x->left = y->right;
        // connect new parent's right element with node
        // if it is not null
        if (y->right != NULL)
        y->right->parent = x;
    
        // connect new parent with x
        y->right = x;
    }

    bool ll = false;
    bool rr = false;
    bool lr = false;
    bool rl = false;
    Node* insertNode(Node* root, int value) {
        bool f = false; // f is true when false false conflict is there.

        // Recursive calls to insert at proper position according to BST properties.
        if (root == nullptr)
            return new Node(value);
        else if (value < root->value)
        {
            root->left = insertNode(root->left, value);
            root->left->parent = root;
            if (root != this->root)
            {
                if (root->color == false && root->left->color == false)
                    f = true;
            }
        }
        else
        {
            root->right = insertNode(root->right, value);
            root->right->parent = root;
            if (root != this->root)
            {
                if (root->color == false && root->right->color == false)
                    f = true;
            }
        }

        // Now let's rotate.
        if (this->ll) // For left rotate.
        {
            root = leftRotate(root);
            root->color = true;
            root->left->color = false;
            this->ll = false;
        }
        else if (this->rr) // For right rotate.
        {
            root = rightRotate(root);
            root->color = true;
            root->right->color = false;
            this->rr = false;
        }
        else if (this->rl) // For right and then left.
        {
            root->right = rightRotate(root->right);
            root->right->parent = root;
            root = leftRotate(root);
            root->color = true;
            root->left->color = false;
            this->rl = false;
        }
        else if (this->lr) // For left and then right.
        {
            root->left = leftRotate(root->left);
            root->left->parent = root;
            root = rightRotate(root);
            root->color = true;
            root->right->color = false;
            this->lr = false;
        }

        // When rotation and recolouring are done, flags are reset.
        // Now let's take care of false false conflict.
        if (f)
        {
            if (root->parent->right == root) // To check which child is the current node of its parent.
            {
                if (root->parent->left == nullptr || root->parent->left->color == true) // Case when parent's S is black.
                {
                    // Perform certain rotation and recolouring. This will be done while backtracking. Hence setting up respective flags.
                    if (root->left != nullptr && root->left->color == false)
                        this->rl = true;
                    else if (root->right != nullptr && root->right->color == false)
                        this->ll = true;
                }
                else // Case when parent's S is red.
                {
                    root->parent->left->color = true;
                    root->color = true;
                    if (root->parent != this->root)
                        root->parent->color = false;
                }
            }
            else
            {
                if (root->parent->right == nullptr || root->parent->right->color == true)
                {
                    if (root->left != nullptr && root->left->color == false)
                        this->rr = true;
                    else if (root->right != nullptr && root->right->color == false)
                        this->lr = true;
                }
                else
                {
                    root->parent->right->color = true;
                    root->color = true;
                    if (root->parent != this->root)
                        root->parent->color = false;
                }
            }
            f = false;
        }
        return root;
    }

    void swapValues(Node *u, Node *v) {
        int temp;
        temp = u->value;
        u->value = v->value;
        v->value = temp;
    }

    Node* minimum(Node* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    Node * find_Nodereplace(Node * x) {
        // when node have 2 children
        if (x->left != nullptr and x->right != nullptr)
            return minimum(x->right);

        // when leaf
        if (x->left == nullptr and x->right == nullptr)
            return nullptr;

        // when single child
        if (x->left != nullptr)
            return x->left;
        else
            return x->right;
    }

    void deleteNode(Node * x) {
        Node * y = find_Nodereplace(x);

        // True when y and x are both black
        bool uvBlack = ((y == nullptr or y->color == 1) and(x->color == 1));
        Node *parent = x->parent;

        if (y == nullptr) {
            // y is nullptr therefore x is leaf
            if (x == root) {
                // x is root, making root null
                root = nullptr;
            } else {
                if (uvBlack) {
                    // y and x both black
                    // x is leaf, fix double black at x
                    fixDoubleBlack(x);
                } else {
                    // y or x is red
                    if (x->sibling() != nullptr)
                        // sibling is not null, make it red"
                        x->sibling()->color = 1;
                }

                // delete x from the tree
                if (x->isOnLeft()) {
                    parent->left = nullptr;
                } else {
                    parent->right = nullptr;
                }
            }
            delete x;
            return;
        }

        if (x->left == nullptr or x->right == nullptr) {
            // x has 1 child
            if (x == root) {
                // x is root, assign the value of y to x, and delete y
                x->value = y->value;
                x->left = x->right = nullptr;
                delete y;
            } else {
                // Detach x from tree and move y up
                if (x->isOnLeft()) {
                    parent->left = y;
                } else {
                    parent->right = y;
                }
                delete x;
                y->parent = parent;
                if (uvBlack) {
                    // y and x both black, fix double black at y
                    fixDoubleBlack(y);
                } else {
                    // y or x red, color y black
                    y->color = 1;
                }
            }
            return;
        }

        // x has 2 children, swap values with successor and recurse
        swapValues(y, x);
        deleteNode(y);
    }

    void fixDoubleBlack(Node * x) {
        if (x == root)
            // Reached root
            return;

        Node * sibling = x->sibling(), * parent = x->parent;
        if (sibling == nullptr) {
            // No sibling, double black pushed up
            fixDoubleBlack(parent);
        } else {
            if (sibling->color == false) {
                // Sibling red
                parent->color = false;
                sibling->color = true;
                if (sibling->isOnLeft()) {
                    // left case
                    rightRotateDelete(parent);
                } else {
                    // right case
                    leftRotateDelete(parent);
                }
                fixDoubleBlack(x);
            } else {
                // Sibling black
                if (sibling->hasRedChild()) {
                    // at least 1 red children
                    if (sibling->left != nullptr and sibling->left->color == false) {
                        if (sibling->isOnLeft()) {
                            // left left
                            sibling->left->color = sibling->color;
                            sibling->color = parent->color;
                            rightRotateDelete(parent);
                        } else {
                            // right left
                            sibling->left->color = parent->color;
                            rightRotateDelete(sibling);
                            leftRotateDelete(parent);
                        }
                    } else {
                        if (sibling->isOnLeft()) {
                            // left right
                            sibling->right->color = parent->color;
                            leftRotateDelete(sibling);
                            rightRotateDelete(parent);
                        } else {
                            // right right
                            sibling->right->color = sibling->color;
                            sibling->color = parent->color;
                            leftRotateDelete(parent);
                        }
                    }
                    parent->color = true;
                } else {
                    // 2 black children
                    sibling->color = false;
                    if (parent->color == true)
                        fixDoubleBlack(parent);
                    else
                        parent->color = true;
                }
            }
        }
    }

public:
    RBT() {
        root = nullptr;
    }
    RBT(int value) {
        root = new Node(value);
        root->color = true;
    }
    void insert(int value) {
        if (this->root == nullptr) {
            this->root = new Node(value);
            this->root->color = true;
        } else {
            this->root = insertNode(this->root, value);
        }
    }
    
    
    void Delete(int value) {
        if (root == nullptr)
            return;
    
        Node *x = search(value);
    
        if (x == nullptr) {
            cout << "Node " << value << " not found" << endl;
            return;
        }
    
        deleteNode(x);
    }

    Node *search(int value) {
        return search(root, value);
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
    RBT *rbt = new RBT(1);
    rbt->insert(2);
    rbt->insert(3);
    rbt->insert(4);
    rbt->insert(5);
    rbt->insert(6);
    rbt->insert(7);
    rbt->insert(8);
    rbt->insert(9);
    rbt->insert(10);
    rbt->preorder();

    rbt->Delete(7);

    
}