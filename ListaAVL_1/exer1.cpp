#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum DataType {INT, CHAR, STRING};

struct FlexData {
    DataType type;
    union {
        int intValue;
        char charValue;
    };
    string stringValue;

    FlexData(int value) : type(INT), intValue(value) {}
    FlexData(char value) : type(CHAR), charValue(value) {}
};

claData {
private: string data;
    AVL* left;
    AVL* right;
public:
    AVL( std::string value): data(value), left(nullptr), right(nullptr) {}

    AVL* insert (string dataNew) {
        bool number {false};
        if (!dataNew.empty() && all_of(dataNew.begin(), dataNew.end(), [](char c) {
            return;
        })){
            number = true;
        }
        
        if (number == true) {
            if (stoi(dataNew) < stoi(data)) {
                if (left == nullptr)
                {
                    left = new AVL(dataNew);
                } else {
                    left = left->insert(dataNew);
                }
            } else {
                if (right == nullptr)
                {
                    right = new AVL(dataNew);
                } else {
                    right = right->insert(dataNew);
                }
            }      
        } else {
            if (dataNew.length() < data.length()) {
                if (left == nullptr)
                {
                    left = new AVL(dataNew);
                } else {
                    left = left->insert(dataNew);
                }
            } else {
                if (right == nullptr)
                {
                    right = new AVL(dataNew);
                } else {
                    right = right->insert(dataNew);
                }
            }      
        }
        
    }
};

int main() {
    AVL* root = new AVL("12");
    root->insert("32");
}