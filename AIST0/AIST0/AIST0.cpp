#include <iostream>

struct Node {
    int data;
    Node* next;
    Node* prev;
    Node(int value) : data(value), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void append(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void display() {
        Node* current = head;
        while (current) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    Node* getTail() const {
        return tail;
    }
};

class DynamicArray {
private:
    int* arr;
    int size;
public:
    DynamicArray() : arr(nullptr), size(0) {}

    void append(int value) {
        int* newArr = new int[size + 1];
        for (int i = 0; i < size; ++i) {
            newArr[i] = arr[i];
        }
        newArr[size] = value;
        delete[] arr;
        arr = newArr;
        ++size;
    }

    void display() {
        for (int i = 0; i < size; ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
    }
};

class Stack {
private:
    DoublyLinkedList list;
public:
    void push(int value) {
        list.append(value);
    }

    void display() {
        list.display();
    }
};

int main() {
    DoublyLinkedList dll;
    dll.append(1);
    dll.append(2);
    dll.append(3);
    std::cout << "Doubly Linked List: ";
    dll.display();

    DynamicArray da;
    da.append(4);
    da.append(5);
    da.append(6);
    std::cout << "Dynamic Array: ";
    da.display();

    Stack stack;
    stack.push(7);
    stack.push(8);
    stack.push(9);
    std::cout << "Stack: ";
    stack.display();

    return 0;
}