#include <iostream>
#include <string>
#include <tuple>

using namespace std;

class ABB {
private: 
    string data;
    ABB* left;
    ABB* right;
    
public:
    ABB(string value): data(value), left(nullptr), right(nullptr) {}

    static tuple< int, string> key(const string& data) {
        try {
            size_t value;
            stoi(data, &value);
            if (value == data.size())
            {
                return {0, data};
            }
        } catch (...) {};

        if (data.size() == 1)
        {
            return {1, data};
        }
        return {2, data};
    }

    ABB* insert (string dataNew) {
        auto [priorityNew, _] = key(dataNew);
        auto [priorityCurrent, __] = key(this->data);

        int priority = priorityNew;

        if (priority == 0) {
            if (stoi(dataNew) < stoi(data)) {
                if (left == nullptr)
                {
                    left = new ABB(dataNew);
                } else {
                    left = left->insert(dataNew);
                }
            } else {
                if (right == nullptr)
                {
                    right = new ABB(dataNew);
                } else {
                    right = right->insert(dataNew);
                }
            }      
        } else if (priority == 1) {
            if (dataNew < data) {
                if (left == nullptr)
                {
                    left = new ABB(dataNew);
                } else {
                    left = left->insert(dataNew);
                }
            } else {
                if (right == nullptr)
                {
                    right = new ABB(dataNew);
                } else {
                    right = right->insert(dataNew);
                }
            }      
        } else if (priority == 2) {
            if (dataNew.length() < data.length()) {
                if (left == nullptr)
                {
                    left = new ABB(dataNew);
                } else {
                    left = left->insert(dataNew);
                }
            } else {
                if (right == nullptr)
                {
                    right = new ABB(dataNew);
                } else {
                    right = right->insert(dataNew);
                }
            }      
        }
        return this;
    }

    void printInOrder() {
        if (left != nullptr) {
            left->printInOrder();  // Imprime a subárvore esquerda
        }
        cout << data << " ";  // Imprime o valor da raiz
        if (right != nullptr) {
            right->printInOrder();  // Imprime a subárvore direita
        }
    }
};

int main() {
    ABB* root = new ABB("12");
    root->insert("32");
    root->insert("a");
    root->insert("8");
    root->insert("verdade");

    cout << "Árvore em ordem: ";
    root->printInOrder();
    cout << endl;

    return 0;
}