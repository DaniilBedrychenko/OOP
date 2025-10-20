#include "Queue.h"
#include<iostream>
using namespace std;

Queue::Queue(int size)
{
	this->size = size;
	arr = new int[size];
	current_size = 0;
}

Queue::Queue(const Queue& other)
{
	this->size = other.size;
	arr = new int[other.size];
	for (int i = 0; i < other.current_size; i++) {
		arr[i] = other.arr[i];
	}
}

Queue& Queue::operator=(const Queue& other)
{
	if (this == &other) return *this;
	if (arr != nullptr) delete[] arr;
	this->size = other.size;
	arr = new int[other.size];
	for (int i = 0; i < other.current_size; i++) {
		arr[i] = other.arr[i];
	}
	return *this;
}

Queue::~Queue()
{
	delete[] arr;
}

void Queue::Print()
{
	cout << "Current size: " << current_size << endl;
	for (int i = 0; i < current_size; i++)
		cout << arr[i] << " ";
	cout << endl;
}

void Queue::Clear()
{
	current_size = 0;
}

int Queue::Dequeue()
{
	if (IsEmpty()) return 0;
	int result = arr[0];
	for (int i = 0; i < current_size - 1; i++) {
		arr[i] = arr[i + 1];
	}
	current_size--;
	return result;
}

void Queue::Enqueue(int value)
{
	if (current_size == size) {
		size *= 2;
		int* copy = new int[size];
		for (int i = 0; i < current_size; i++) {
			copy[i] = arr[i];
		}
		delete[] arr;

		arr = copy;
	}
	arr[current_size++] = value;
}

bool Queue::IsEmpty()
{
	return current_size == 0;
}

int Queue::getSize()
{
	return current_size;
}
