#include "QueuePriority.h"
#include <iostream>
using namespace std;

QueuePriority::QueuePriority(int size)
{
    maxSize = size;
    currentSize = 0;
    priorityArray = new int[maxSize];
    items = new int[maxSize];
}

QueuePriority::~QueuePriority()
{
    delete[] priorityArray;
    delete[] items;
}

void QueuePriority::Add(int item, int priority)
{
    if (!IsFull()) {
        items[currentSize] = item;
        priorityArray[currentSize] = priority;
        currentSize++;
    }
}

int QueuePriority::Extract()
{
    if (!IsEmpty()) {
        int maxPri = priorityArray[0];
        int maxPriPos = 0;
        for (int i = 0; i < currentSize; i++) {
            if (maxPri < priorityArray[i]) {
                maxPri = priorityArray[i];
                maxPriPos = i;
            }
        }
        int item = items[maxPriPos];
        for (int i = maxPriPos; i < currentSize - 1; i++) {
            items[i] = items[i + 1];
            priorityArray[i] = priorityArray[i + 1];
        }
        currentSize--;
        return item;
    }
    return 0;
}

void QueuePriority::Clear()
{
    currentSize = 0;
}

bool QueuePriority::IsEmpty()
{
    return currentSize == 0;
}

bool QueuePriority::IsFull()
{
    return currentSize == maxSize;
}

int QueuePriority::getCount()
{
    return currentSize;
}

void QueuePriority::Print()
{
    cout << "Current size: " << currentSize << endl;
    cout << "(priority|item):" << endl;
    for (int i = 0; i < currentSize; i++) {
        cout << "(" << priorityArray[i] << "|" << items[i] << ")" << endl;
    }
    cout << endl;
}
