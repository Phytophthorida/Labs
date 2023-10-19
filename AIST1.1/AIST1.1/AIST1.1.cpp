#include <iostream>
#include <string>
using namespace std;

class Stack {
private:
    char* data;
    int capacity;
    int topIndex;

public:
    Stack(int capacity) {
        this->capacity = capacity;
        data = new char[capacity];
        topIndex = -1;
    }

    ~Stack() {
        delete[] data;
    }

    void push(char c) {
        if (topIndex < capacity - 1) {
            data[++topIndex] = c;
        }
    }

    char pop() {
        if (topIndex >= 0) {
            return data[topIndex--];
        }
        return '\0';
    }

    char top() const {
        if (topIndex >= 0) {
            return data[topIndex];
        }
        return '\0';
    }

    bool empty() const {
        return topIndex == -1;
    }
};

bool isOperator(char c) {
    return c == '+'  || c == '-' || c == '*' || c == '^';
}

int getPriority(char c) {
    if (c == '+' || c == '-') return 1;
    else if (c == '*' || c == '^') return 2;
    return 0;
}

string* tokenize(const string& expression, int& tokenCount) {
    string* tokens = new string[expression.length()];
    tokenCount = 0;
    string currentToken = "";
    for (char c : expression) {
        if (c == ' '  || c == '\t' ||  c == '\n' ||  c == '\r' || c == '\v' || c == '\f') {
            if (!currentToken.empty()) {
                tokens[tokenCount++] = currentToken;
                currentToken = "";
            }
        }
        else if (isalnum(c)  || c == '('  || c == ')' || c == '^') {
            currentToken += c;
        }
        else if (isOperator(c)) {
            if (!currentToken.empty()) {
                tokens[tokenCount++] = currentToken;
                currentToken = "";
            }
            tokens[tokenCount++] = string(1, c);
        }
    }
    if (!currentToken.empty()) {
        tokens[tokenCount++] = currentToken;
    }
    return tokens;
}

string* infixToPostfix(const string& expression, int& postfixSize) {
    int tokenCount;
    string* tokens = tokenize(expression, tokenCount);
    Stack operatorStack(tokenCount);
    string* postfix = new string[tokenCount];
    postfixSize = 0;
    for (int i = 0; i < tokenCount; i++) {
        if (isOperator(tokens[i][0])) {
            while (!operatorStack.empty() && isOperator(operatorStack.top()) &&
                (
                    (tokens[i][0] != '^' &&
                        isOperator(operatorStack.top()) &&
                        operatorStack.top() != '('
                        ) ||
                    (tokens[i][0] == '^' &&
                        isOperator(operatorStack.top()) &&
                        operatorStack.top() == '^'
                        ) ||
                    (getPriority(tokens[i][0]) <= getPriority(operatorStack.top()))
                    )
                ) {
                postfix[postfixSize++] = string(1, operatorStack.pop());
            }
            operatorStack.push(tokens[i][0]);
        }
        else if (tokens[i] == "(") {
            operatorStack.push(tokens[i][0]);
        }
        else if (tokens[i] == ")") {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                postfix[postfixSize++] = string(1, operatorStack.pop());
            }
            operatorStack.pop();
        }
        else {
            postfix[postfixSize++] = tokens[i];
        }
    }
    while (!operatorStack.empty()) {
        postfix[postfixSize++] = string(1, operatorStack.pop());
    }
    return postfix;
}

int main() {

    setlocale(LC_ALL, "");
    string expression;
    cout << "Введите выражение: ";
    getline(cin, expression);
    int postfixSize;
    string* postfixExpression = infixToPostfix(expression, postfixSize);
    cout << "Выражение в постфиксной форме: ";
    for (int i = 0; i < postfixSize; i++) {
        cout << postfixExpression[i] << " ";
    }
    cout << endl;
    delete[] postfixExpression;
    return 0;
}
