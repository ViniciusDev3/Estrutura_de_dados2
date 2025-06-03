#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

enum Color {RED, BLACK};

class RBNode {
public:
    int data;
    Color color;
    RBNode* left;
    RBNode* right;
    RBNode* parent;

    RBNode(int value) {
        data = value;
        color = RED;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    void printRB(int level, const string& side) const {
        if (left && left->data != 0) {
            left->printRB(level + 1, "/");
        }
        string space(6 * level, ' ');
        string colorRB = (color == RED) ? "RED" : "BLACK";
        if (data != 0) {
            cout << space << side << "--> " << data << " (" << colorRB << ")\n";
        }
        if (right && right->data != 0) {
            right->printRB(level + 1, "\\");
        }
    }
};

class RedBlackTree {
private:
    RBNode* root;
    RBNode* NIL;

    void rightRotate(RBNode* x) {
        RBNode* y = x->left;
        x->left = y->right;
        if (y->right != NIL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->right) {
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
        if (y->left != NIL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void fixColor(RBNode* k) {
        RBNode* u;
        while (k->parent != nullptr && k->parent->color == RED) {
            if (k->parent == k->parent->parent->left) {
                u = k->parent->parent->right;
                if (u != NIL && u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->left;
                if (u != NIL && u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = BLACK;
    }

    void transplant(RBNode* u, RBNode* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    RBNode* minimum(RBNode* node) {
        while (node->left != NIL) {
            node = node->left;
        }
        return node;
    }

    RBNode* maximum(RBNode* node) {
        while (node->right != NIL) {
            node = node->right;
        }
        return node;
    }

    void deleteFix(RBNode* x) {
        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                RBNode* w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                RBNode* w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    void insertRecursive(RBNode* current, RBNode* newNode) {
        if (newNode->data < current->data) {
            if (current->left == NIL) {
                current->left = newNode;
                newNode->parent = current;
            } else {
                insertRecursive(current->left, newNode);
            }
        } else {
            if (current->right == NIL) {
                current->right = newNode;
                newNode->parent = current;
            } else {
                insertRecursive(current->right, newNode);
            }
        }
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
        if (n->left == NIL) {
            return n->data;
        }
        return getMin(n->left);
    }

    int getMax(RBNode* n) {
        if (n->right == NIL) {
            return n->data;
        }
        return getMax(n->right);
    }

    int countNodes(RBNode* n) {
        if (n == NIL) {
            return 0;
        }
        return 1 + countNodes(n->left) + countNodes(n->right);
    }

    int height(RBNode* n) {
        if (n == NIL) {
            return -1;
        }
        int leftHeight = height(n->left);
        int rightHeight = height(n->right);
        return 1 + max(leftHeight, rightHeight);
    }

public:
    RedBlackTree() {
        NIL = new RBNode(0);
        NIL->color = BLACK;
        NIL->left = NIL;
        NIL->right = NIL;
        NIL->parent = nullptr;
        root = NIL;
    }

    ~RedBlackTree() {
        clear(root);
        delete NIL;
    }

    void insert(int value) {
        RBNode* node = new RBNode(value);
        node->left = NIL;
        node->right = NIL;
        node->parent = nullptr;
        if (root == NIL) {
            root = node;
            root->color = BLACK;
            return;
        }
        insertRecursive(root, node);
        fixColor(node);
    }

    bool remove(int key) {
        RBNode* z = root;
        while (z != NIL) {
            if (key == z->data) {
                break;
            } else if (key < z->data) {
                z = z->left;
            } else {
                z = z->right;
            }
        }

        if (z == NIL) {
            return false;
        }

        RBNode* y = z;
        RBNode* x;
        Color y_original_color = y->color;

        if (z->left == NIL) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == NIL) {
            x = z->left;
            transplant(z, z->left);
        } else {
            // Usa o predecessor: máximo da subárvore esquerda
            y = maximum(z->left);
            y_original_color = y->color;
            x = y->left;

            if (y->parent != z) {
                transplant(y, y->left);
                y->left = z->left;
                y->left->parent = y;
            }

            transplant(z, y);
            y->right = z->right;
            y->right->parent = y;
            y->color = z->color;
        }

        if (y_original_color == BLACK) {
            deleteFix(x);
        }

        delete z;
        return true;
    }

    bool search(int key) const {
        return search(root, key);
    }

    int getMin() {
        return getMin(root);
    }

    int getMax() {
        return getMax(root);
    }

    int countNodes() {
        return countNodes(root);
    }

    int height() {
        return height(root);
    }

    void printTree() {
        if (root != NIL) {
            root->printRB(0, "");
        } else {
            cout << "Árvore vazia." << endl;
        }
    }
};

int main() {
    RedBlackTree tree;

    tree.insert(10);
    tree.insert(12);
    tree.insert(5);
    tree.insert(4);
    tree.insert(39);
    tree.insert(17);

    cout << "Árvore Rubro Negro" << endl;
    tree.printTree();

    cout << "\nDigite um numero da arvore: ";
    int key;
    cin >> key;
    cout << (tree.search(key) ? "O numero foi encontrado\n" : "O numero nao foi encontrado\n");

    cout << "\nDigite um numero para remover: ";
    int removeKey;
    cin >> removeKey;
    if (tree.remove(removeKey)) {
        cout << removeKey << " removido com sucesso.\n";
        cout << "\nÁrvore após remoção:" << endl;
        tree.printTree();
    } else {
        cout << removeKey << " não encontrado na árvore.\n";
    }

    cout << "\nO menor numero da arvore é: " << tree.getMin() << endl;
    cout << "O maior numero da arvore é: " << tree.getMax() << endl;
    cout << "Número de nós: " << tree.countNodes() << endl;
    cout << "Altura da árvore: " << tree.height() << endl;

    return 0;
}

