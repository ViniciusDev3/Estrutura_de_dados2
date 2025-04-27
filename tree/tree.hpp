#ifndef TREE_HPP
#define TREE_HPP

#include <string>

class TreeNode {
private:
    int data;
    TreeNode* left;
    TreeNode* right;
    

public:
    TreeNode(int val);
    int getData() const;
    TreeNode* getLeft() const;
    TreeNode* getRight() const;
    void setLeft(TreeNode* node);
    void setRight(TreeNode* node);
    ~TreeNode();
};

class BinaryTree {
private:
    TreeNode* root;

    TreeNode* insert(TreeNode* node, int val);
    void deleteTree(TreeNode* node);
    void inOrder(TreeNode* node, int level, std::string side); 
    void posOrder(TreeNode* node, int level); 
    void preOrder(TreeNode* node, int level);
    int Height(TreeNode* node);
    
public:
    BinaryTree();
    ~BinaryTree();
    void insertVal(int val);
    int getHeight();
    bool estruturalmenteSimilar(BinaryTree& outraArvore); 
    
};

#endif
