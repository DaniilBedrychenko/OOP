#pragma once
#include <iostream>
using namespace std;

template <class T>
class DLList
{
    struct Node {
        T data;
        Node* next;
        Node* prev;
        Node(const T& value, Node* _next = nullptr, Node* _prev = nullptr)
            : data(value), next(_next), prev(_prev) {}
    };

    Node* head;
    Node* tail;
    int count;

    void copyFrom(const DLList<T>& other) {
        Node* temp = other.head;
        while (temp) {
            push_back(temp->data);
            temp = temp->next;
        }
    }

public:
    DLList() : head(nullptr), tail(nullptr), count(0) {}

   
    DLList(const DLList<T>& other) : head(nullptr), tail(nullptr), count(0) {
        copyFrom(other);
    }

 
    DLList<T>& operator=(const DLList<T>& other) {
        if (this != &other) {
            removeAll();
            copyFrom(other);
        }
        return *this;
    }

  
    ~DLList() { removeAll(); }

    inline int getLength() const { return count; }

    void push_back(const T& value) {
        Node* newNode = new Node(value, nullptr, tail);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    void push_front(const T& value) {
        Node* newNode = new Node(value, head, nullptr);
        if (!head) {
            head = tail = newNode;
        } else {
            head->prev = newNode;
            head = newNode;
        }
        count++;
    }

    void removeItem(const T& value) {
        if (!head) return;
        Node* temp = head;
        while (temp && temp->data != value) temp = temp->next;
        if (!temp) return;

        if (temp == head) {
            head = head->next;
            if (head) head->prev = nullptr;
            else tail = nullptr;
        } else if (temp == tail) {
            tail = tail->prev;
            if (tail) tail->next = nullptr;
        } else {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;
        }

        delete temp;
        count--;
    }

    void removeAll() {
        Node* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
            count--;
        }
        tail = nullptr;
    }

    void print(bool forward = true) const {
        if (count == 0) {
            cout << "List is empty" << endl;
            return;
        }
        cout << "Count: " << count << endl;
        Node* temp = forward ? head : tail;
        int i = 0;
        while (temp) {
            cout << temp->data;
            if (i < count - 1) cout << " -> ";
            temp = forward ? temp->next : temp->prev;
            i++;
        }
        cout << endl;
    }

    bool find(const T& value) const {
        Node* temp = head;
        while (temp) {
            if (temp->data == value) return true;
            temp = temp->next;
        }
        return false;
    }
};
