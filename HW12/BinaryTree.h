#pragma once
#include <iostream>
using namespace std;

template <class T>
class BinaryTree
{
    struct Node {
        T data;
        Node* left;
        Node* right;
        Node(const T& _data, Node* _left = nullptr, Node* _right = nullptr)
            : data(_data), left(_left), right(_right) {}
    };

    Node* root;

    Node* insert(Node* node, const T& value) {
        if (!node) return new Node(value);
        if (value < node->data)
            node->left = insert(node->left, value);
        else if (value > node->data)
            node->right = insert(node->right, value);
        return node;
    }

    bool search(Node* node, const T& value) const {
        if (!node) return false;
        if (node->data == value) return true;
        if (value < node->data)
            return search(node->left, value);
        return search(node->right, value);
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

    void print(Node* node) const {
        if (!node) return;
        cout << node->data << " ";
        print(node->left);
        print(node->right);
    }

    Node* copyNode(Node* otherNode) {
        if (!otherNode) return nullptr;
        Node* newNode = new Node(otherNode->data);
        newNode->left = copyNode(otherNode->left);
        newNode->right = copyNode(otherNode->right);
        return newNode;
    }

public:
    BinaryTree() : root(nullptr) {}

   
    BinaryTree(const BinaryTree<T>& other) {
        root = copyNode(other.root);
    }

  
    BinaryTree<T>& operator=(const BinaryTree<T>& other) {
        if (this != &other) {
            clear(root);
            root = copyNode(other.root);
        }
        return *this;
    }


    ~BinaryTree() { clear(root); }

    void clear() {
        clear(root);
        root = nullptr;
    }

    bool search(const T& value) const {
        return search(root, value);
    }

    void insert(const T& value) {
        root = insert(root, value);
    }

    void print() const {
        if (!root) {
            cout << "Tree is empty" << endl;
            return;
        }
        cout << "Tree: ";
        print(root);
        cout << endl;
    }
};
