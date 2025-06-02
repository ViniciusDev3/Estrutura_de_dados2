/*

Imagine uma estrutura de árvore binária de busca flexível, onde cada ponto (ou nó) guarda informações variadas, como números inteiros, letras ou palavras. A organização dessa estrutura segue uma ordem específica: primeiro os números, depois as letras, e por último as palavras. Para elementos do mesmo tipo, a comparação é feita de forma usual: valor numérico para números e ordem alfabética para letras e palavras.
Por exemplo, ao inserir os elementos [12, 'a', "texto", 5, 'z', "dados"] ...

Crie uma função que permita adicionar novos elementos e, em seguida, procure pelo valor específico "dados". Ao encontrar, mostre precisamente a sequência de passos tomados na estrutura da árvore.

*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Enumeração para identificar o tipo de dado armazenado
enum DataType { INT, CHAR, STRING };

// Estrutura para armazenar os dados
// O union permite que intValue e charValue compartilhem o mesmo espaço de memória
// Isso é útil porque um nó só pode ter um tipo de dado por vez
struct FlexData {
    DataType type;  // Tipo do dado armazenado
    union {
        int intValue;    // Valor inteiro
        char charValue;  // Valor caractere
    };
    string stringValue;  // Para strings, usamos o membro string separadamente

    
    // Construtor para inteiro que inicializa:
    // - type como INT (indicando que o dado é um inteiro)
    // - intValue com o valor passado como parâmetro
    // O construtor usa a sintaxe de inicialização de lista para atribuir os valores
    FlexData(int value) : type(INT), intValue(value) {}
    
    // Construtor para caractere
    FlexData(char value) : type(CHAR), charValue(value) {}
    
    // Construtor para string
    FlexData(const string& value) : type(STRING), stringValue(value) {}
    
    // Construtor padrão
    FlexData() : type(INT), intValue(0) {}
};

// Classe que define um nó da Árvore AVL Flexível
class FlexAVLNode {
private:
    FlexData data;  // Dado armazenado no nó
    int height;     // Altura do nó
    FlexAVLNode* left;   // Ponteiro para o filho esquerdo
    FlexAVLNode* right;  // Ponteiro para o filho direito

    // Função auxiliar para comparar dois valores FlexData
    int compare(const FlexData& a, const FlexData& b) {
        // Primeiro compara os tipos
        if (a.type != b.type) {
            return a.type - b.type; // int < char < string
        }
        
        // Depois compara valores do mesmo tipo
        switch (a.type) {
            case INT:
                return a.intValue - b.intValue;
            case CHAR:
                return a.charValue - b.charValue;
            case STRING:
                return a.stringValue.compare(b.stringValue);
            default:
                return 0;
        }
    }

    // Função auxiliar para obter representação em string do dado
    string getDataString() const {
        switch (data.type) {
            case INT:
                return to_string(data.intValue);
            case CHAR:
                return string(1, data.charValue);
            case STRING:
                return data.stringValue;
            default:
                return "";
        }
    }

    // Função auxiliar para obter altura
    int getHeight() {
        return height;
    }

    // Função auxiliar para obter fator de balanceamento
    int getBalanceFactor() {
        return (left ? left->height : 0) - (right ? right->height : 0);
    }

    // Atualiza altura baseado nos filhos
    void updateHeight() {
        height = 1 + max(
            (left ? left->height : 0),
            (right ? right->height : 0)
        );
    }

    // Rotação à direita
    FlexAVLNode* rotateRight() {
        FlexAVLNode* newRoot = left;
        FlexAVLNode* subtree = newRoot->right;

        newRoot->right = this;
        left = subtree;

        updateHeight();
        newRoot->updateHeight();

        return newRoot;
    }

    // Rotação à esquerda
    FlexAVLNode* rotateLeft() {
        FlexAVLNode* newRoot = right;
        FlexAVLNode* subtree = newRoot->left;

        newRoot->left = this;
        right = subtree;

        updateHeight();
        newRoot->updateHeight();

        return newRoot;
    }

    // Balanceia o nó
    FlexAVLNode* balance() {
        updateHeight();
        int balanceFactor = getBalanceFactor();

        if (balanceFactor > 1 && left->getBalanceFactor() >= 0)
            return rotateRight();

        if (balanceFactor < -1 && right->getBalanceFactor() <= 0)
            return rotateLeft();

        if (balanceFactor > 1 && left->getBalanceFactor() < 0) {
            left = left->rotateLeft();
            return rotateRight();
        }

        if (balanceFactor < -1 && right->getBalanceFactor() > 0) {
            right = right->rotateRight();
            return rotateLeft();
        }

        return this;
    }

public:
    // Construtor que inicializa o nó com um valor
    FlexAVLNode(const FlexData& value) : data(value), height(1), left(nullptr), right(nullptr) {}

    // Destrutor para liberar a memória dos nós filhos
    ~FlexAVLNode() {
        delete left;
        delete right;
    }

    // Insere novo dado
    FlexAVLNode* insert(const FlexData& new_data) {
        if (compare(new_data, data) < 0) {
            if (left == nullptr)
                left = new FlexAVLNode(new_data);
            else
                left = left->insert(new_data);
        } else {
            if (right == nullptr)
                right = new FlexAVLNode(new_data);
            else
                right = right->insert(new_data);
        }

        return balance();
    }

    // Procura por um dado e retorna o caminho percorrido # Collection
    vector<string> search(const FlexData& target) {
        vector<string> path;
        path.push_back(getDataString());

        if (compare(target, data) == 0) {
            return path;
        }

        if (compare(target, data) < 0) {
            if (left == nullptr) {
                path.push_back("Não encontrado");
                return path;
            }
            vector<string> leftPath = left->search(target);
            path.insert(path.end(), leftPath.begin(), leftPath.end());
        } else {
            if (right == nullptr) {
                path.push_back("Não encontrado");
                return path;
            }
            vector<string> rightPath = right->search(target);
            path.insert(path.end(), rightPath.begin(), rightPath.end());
        }

        return path;
    }

    // Imprime a estrutura da árvore
    void printTree(const string& prefix = "", bool isLeft = true) {
        if (right)
            right->printTree(prefix + (isLeft ? "│   " : "    "), false);

        cout << prefix;
        cout << (isLeft ? "└── " : "┌── ");
        cout << getDataString() << " (h:" << height << ")" << endl;

        if (left)
            left->printTree(prefix + (isLeft ? "    " : "│   "), true);
    }
};

int main() {
    // Cria a árvore inicial com os elementos do exemplo
    FlexAVLNode* root = new FlexAVLNode(FlexData(12));
    root = root->insert(FlexData('a'));
    root = root->insert(FlexData("texto"));
    root = root->insert(FlexData(5));
    root = root->insert(FlexData('z'));
    root = root->insert(FlexData("dados"));

    // Imprime a estrutura da árvore
    cout << "Estrutura da árvore:" << endl;
    root->printTree();
    cout << endl;

    // Procura por "dados" e mostra o caminho percorrido
    cout << "Procurando por \"dados\":" << endl;
    vector<string> path = root->search(FlexData("dados"));
    for (size_t i = 0; i < path.size(); ++i) {
        cout << "Passo " << i + 1 << ": " << path[i] << endl;
    }

    // Limpa a memória
    delete root;
    return 0;
}