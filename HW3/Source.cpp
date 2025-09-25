#include <iostream>
#include <cstring>
using namespace std;

class MyString {
private:
    char* data;
    size_t length;

public:
    MyString() : data(nullptr), length(0) {}

    MyString(const char* str) {
        if (str) {
            length = strlen(str);
            data = new char[length + 1];
            strcpy(data, str);
        } else {
            data = nullptr;
            length = 0;
        }
    }

    MyString(const MyString& other) {
        length = other.length;
        if (other.data) {
            data = new char[length + 1];
            strcpy(data, other.data);
        } else {
            data = nullptr;
        }
    }

    ~MyString() {
        delete[] data;
    }

    size_t size() const {
        return length;
    }

    bool empty() const {
        return length == 0;
    }

    const char* cStr() const {
        return data ? data : "";
    }

    char at(size_t index) const {
        if (index < length) return data[index];
        throw out_of_range("Index out of range");
    }

    void pushBack(char c) {
        char* newData = new char[length + 2];
        if (data) strcpy(newData, data);
        newData[length] = c;
        newData[length + 1] = '\0';
        delete[] data;
        data = newData;
        length++;
    }

    void popBack() {
        if (length > 0) {
            length--;
            data[length] = '\0';
        }
    }

    void clear() {
        delete[] data;
        data = nullptr;
        length = 0;
    }

    void append(const char* str) {
        if (!str) return;
        size_t addLen = strlen(str);
        char* newData = new char[length + addLen + 1];
        if (data) strcpy(newData, data);
        else newData[0] = '\0';
        strcat(newData, str);
        delete[] data;
        data = newData;
        length += addLen;
    }

    void assign(const char* str) {
        delete[] data;
        if (str) {
            length = strlen(str);
            data = new char[length + 1];
            strcpy(data, str);
        } else {
            data = nullptr;
            length = 0;
        }
    }

    int find(char c) const {
        if (!data) return -1;
        for (size_t i = 0; i < length; i++)
            if (data[i] == c) return (int)i;
        return -1;
    }

    MyString substr(size_t pos, size_t count) const {
        if (pos >= length) return MyString();
        if (pos + count > length) count = length - pos;
        char* temp = new char[count + 1];
        strncpy(temp, data + pos, count);
        temp[count] = '\0';
        MyString result(temp);
        delete[] temp;
        return result;
    }

    void resize(size_t newSize) {
        char* newData = new char[newSize + 1];
        if (data) {
            if (newSize < length) {
                strncpy(newData, data, newSize);
                newData[newSize] = '\0';
            } else {
                strcpy(newData, data);
                for (size_t i = length; i < newSize; i++) newData[i] = '\0';
                newData[newSize] = '\0';
            }
        } else {
            for (size_t i = 0; i < newSize; i++) newData[i] = '\0';
            newData[newSize] = '\0';
        }
        delete[] data;
        data = newData;
        length = newSize;
    }
};

int main() {
    MyString s("Hello");
    s.pushBack('!');
    cout << s.cStr() << endl;

    s.append(" World");
    cout << s.cStr() << endl;

    MyString t = s.substr(6, 5);
    cout << t.cStr() << endl;

    s.popBack();
    cout << s.cStr() << endl;

    s.resize(4);
    cout << s.cStr() << endl;

    cout << s.find('l') << endl;

    return 0;
}
