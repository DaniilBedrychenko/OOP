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



