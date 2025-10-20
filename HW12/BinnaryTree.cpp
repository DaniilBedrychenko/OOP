#include "BinnaryTree.h"
#include<iostream>
using namespace std;
BinnaryTree::Node* BinnaryTree::insert(Node* node, int value)
{
    if (!node) return new Node(value, nullptr, nullptr);
    if (value < node->data)
        node->left = insert(node->left, value);
    else if (value > node->data)
        node->right = insert(node->right, value);
    return node;
}

bool BinnaryTree::search(Node* node, int value)
{
    if (!node) return false;
    if (node->data == value) return true;
    if (value < node->data)
        return search(node->left, value);
    else
        return search(node->right, value);
}

void BinnaryTree::clear(Node* node)
{
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

void BinnaryTree::print(Node* node)
{
    if (!node) return;
    cout << node->data << " ";
    print(node->left);
    
    print(node->right);
}

void BinnaryTree::clear()
{
    clear(root);
    root = nullptr;
}

bool BinnaryTree::search(int value)
{
    return search(root, value);
}

void BinnaryTree::insert(int value)
{
    root = insert(root, value);
}

void BinnaryTree::print()
{
    if (root == nullptr) {
        cout << "Tree is empty" << endl;
        return;
    }
    cout << "Tree: ";
    print(root);
}
