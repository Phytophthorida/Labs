//Нужный формат скобочной записи: A(B(C)(D))(E)

#include <iostream>
#include <fstream>
#include <string>

struct Node {
    char data;
    Node* left;
    Node* right;
};

struct StackNode{
    Node * data;
    StackNode* next;

    StackNode(Node* node) : data(node), next(nullptr) {}
};

class CustomStack {
private:
    StackNode* top;

public:
    CustomStack() : top(nullptr) {}

    void push(Node* node) {
        StackNode* newNode = new StackNode(node);
        newNode->next = top;
        top = newNode;
    }

    Node* pop() {
        if (isEmpty()) {
            return nullptr;
        }

        StackNode* temp = top;
        top = top->next;
        Node* popped = temp->data;
        delete temp;
        return popped;
    }

    bool isEmpty() {
        return top == nullptr;
    }
};


Node* createNode(char data) {
    Node* newNode = new Node;
    newNode->data = data;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

Node* buildTreeFromExpression(const std::string& expression, int& index) {
    if (index >= expression.length() || expression[index] == ')') {
        return nullptr;
    }

    while (index < expression.length() && (expression[index] == '(' || expression[index] == ')')) {
        index++;
    }

    if (index >= expression.length()) {
        return nullptr;
    }

    Node* root = createNode(expression[index]);
    index++;

    if (index < expression.length() && expression[index] == '(') {
        index++;
        root->left = buildTreeFromExpression(expression, index);
        index++;
        root->right = buildTreeFromExpression(expression, index);
        index++;
    }

    return root;
}

void preorderTraversal(Node* root) {
    if (root == nullptr) {
        return;
    }

    std::cout << root->data << " ";
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

void inorderTraversal(Node* root) {
    if (root == nullptr) {
        return;
    }

    inorderTraversal(root->left);
    std::cout << root->data << " ";
    inorderTraversal(root->right);
}

void postorderTraversal(Node* root) {
    if (root == nullptr) {
        return;
    }

    postorderTraversal(root->left);
    postorderTraversal(root->right);
    std::cout << root->data << " ";
}

void breadthFirstTraversal(Node* root) {
    if (root == nullptr) {
        return;
    }

    CustomStack currentLevel;
    CustomStack nextLevel;

    currentLevel.push(root);

    while (!currentLevel.isEmpty()) {
        Node* current = currentLevel.pop();
        std::cout << current->data << " ";

        if (current->left != nullptr) {
            nextLevel.push(current->left);
        }

        if (current->right != nullptr) {
            nextLevel.push(current->right);
        }

        if (currentLevel.isEmpty()) {
            std::swap(currentLevel, nextLevel);
            std::cout << "\n";
        }
    }
}


int main() {

    setlocale(LC_ALL, "");

    /*Ручной ввод скобочной записи, не из файла
    std::string expression;
    std::cout << "Введите скобочную запись двоичного дерева: ";
    std::cin >> expression;

    int index = 0;
    Node* binaryTreeRoot = buildTreeFromExpression(expression, index);

    if (binaryTreeRoot == nullptr) {
        std::cout << "Ошибка: Невозможно создать дерево.\n";
        return 1;
    }*/

    std::string file_path;
    std::cout << "Введите путь к файлу с скобочной записью двоичного дерева: ";
    std::cin >> file_path;

    std::ifstream file(file_path);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла.\n";
        return 1;
    }

    std::string expression;
    std::getline(file, expression);

    int index = 0;
    Node* binaryTreeRoot = buildTreeFromExpression(expression, index);

    if (binaryTreeRoot == nullptr) {
        std::cout << "Ошибка: Невозможно создать дерево.\n";
        return 1;
    }

    std::cout << "Прямой обход дерева:\n";
    preorderTraversal(binaryTreeRoot);
    std::cout << "\n";

    std::cout << "Центрированный обход дерева:\n";
    inorderTraversal(binaryTreeRoot);
    std::cout << "\n";

    std::cout << "Обратный обход дерева:\n";
    postorderTraversal(binaryTreeRoot);
    std::cout << "\n";

    std::cout << "Обход дерева в ширину:\n";
    breadthFirstTraversal(binaryTreeRoot);
    std::cout << "\n";

    return 0;
}