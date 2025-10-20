#pragma once

class QueuePriority
{
    int* items;
    int* priorityArray;
    int maxSize;
    int currentSize;
public:
    QueuePriority(int size);
    ~QueuePriority();

    void Add(int item, int priority = 0);
    int Extract();
    void Clear();
    bool IsEmpty();
    bool IsFull();
    int getCount();
    void Print();
};
