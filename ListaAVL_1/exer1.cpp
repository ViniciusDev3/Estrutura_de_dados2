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

    ABB* insert(string dataNew) {
        auto [priorityNew, _] = key(dataNew);
        auto [priorityCurrent, __] = key(this->data);
    
        if (priorityNew < priorityCurrent) {
            if (left == nullptr) {
                left = new ABB(dataNew);
            } else {
                left = left->insert(dataNew);
            }
        } else if (priorityNew > priorityCurrent) {
            if (right == nullptr) {
                right = new ABB(dataNew);
            } else {
                right = right->insert(dataNew);
            }
        } else {
            // Se mesma prioridade, comparar valores
            if (priorityNew == 0) { // Comparação numérica
                if (stoi(dataNew) < stoi(data)) {
                    if (left == nullptr) {
                        left = new ABB(dataNew);
                    } else {
                        left = left->insert(dataNew);
                    }
                } else {
                    if (right == nullptr) {
                        right = new ABB(dataNew);
                    } else {
                        right = right->insert(dataNew);
                    }
                }
            } else { // Comparação alfabética para letras ou palavras
                if (dataNew < data) {
                    if (left == nullptr) {
                        left = new ABB(dataNew);
                    } else {
                        left = left->insert(dataNew);
                    }
                } else {
                    if (right == nullptr) {
                        right = new ABB(dataNew);
                    } else {
                        right = right->insert(dataNew);
                    }
                }
            }
        }
        return this;
    }

    void printInOrder(int nivel, string lado) {
        if (left != nullptr) {
            left->printInOrder(nivel + 1, "/");  
        }
        string space(6 * nivel, ' ');
        cout << space << lado << "-->" << data  << "\n";   
        if (right != nullptr) {
            right->printInOrder(nivel + 1, "\\");  
        }
    }

    void search(string value) {
        if (left != nullptr) {
            left->search(value);  
        }
        if (value == data)
        {
            cout << "Valor encontrado: " << data  << "\n";
        }
        if (right != nullptr) {
            right->search(value);  
        }
    }
};

int main() {
    ABB* root = nullptr;
   
    string valores[] = {"12", "a", "texto", "5", "z", "dados"};

    for (string v : valores) {
        if (root == nullptr) {
            root = new ABB(v);
        } else {
            root = root->insert(v);
        }
    }

    cout << "Árvore em ordem: \n";
    root->printInOrder(0, "");
    cout << endl;

    cout << "Digite uma nova entrada: ";
    string value;
    cin >> value;
    root->insert(value);
    cout << "Árvore em ordem: \n";
    root->printInOrder(0, "");
    cout << endl;

    cout << "Digite para procurar um valor na arvore: \n";
    cin >> value;
    root->search(value);

    return 0;
}