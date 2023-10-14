#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Stack {
private:
    vector<char> data;

public:
    void push(char c) {
        data.push_back(c);
    }

    char pop() {
        char top = data.back();
        data.pop_back();
        return top;
    }

    char top() const {
        return data.back();
    }

    bool empty() const {
        return data.empty();
    }

    int size() const {
        return data.size();
    }
};

bool isOperator(char c) {
    return c == '+' || c == '-' ||  c == '*' || c == '^';
}

int getPriority(char c) {
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '^')
        return 2;
    return 0;
}

vector<string> tokenize(const string& expression) {
    vector<string> tokens;
    string currentToken = "";

    for (char c : expression) {
        if (isspace(c)) {
            if (!currentToken.empty()) {
                tokens.push_back(currentToken);
                currentToken = "";
            }
        }
        else if (isalnum(c) || c == '(' || c == ')' || c == '^') {
            currentToken += c;
        }
        else if (isOperator(c)) {
            if (!currentToken.empty()) {
                tokens.push_back(currentToken);
                currentToken = "";
            }
            tokens.push_back(string(1, c));
        }
    }

    if (!currentToken.empty()) {
        tokens.push_back(currentToken);
    }

    return tokens;
}

vector<string> infixToPostfix(const string& expression) {
    vector<string> tokens = tokenize(expression);
    Stack operatorStack;
    vector<string> postfix;

    for (const string& token : tokens) {
        if (isOperator(token[0])) {
            while (!operatorStack.empty() && isOperator(operatorStack.top()) &&
                ((token[0] != '^' && isOperator(operatorStack.top()) && operatorStack.top() != '(') ||
                    (token[0] == '^' && isOperator(operatorStack.top()) && operatorStack.top() == '^') ||
                    (getPriority(token[0]) <= getPriority(operatorStack.top())))) {
                postfix.push_back(string(1, operatorStack.pop()));
            }
            operatorStack.push(token[0]);
        }
        else if (token == "(") {
            operatorStack.push(token[0]);
        }
        else if (token == ")") {
            while (!operatorStack.empty() && operatorStack.top() != '(') {
                postfix.push_back(string(1, operatorStack.pop()));
            }
            operatorStack.pop();
        }
        else {
            postfix.push_back(token);
        }
    }

    while (!operatorStack.empty()) {
        postfix.push_back(string(1, operatorStack.pop()));
    }

    return postfix;
}

int main() {
    setlocale(LC_ALL, "");

    string expression;
    cout << "Введите выражение: ";
    getline(cin, expression);

    vector<string> postfixExpression = infixToPostfix(expression);

    cout << "Выражение в постфиксной форме: ";
    for (const string& token : postfixExpression) {
        cout << token << " ";
    }
    cout << endl;

    return 0;
}
