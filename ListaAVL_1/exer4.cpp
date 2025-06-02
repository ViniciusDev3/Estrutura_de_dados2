#include <iostream>
#include <string>
#include <tuple>
#include <algorithm> 

using namespace std;

class AVL {
private:
    string data;
    AVL* left;
    AVL* right;
public:
    AVL(string value): data(value), left(nullptr), right(nullptr) {}

    static tuple<int, string> key(const string& value) {
        try {
            size_t pos;
            stoi(value, &pos);
            if (pos == value.size())
            {
                return {0, value};
            }
        } catch (...) {}
        if (value.size() >= 1)
        {
            return {1, value};
        } else {
            return {2, value};
        }
    }

    AVL* insert(string dataNew) {
        auto [priority, _] = key(dataNew);
        auto [priorityAtual, __] = key(this->data);

        if (priority > priorityAtual){
            if (left == nullptr)
            {
                left = new AVL(dataNew);
            } else {
                left->insert(dataNew);
            } 
        } else if (priority < priorityAtual){
            if (right == nullptr)
            {
                right = new AVL(dataNew);
            } else {
                right->insert(dataNew);
            } 
        } else {
            if (priority == 0) {
                if (stoi(dataNew) < stoi(data)) {
                    if (left == nullptr)
                    {
                        left = new AVL(dataNew);
                    } else {
                        left->insert(dataNew);
                    }
                } else {
                    if (right == nullptr)
                    {
                        right = new AVL(dataNew);
                    } else {
                        right->insert(dataNew);
                    }
                }
            } else {
                if (dataNew < data) {
                    if (left == nullptr)
                    {
                        left = new AVL(dataNew);
                    } else {
                        left->insert(dataNew);
                    }
                } else {
                    if (right == nullptr)
                    {
                        right = new AVL(dataNew);
                    } else {
                        right->insert(dataNew);
                    }
                }
            }
        }
        
        int newBalance = HeightNo();

        if (newBalance > 1)
        {
            if(dataNew < left->data){
                return rightRotation();
            } else {
                left = left->leftRotation();
                return rightRotation();
            }
        }
        if (newBalance < -1)
        {
            if(dataNew > right->data){
                return leftRotation();
            } else {
                right = right->rightRotation();
                return leftRotation();
            }
        }
    
        return this;
    }

    int Height () {
        int leftHeight = 0;
        int rightHeight = 0;
        if (left != nullptr)
        {
            leftHeight = left->Height();
        }
        if (right != nullptr)
        {
            rightHeight = right->Height();
        }
        return 1 + max(leftHeight, rightHeight);
    }

    int HeightNo () {
        int leftHeight = 0;
        int rightHeight = 0;
        if (left != nullptr)
        {
            leftHeight = left->Height();
        }
        if (right != nullptr)
        {
            rightHeight = right->Height();
        }
        return leftHeight - rightHeight;
    }

    AVL* leftRotation (){
        AVL* newValue = right;
        AVL* newTraid = newValue->left;

        newValue->left = this;
        right = newTraid;

        return newValue;
    }

    AVL* rightRotation (){
        AVL* newValue = left;
        AVL* newTraid = newValue->right;

        newValue->right = this;
        left = newTraid;

        return newValue;
    }

    void printInOrder(int nivel = 0) {
        if (right) right->printInOrder(nivel + 1);
        cout << string(nivel * 4, ' ') << data << "\n";
        if (left) left->printInOrder(nivel + 1);
    }
};

int main() {
    AVL* root = nullptr;
    string vals[] = {"20", "banana", "15", "uva", "25", "abacaxi", "10"};

    for (auto& v : vals) {
        if (!root) root = new AVL(v);
        else       root = root->insert(v);
    }

    cout << "Árvore AVL após inserções:\n";
    root->printInOrder();
    return 0;
}