#include "DLList.h"
#include <iostream>
using namespace std;


void DLLlist::push_back(int value) {
	Node* newNode = new Node(value, nullptr, tail);
	if (head == nullptr) {
		head = tail = newNode;
		count++;
		return;
	}
	tail->next = newNode;
	tail = newNode;
	count++;
}

void DLLlist::push_front(int value)
{
	Node* newNode = new Node(value, head, nullptr);
	if (head == nullptr) {
		head = tail = newNode;
		count++;
		return;
	}
	head->prev = newNode;
	head = newNode;
	count++;
}

void DLLlist::removeItem(int value)
{
	if (!head) return;
	Node* temp = head;
	while (temp != nullptr && temp->data != value) temp = temp->next;

	if (temp == head) {
		head = head->next;
		if (head != nullptr) head->prev = nullptr;
		else tail = nullptr;
	}

	else if (temp == tail) {
		tail = tail->prev;
		tail->next = nullptr;
	}

	else {
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
	}
	count--;
	delete temp;
}

void DLLlist::removeAll()
{
	Node* temp;
	while (head != nullptr) {
		temp = head;
		head = head->next;
		count--;
		delete temp;
	}
	tail = nullptr;
}

void DLLlist::print(bool forward)
{
	if (count == 0) {
		cout << "List is empty" << endl;
		return;
	}
	cout << "Count: " << count << endl;
	Node* temp = forward ? head : tail;
	int i = 0;
	while (temp) {
		cout << temp->data;
		(count - 1) == i ? cout << " " :
			cout << " -> ";
		temp = forward ? temp->next : temp->prev;
		i++;
	}
	cout << endl;
}

bool DLLlist::find(int value)
{
	Node* temp = head;
	while (temp!=nullptr) {
		if (temp->data == value) return true;
		temp = temp->next;
	}
	return false;
}
