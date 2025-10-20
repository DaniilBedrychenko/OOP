#include "SingleLinkedList.h"
#include <iostream>
using namespace std;

int& SingleLinkedList::operator[](int index)
{
	int temp_count = 0;
	for (Node* temp = head; temp != nullptr; temp = temp->next) {
		if (temp_count == index) {
			return temp->data;
		}
		temp_count++;
	}
}

void SingleLinkedList::push_back(int value)
{
	Node* newNode = new Node(value, nullptr);
	if (!head) {
		head = newNode;
		count++;
		return;
	}
	Node* temp = head;
	while (temp->next != nullptr)
		temp = temp->next; 
	temp->next = newNode;
	count++;
}

void SingleLinkedList::push_front(int value)
{
	Node* newNode = new Node(value, head);
	head = newNode;
	count++;
}

void SingleLinkedList::remove(int value)
{
	if (head == nullptr) return;
	if (head->data == value) {
		Node* temp = head;
		head = temp->next;
		delete temp;
		count--;
		return;
	}
	Node* temp = head;
	while (temp->next != nullptr) {
		if (temp->next->data == value) {
			Node* toDelete = temp->next;
			temp->next = temp->next->next;
			count--;
			delete toDelete;
			return;
		}
		temp = temp->next;
	}
	
}

void SingleLinkedList::removeAll()
{
	Node* temp;
	while (head) {
		temp = head;
		head = head->next;
		delete temp;
		count--;
	}
}

void SingleLinkedList::print()
{
	if (count == 0) {
		cout << "List is empty" << endl;
		return;
	}
	cout << "Count: " << count << endl;
	Node* temp = head;
	int i = 0;
	while (temp) {
		cout << temp->data;
		(count - 1) == i ? cout << " " :
			cout << " -> ";
		temp = temp->next;
		i++;
	}
	cout << endl;
}

bool SingleLinkedList::find(int value)
{
	Node* temp = head;
	while (temp){
		if (temp->data == value) {
			return true;
		}
		temp = temp->next;
	}
	return false;
}
