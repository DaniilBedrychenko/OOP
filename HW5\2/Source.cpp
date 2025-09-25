#include <iostream>
using namespace std;

class DynamicArray {
private:
    int* data;
    int arrSize;
    int arrCapacity;

    void resize(int newCapacity) {
        int* newData = new int[newCapacity];
        for (int i = 0; i < arrSize; i++)
            newData[i] = data[i];
        delete[] data;
        data = newData;
        arrCapacity = newCapacity;
    }

public:
    DynamicArray() : data(nullptr), arrSize(0), arrCapacity(0) {}

    DynamicArray(int capacity) : arrSize(0), arrCapacity(capacity) {
        data = new int[arrCapacity];
    }

    DynamicArray(const DynamicArray& other) {
        arrSize = other.arrSize;
        arrCapacity = other.arrCapacity;
        data = new int[arrCapacity];
        for (int i = 0; i < arrSize; i++)
            data[i] = other.data[i];
    }

    DynamicArray& operator=(const DynamicArray& other) {
        if (this != &other) {
            delete[] data;
            arrSize = other.arrSize;
            arrCapacity = other.arrCapacity;
            data = new int[arrCapacity];
            for (int i = 0; i < arrSize; i++)
                data[i] = other.data[i];
        }
        return *this;
    }

    ~DynamicArray() {
        delete[] data;
    }

    void add(int value) {
        if (arrSize == arrCapacity) {
            int newCapacity = arrCapacity == 0 ? 1 : arrCapacity * 2;
            resize(newCapacity);
        }
        data[arrSize++] = value;
    }

    void remove(int index) {
        if (index < 0 || index >= arrSize) {
            cout << "Index out of bounds\n";
            return;
        }
        for (int i = index; i < arrSize - 1; i++)
            data[i] = data[i + 1];
        arrSize--;
    }

    int get(int index) const {
        if (index < 0 || index >= arrSize) {
            cout << "Index out of bounds\n";
            return -1;
        }
        return data[index];
    }

    int size() const {
        return arrSize;
    }

    int capacity() const {
        return arrCapacity;
    }

    void print() const {
        for (int i = 0; i < arrSize; i++)
            cout << data[i] << " ";
        cout << endl;
    }

    int& operator[](int index) {
        if (index < 0 || index >= arrSize) throw out_of_range("Index out of bounds");
        return data[index];
    }

    DynamicArray operator+(const DynamicArray& other) const {
        DynamicArray result(arrSize + other.arrSize);
        for (int i = 0; i < arrSize; i++)
            result.add(data[i]);
        for (int i = 0; i < other.arrSize; i++)
            result.add(other.data[i]);
        return result;
    }

    DynamicArray& operator+=(int value) {
        add(value);
        return *this;
    }

    bool operator==(const DynamicArray& other) const {
        if (arrSize != other.arrSize) return false;
        for (int i = 0; i < arrSize; i++)
            if (data[i] != other.data[i]) return false;
        return true;
    }
};

int main() {
    DynamicArray arr1;
    arr1.add(1);
    arr1.add(2);
    arr1.add(3);
    arr1.print();

    DynamicArray arr2(2);
    arr2 += 4;
    arr2 += 5;
    arr2.print();

    DynamicArray arr3 = arr1 + arr2;
    arr3.print();

    arr3.remove(2);
    arr3.print();

    cout << "Element at index 1: " << arr3.get(1) << endl;

    cout << "arr1 == arr2? " << (arr1 == arr2 ? "Yes" : "No") << endl;

    DynamicArray arr4 = arr1;
    cout << "arr4 copied from arr1: ";
    arr4.print();

    arr4[0] = 10;
    cout << "arr4 after modification: ";
    arr4.print();

    return 0;
}
