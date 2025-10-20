#pragma once
#include <iostream>
using namespace std;

template <class T>
class SingleLinkedList
{
    struct Node {
        T data;
        Node* next;
        Node(const T& value, Node* _next = nullptr) : data(value), next(_next) {}
    };

    Node* head;
    int count;

    void copyFrom(const SingleLinkedList<T>& other) {
        Node* temp = other.head;
        while (temp) {
            push_back(temp->data);
            temp = temp->next;
        }
    }

public:
    SingleLinkedList() : head(nullptr), count(0) {}

   
    SingleLinkedList(const SingleLinkedList<T>& other) : head(nullptr), count(0) {
        copyFrom(other);
    }

  
    SingleLinkedList<T>& operator=(const SingleLinkedList<T>& other) {
        if (this != &other) {
            removeAll();
            copyFrom(other);
        }
        return *this;
    }

    
    ~SingleLinkedList() { removeAll(); }

    inline int getLength() const { return count; }

    T& operator[](int index) {
        int i = 0;
        for (Node* temp = head; temp; temp = temp->next) {
            if (i == index) return temp->data;
            i++;
        }
        throw out_of_range("Index out of range");
    }

    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            count++;
            return;
        }
        Node* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
        count++;
    }

    void push_front(const T& value) {
        Node* newNode = new Node(value, head);
        head = newNode;
        count++;
    }

    void remove(const T& value) {
        if (!head) return;
        if (head->data == value) {
            Node* temp = head;
            head = head->next;
            delete temp;
            count--;
            return;
        }
        Node* temp = head;
        while (temp->next) {
            if (temp->next->data == value) {
                Node* toDelete = temp->next;
                temp->next = temp->next->next;
                delete toDelete;
                count--;
                return;
            }
            temp = temp->next;
        }
    }

    void removeAll() {
        Node* temp;
        while (head) {
            temp = head;
            head = head->next;
            delete temp;
            count--;
        }
        head = nullptr;
    }

    void print() const {
        if (count == 0) {
            cout << "List is empty" << endl;
            return;
        }
        cout << "Count: " << count << endl;
        Node* temp = head;
        int i = 0;
        while (temp) {
            cout << temp->data;
            if (i < count - 1) cout << " -> ";
            temp = temp->next;
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
