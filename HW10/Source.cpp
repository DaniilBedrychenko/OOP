#include<iostream>
#include"Stack.h"
using namespace std;

int showMenu() {
	cout << "Control of Stack: " << endl;
	cout << "1) Push item\n";
	cout << "2) Pop item\n";
	cout << "3) Size of stack\n";
	cout << "4) Is empty?\n";
	cout << "5) Get last\n";
	cout << "6) Exit\n";
	cout << "Enter choice: ";
	int choice = 0;
	cin >> choice;
	return choice;
}

template<class T>
void startProgram() {
	cout << "Enter stack max size: ";
	int maxSize = 0;
	cin >> maxSize;
	Stack<T> myStack(maxSize);
	bool isExit = false;
	while (!isExit) {
		system("cls");
		cout << "Stack items: " << endl;
		myStack.print();
		T value = T();
		int choice = showMenu();
		switch(choice) {
			case 1:  
				system("cls");
				cout << "Enter value: " << endl;
				
				cin >> value;
				myStack.push(value);
				break;
			case 2:
				system("cls");
				cout << "Pop item: " << myStack.top() << endl;
				myStack.pop();
				system("pause");
				break;
			case 3:
				system("cls");
				cout << "Stack size: " << myStack.size() << endl;
				system("pause");
				break;
			case 4:
				system("cls");
				cout << "Stack is empty: " << myStack.empty() << endl;
				system("pause");
				break;
			case 5:
				system("cls");
				cout << "Stack last item: " << myStack.top() << endl;
				system("pause");
				break;
			case 6:
				system("cls");
				cout << "Goodbye" << endl;
				isExit = true;
				break;
			default:
				cout << "Wrong choice. Try again!" << endl;
				system("pause");
				break;
		}
	}
}

int main() {
	startProgram<int>();
}


```cpp
#pragma once
#include <iostream>
using namespace std;

template<class T>
class Stack {
    T* ptr;
    int maxSize;
    int current;
public:
    Stack(int size = 200);
    Stack(const Stack<T>& other);
    ~Stack();

    Stack<T>& operator=(const Stack<T>& other) = delete;

    void print();
    void push(const T& value);
    void pop();
    T& top();
    bool empty() const;
    int size() const;

private:
    void resize();
};

template<typename T>
Stack<T>::Stack(int size) : maxSize(size), current(-1) {
    ptr = new T[maxSize];
}

template<class T>
Stack<T>::Stack(const Stack<T>& other) : maxSize(other.maxSize), current(other.current) {
    ptr = new T[maxSize];
    for (int i = 0; i <= current; i++)
        ptr[i] = other.ptr[i];
}

template<class T>
Stack<T>::~Stack() {
    delete[] ptr;
}

template<class T>
void Stack<T>::print() {
    if (empty()) {
        cout << "[empty]" << endl;
        return;
    }
    for (int i = 0; i <= current; i++) {
        cout << ptr[i] << " ";
    }
    cout << endl;
}

template<class T>
void Stack<T>::push(const T& value) {
    if (current >= maxSize - 1) {
        resize();
    }
    ptr[++current] = value;
}

template<class T>
void Stack<T>::pop() {
    if (empty()) {
        cout << "Exception: Stack is empty\n";
        return;
    }
    current--;
}

template<class T>
T& Stack<T>::top() {
    if (empty()) {
        cout << "Exception: Stack is empty\n";
        exit(-1);
    }
    return ptr[current];
}

template<class T>
bool Stack<T>::empty() const {
    return current < 0;
}

template<class T>
int Stack<T>::size() const {
    return current + 1;
}

template<class T>
void Stack<T>::resize() {
    int newSize = maxSize * 2;
    T* newPtr = new T[newSize];
    for (int i = 0; i <= current; i++) {
        newPtr[i] = ptr[i];
    }
    delete[] ptr;
    ptr = newPtr;
    maxSize = newSize;
}
