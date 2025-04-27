#include <iostream>
using namespace std;

class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;
    TreeNode* next;

    TreeNode(int value) : data(value), left(nullptr), right(nullptr), next(nullptr) {}

    void insert(int new_data) {
        if (new_data < data) {
            if (left == nullptr)
                left = new TreeNode(new_data);
            else
                left->insert(new_data);
        } else {
            if (right == nullptr)
                right = new TreeNode(new_data);
            else
                right->insert(new_data);
        }
    }
};

class BinaryTree {
private:
    TreeNode* root;
    TreeNode* head;
    TreeNode* tail;

public:
    BinaryTree() : root(nullptr), head(nullptr), tail(nullptr) {}

    void insert(int value) {
        if (root == nullptr)
            root = new TreeNode(value);
        else
            root->insert(value);
    }

    void converterParaListaEncadeada() {
        head = tail = nullptr; // Reinicia a lista
        converterParaListaEncadeada(root); // Chama a recursão a partir do root
    }

    void printList() {
        TreeNode* temp = head;
        cout << "Lista -> ";
        while(temp) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL\n";
    }

private:
    // Função recursiva agora é privada e tem o mesmo nome
    void converterParaListaEncadeada(TreeNode* node) {
        if (node == nullptr) return;

        converterParaListaEncadeada(node->left); // Recursão no filho esquerdo

        // Adiciona o nó atual à lista
        TreeNode* listNode = new TreeNode(node->data); // Cria novo nó para a lista
        if (tail == nullptr)
            head = tail = listNode;
        else {
            tail->next = listNode;
            tail = listNode;
        }

        converterParaListaEncadeada(node->right); // Recursão no filho direito
    }
};

int main() {
    BinaryTree tree;
    tree.insert(50);
    tree.insert(30);
    tree.insert(20);
    tree.insert(40);
    tree.insert(70);
    tree.insert(60);
    tree.insert(80);

    tree.converterParaListaEncadeada();
    tree.printList();

    return 0;
}

