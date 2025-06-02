#include<iostream>
#include<string>

using namespace std;

enum Color {RED, BLACK};

class RBNode {
public:
    int data;
    Color color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;

    RBNode (int value){
        data = value;
        color = RED;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    void printRB (int level, std::string side, int RedBlack){
        if (left != nullptr)
        {
            left->printRB(level + 1, "/", RedBlack);
        }
        std::string space(6 * level, ' ');
        string colorRB = "";
        if (RedBlack == 1)
        {
            colorRB = "RED";
        } else {
            colorRB = "BLACK";
        }
        if (data == 0)
        {
            this;
        } else {
            std::cout << space << side << "-->" << data << " (" << colorRB << ")\n";
        }
        if (right != nullptr)
        {
            right->printRB(level + 1, "\\", RedBlack);
        }
    }
};

class RedBlackTree {
private:
    RBNode* root;
    RBNode* NIL;
    // Void leftRotate

    void rightRotate(RBNode* x) {
        RBNode* y = x->left;
        x->left = y->right;

        if (y->right!= NIL)
        {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            root = y;
        } else if ( x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    void leftRotate(RBNode* x) {
        RBNode* y = x->right;
        x->right = y->left;

        if (y->left!= NIL)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            root = y;
        } else if ( x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void fixColor (RBNode* k){
        RBNode* u;

        while (k->parent != nullptr && k->parent->color == RED)
        {
            if (k->parent == k->parent->parent->left)
            {
                u = k->parent->parent->left;

                if (u != nullptr && u->color == RED)
                {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if(k == k->parent->left){
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right;

                if (u != nullptr && u->color == RED)
                {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if(k == k->parent->right){
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            }

            if (k == root){
                break;
            }
        }
        root->color = BLACK;
    }
public:
    RedBlackTree(){
        NIL = new RBNode(0);
        NIL -> color = BLACK;
        root = NIL;
    }
    
    ~RedBlackTree(){
        clear(root);
        delete NIL;
    }
    
    void insert (int value){
        RBNode* node = new RBNode(value);
        node -> left = NIL;
        node -> right = NIL;
        node -> color = RED;
        
        if(root == NIL){
            root = node;
            root -> color = BLACK;
            return;
        }
        
        insertRecurvise (root, node);
        
        fixColor(node);
    }
    
    bool search(RBNode* n, int key) const {
        if (n == NIL) {
            return false;
        }
        if (key == n->data) {
            return true;
        }
        if (key < n->data) {
            return search(n->left, key); 
        } else {
            return search(n->right, key);
        }
    }

    void clear(RBNode* n) {
        if (n == NIL) {
            return;
        }
        clear(n->left);
        clear(n->right);
        delete n;
    }

    int getMin(RBNode* n) {
        if (!left) return n->data;
        return getMin(n->left);
    }

    int getMax(RBNode* n) {
        if (!right) return n->data;
        return getMax(n->right);     
    }
    /*
    int countNodes() {
        int count = 1;
        if(left)
            count += left->countNodes();
        if(right)
            count += right->countNodes();
    }

    int height() {
        int leftHeight = left ? left->height() : 0;
        int rightHeight = right ? right->height() : 0;
        return 1 + max(leftHeight, rightHeight);
    }
    */
    void insertRecurvise(RBNode* current, RBNode* newNode){
        if(newNode->data < current->data){
            if(current->left == NIL){
                current->left = newNode;
                newNode->parent = current;
            } else {
                insertRecurvise (current->left, newNode);
            }
        } else {
            if(current->right == NIL){
                current->right = newNode;
                newNode->parent = current;
            } else {
                insertRecurvise (current->right, newNode);
            }
        }
    }
    
    void printTree() {
        if (root != NIL) {
            root->printRB(0, "", root->color);
        } else {
            cout << "Árvore vazia." << endl;
        }
    }

    bool search(int key) const {
        return search(root, key);
    }

    int getMin() {
        return getMin(root);
    }

    int getMax() {
        return getMin(root);
    }
};

int main (){
    RedBlackTree tree;
    
    tree.insert(10);
    tree.insert(12);
    tree.insert(5);
    tree.insert(4);
    tree.insert(39);
    tree.insert(17);
    
    cout << "Árvore Rubro Negro" << endl;
    tree.printTree();

    cout << "Digite um numero da arvore: " << endl;
    int key;
    if(cin >> key) {
        cout << (tree.search(key) ? "O numero foi encontrado\n": "O numero nao foi encontrado\n");
    }

    cout << tree.getMin() << endl;
    cout << tree.getMax() << endl;
    return 0;
}
    ad