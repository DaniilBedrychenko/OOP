#include <iostream>
#include "SingleLinkedList.h"
#include "DLList.h"
#include "BinnaryTree.h"
using namespace std;

int main()
{
    SingleLinkedList list;
    list.push_back(50);
    list.push_back(20);
    list.push_front(10);
    list.print();
    list.remove(10);
    list.print();
    list.removeAll();
    list.print();

    for (int i = 0; i < 10; i++) {
        list.push_back(i);
    }
    cout << "\nDouble linked list: " << endl;
    
    DLLlist dList;
    for (int i = 0; i < 10; i++) {
        i > 4 ? dList.push_back(i) : dList.push_front(i);
    }

    dList.print();
    dList.removeItem(0);
    dList.print(false);

    BinnaryTree tree;
    tree.insert(5);
    tree.insert(10);
    tree.insert(4);
    tree.insert(3);
    tree.insert(6);
    tree.insert(11);
    tree.insert(55);

    tree.print();



}


