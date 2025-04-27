#include <iostream>

class AVL{    
private:
    int data;
    AVL* left;
    AVL* right;

public:
    AVL(int value): data(value), left(nullptr), right(nullptr) {}

    AVL* insert(int newData){
        if (newData < data)
        {
            if (left == nullptr){
                left = new AVL(newData);
            } else {
                left = left->insert(newData);
            }
        } else {
            if (right == nullptr){
                right = new AVL(newData);
            } else {
                right = right->insert(newData);
            }         
        }
        
        int balance = heightNo();

        if (balance > 1){
            if (newData < left->data)
            {
                return rightRotation();
            } else {
                left = left->leftRotation();
                return rightRotation();
            }
        }

        if (balance < -1){
            if (newData > right->data)
            {
                return leftRotation();
            } else {
                right = right->rightRotation();
                return leftRotation();
            }         
        }

        return this;
    }

    int height (){
        int heightLeft = 0, heightRight = 0;
        if (left != nullptr)
        {
            heightLeft = left->height();
        }
        if (right != nullptr)
        {
            heightRight = right->height();
        }
        return 1 + std::max(heightLeft, heightRight);
    }

    int heightNo (){
        int heightLeft = 0, heightRight = 0;
        if (left != nullptr)
        {
            heightLeft = left->height();
        }
        if (right != nullptr)
        {
            heightRight = right->height();
        }
        return heightLeft - heightRight;
    }

    void printAVL (int level, std::string side){
        if (left != nullptr)
        {
            left->printAVL(level + 1, "/");
        }
        std::string space(6 * level, ' '); 
        std::cout << space << side << "-->" << data << "\n";
        if (right != nullptr)
        {
            right->printAVL(level + 1, "\\");
        }
    }

    AVL* leftRotation (){
        AVL* newRoot = right;
        AVL* subTree = newRoot->left;

        newRoot->left = this;
        right = subTree;

        return newRoot;
    }

    AVL* rightRotation (){
        AVL* newRoot = left;
        AVL* subTree = newRoot->right;

        newRoot->right = this;
        left = subTree;

        return newRoot;
    }

};

int main() {
    AVL* root = new AVL(8);
    root = root->insert(6);
    root = root->insert(4);
    root = root->insert(3);
    root = root->insert(1);
    root = root->insert(9);

    std::cout << "Altura Arvore: " << root->height() << "\nArvore: " << std::endl;
    root->printAVL(0, "");
    std::cout << "\n";
}