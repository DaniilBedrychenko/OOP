#pragma once
#include <iostream>
using namespace std;

template <class T>
class Queue
{
private:
    int size;
    T* arr;
    int current_size;
public:
    Queue(int size);
    Queue(const Queue<T>& other);
    Queue<T>& operator=(const Queue<T>& other);
    ~Queue();

    void Print();
    void Clear();
    T Dequeue();
    void Enqueue(const T& value);
    bool IsEmpty();
    int getSize();
};

// -------------------- Реалізація шаблонів --------------------

template <class T>
Queue<T>::Queue(int size)
{
    this->size = size;
    arr = new T[size];
    current_size = 0;
}

template <class T>
Queue<T>::Queue(const Queue<T>& other)
{
    this->size = other.size;
    arr = new T[other.size];
    for (int i = 0; i < other.current_size; i++) {
        arr[i] = other.arr[i];
    }
    current_size = other.current_size;
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& other)
{
    if (this == &other) return *this;
    if (arr != nullptr) delete[] arr;
    this->size = other.size;
    arr = new T[other.size];
    for (int i = 0; i < other.current_size; i++) {
        arr[i] = other.arr[i];
    }
    current_size = other.current_size;
    return *this;
}

template <class T>
Queue<T>::~Queue()
{
    delete[] arr;
}

template <class T>
void Queue<T>::Print()
{
    cout << "Current size: " << current_size << endl;
    for (int i = 0; i < current_size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

template <class T>
void Queue<T>::Clear()
{
    current_size = 0;
}

template <class T>
T Queue<T>::Dequeue()
{
    if (IsEmpty()) {
        cout << "Queue is empty!\n";
        return T();
    }
    T result = arr[0];
    for (int i = 0; i < current_size - 1; i++) {
        arr[i] = arr[i + 1];
    }
    current_size--;
    return result;
}

template <class T>
void Queue<T>::Enqueue(const T& value)
{
    if (current_size == size) {
        size *= 2;
        T* copy = new T[size];
        for (int i = 0; i < current_size; i++) {
            copy[i] = arr[i];
        }
        delete[] arr;
        arr = copy;
    }
    arr[current_size++] = value;
}

template <class T>
bool Queue<T>::IsEmpty()
{
    return current_size == 0;
}

template <class T>
int Queue<T>::getSize()
{
    return current_size;
}
