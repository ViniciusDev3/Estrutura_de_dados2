#include "tree.hpp"
#include <iostream>
#include <algorithm> 

TreeNode::TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
int TreeNode::getData() const { return data; }
TreeNode* TreeNode::getLeft() const { return left; }
TreeNode* TreeNode::getRight() const { return right; }
void TreeNode::setLeft(TreeNode* node) { left = node; }
void TreeNode::setRight(TreeNode* node) { right = node; }
TreeNode::~TreeNode() {}

BinaryTree::BinaryTree() : root(nullptr) {}

TreeNode* BinaryTree::insert(TreeNode* node, int val) {
    if (node == nullptr) {
        return new TreeNode(val);
    }
    if (val < node->getData()) {
        node->setLeft(insert(node->getLeft(), val));
    } else if (val > node->getData()) {
        node->setRight(insert(node->getRight(), val));
    }
    return node;
}

void BinaryTree::deleteTree(TreeNode* node) {
    if (node != nullptr) {
        deleteTree(node->getLeft());
        deleteTree(node->getRight());
        delete node;
    }
}

void BinaryTree::inOrder(TreeNode* node, int level, std::string side) {
    if (node != nullptr) {
        inOrder(node->getLeft(), level + 1, "/");
        std::string indent(6 * level, ' ');
        std::cout << indent << side << " -> " << node->getData() << "\n";
        inOrder(node->getRight(), level + 1, "\\");
    }
}

void BinaryTree::posOrder(TreeNode* node, int level) {
    if (node != nullptr) {
        posOrder(node->getLeft(), level + 1);
        posOrder(node->getRight(), level + 1);
        std::cout << node->getData() << " ";
    }
}

void BinaryTree::preOrder(TreeNode* node, int level) {
    if (node != nullptr) {
        std::cout << node->getData() << " ";
        preOrder(node->getLeft(), level + 1);
        preOrder(node->getRight(), level + 1);
    }
}

int BinaryTree::Height(TreeNode* node) {
    if (node == nullptr)
        return 0;
    int leftHeight = Height(node->getLeft());
    int rightHeight = Height(node->getRight());
    return 1 + std::max(leftHeight, rightHeight);
}

int BinaryTree::getHeight() {
    return Height(root);
}

bool BinaryTree::estruturalmenteSimilar(BinaryTree& outraArvore) {
    return (this->getHeight() == outraArvore.getHeight());
}

BinaryTree::~BinaryTree() {
    std::cout << "In-Order\n";
    inOrder(root, 0, " ");
    std::cout << "Pre-Order\n";
    preOrder(root, 0);
    std::cout << "\nPos-Order\n";
    posOrder(root, 0);
    std::cout << "\nTamanho da arvore: " << Height(root) << "\n";
    deleteTree(root);
    std::cout << "Arvore destruida\n";
}

void BinaryTree::insertVal(int val) {
    root = insert(root, val);
}
