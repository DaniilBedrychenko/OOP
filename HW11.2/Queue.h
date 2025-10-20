#pragma once
#include <string>
using namespace std;

class Queue
{
private:
    int size;
    int* arr;
    int current_size;
public:
    Queue(int size);
    Queue(const Queue& other);
    Queue& operator=(const Queue& other);
    ~Queue();

    void Print();
    void Clear();
    int Dequeue();
    void Enqueue(int value);
    bool IsEmpty();
    int getSize();
};
