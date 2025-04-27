#include <iostream>
//#include <iomanip>

using namespace std;

// Classe que define um nó da Árvore Binária de Busca
class TreeNode {
private:
    int data;             // Valor inteiro do nó
    TreeNode* left;       // Ponteiro para o filho esquerdo
    TreeNode* right;      // Ponteiro para o filho direito

    // Função auxiliar para encontrar o nó com menor valor na subárvore
    // Utilizada no caso 3 da deleção (quando há dois filhos)
    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        // Continua indo para a esquerda até encontrar o menor valor
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

public:
    // Construtor que inicializa o nó com um valor e filhos nulos
    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}

    // Destrutor para liberar recursivamente os nós filhos
    ~TreeNode() {
        delete left;   // chama recursivamente os destrutores
        delete right;
    }

    // Insere 'new_data' na posição correta, mantendo as regras de BST:
    // valores menores à esquerda, valores maiores ou iguais à direita
    TreeNode* insert(int new_data) {
        if (new_data < data) {
            if (left == nullptr)
                left = new TreeNode(new_data);
            else
                left = left->insert(new_data);
        } else {
            if (right == nullptr)
                right = new TreeNode(new_data);
            else
                right = right->insert(new_data);
        }

        int balance = heightNo();

        if (balance > 1){
            if (new_data < left->data)
            {
                return rightRotation();
            } else {
                left = left->leftRotation();
                return rightRotation();
            }
        }

        if (balance < -1){
            if (new_data > right->data)
            {
                return leftRotation();
            } else {
                right = right->rightRotation();
                return leftRotation();
            }         
        }

        return this;
    }

    // Exibe a árvore de forma hierárquica:
    // A lógica utiliza prefixos (indentação) e caracteres especiais
    // para mostrar a árvore no console
    void printTree(const string& prefix = "", bool isLeft = true) {
        // Caso exista filho à direita, chama recursivamente para ele
        if (right)
            right->printTree(prefix + (isLeft ? "│   " : "    "), false);

        // Exibe o prefixo (indentação) e o tipo de aresta (└── ou ┌──)
        cout << prefix;
        cout << (isLeft ? "└── " : "┌── ");
        cout << data << endl;

        // Caso exista filho à esquerda, chama recursivamente para ele
        if (left)
            left->printTree(prefix + (isLeft ? "    " : "│   "), true);
    }

    // Percurso em Pré-Ordem (Root, Left, Right):
    // Exibe o valor do nó, percorre a subárvore esquerda e depois a direita
    void preOrder() {
        cout << data << " ";
        if (left) left->preOrder();
        if (right) right->preOrder();
    }

    // Percurso em Ordem (Left, Root, Right):
    // Visita primeiro a subárvore esquerda, depois o nó e em seguida a direita
    void inOrder() {
        if (left) left->inOrder();
        cout << data << " ";
        if (right) right->inOrder();
    }

    // Percurso em Pós-Ordem (Left, Right, Root):
    // Visita primeiro a subárvore esquerda, depois a direita e, por fim, o nó
    void postOrder() {
        if (left) left->postOrder();
        if (right) right->postOrder();
        cout << data << " ";
    }

    // Busca um valor 'key' na árvore:
    // Retorna 'true' se encontrado, ou 'false' caso contrário
    bool search(int key) {
        if (data == key)
            return true;
        if (key < data && left)
            return left->search(key);
        if (key > data && right)
            return right->search(key);
        return false;
    }

    // Calcula a altura da árvore, retornando
    // a maior profundidade entre os sub-ramos
    int height() {
        int leftHeight = left ? left->height() : 0;
        int rightHeight = right ? right->height() : 0;
        return 1 + max(leftHeight, rightHeight);
    }

    // Exclui um nó com o valor 'key' da árvore, mantendo as regras da BST.
    // Casos de deleção:
    //  1. Nó folha (sem filhos)
    //  2. Nó com apenas um filho (esquerdo ou direito)
    //  3. Nó com dois filhos (troca pelo sucessor ou predecessor e deleta o substituído)
    TreeNode* deleteNode(int key) {
        if(key < data && left){
            left = left->deleteNode(key);
        }
        else if (key > data && right){
            right = right->deleteNode(key);
        }
        else if (key == data){
            // Caso 1: sem filho a esq
            if(!left){
                TreeNode* temp = right;

                this->right = nullptr;
                delete this;
                return temp;
            }

            //Caso 2: sem filho a dir
            if (!right){
                TreeNode* temp = left;
                this->left = nullptr;               
                delete this;
                return temp;
            }

            TreeNode* temp = minValueNode(right);
            data = temp->data;
            right = right->deleteNode(temp->data);
            cout << "\nDeletado\n";
        }

        int balance = heightNo();

        if (balance > 1){
            if (left->heightNo() >= 0)
            {
                return rightRotation();
            } else {
                left = left->leftRotation();
                return rightRotation();
            }
        }

        if (balance < -1){
            if (right->heightNo() <= 0)
            {
                return leftRotation();
            } else {
                right = right->rightRotation();
                return leftRotation();
            }         
        }
        // Retorna o ponteiro atual (em caso de não remoção)
        return this;
    }

    // Libera recursivamente todos os nós da subárvore
    // transformando o nó atual em uma árvore vazia
    void clear() {
        if (left){
            left->clear();
            delete left;
        }
        if (right){
            right->clear();
            delete right;
        }
    }

    // Retorna o valor mínimo da árvore
    int getMin() {
        if (!left) return data;
        return left->getMin();
    }

    // Retorna o valor máximo da árvore
    int getMax() {
        if (!right) return data;
        return right->getMax();     
    }

    // Retorna a contagem total de nós na subárvore
    int countNodes() {
        int count = 1;
        if(left)
            count += left->countNodes();
        if(right)
            count += right->countNodes();
        return count;
    }

    // Retorna a contagem de folhas (nós sem filhos)
    int countLeaves() {
        if(!left && !right)
            return 1;
        int leaves = 0;
        if(left)
            leaves += left->countLeaves();
        if(right)
            leaves += right->countLeaves();
        
        return leaves;
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

    TreeNode* leftRotation (){
        TreeNode* newRoot = right;
        TreeNode* subTree = newRoot->left;

        newRoot->left = this;
        right = subTree;

        return newRoot;
    }

    TreeNode* rightRotation (){
        TreeNode* newRoot = left;
        TreeNode* subTree = newRoot->right;

        newRoot->right = this;
        left = subTree;

        return newRoot;
    }
};

int main() {
    TreeNode* root = new TreeNode(50);
    root = root->insert(30);
    root = root->insert(70);
    root = root->insert(60);
    root = root->insert(80);
    root = root->insert(100);
    root = root->insert(85);
    root = root->insert(90);
    

    cout << "BST -- Aula 6\n";

    root->printTree();

    int deleteValue = 0;
    cout << "Digite um valor para deletar: ";
    cin >> deleteValue;

    root = root->deleteNode(deleteValue);
    root->printTree();

    cout << "Menor Valor: " << root->getMin() << endl; 
    cout << "Maior Valor: " << root->getMax() << endl;

    cout << "Altura da Arvore: " << root->height() << endl;

    cout << "Quantidade total de nós: " << root->countNodes() << endl;
    cout << "Quantidade total de folhas: " << root->countLeaves() << endl;
    
    return 0;
}
