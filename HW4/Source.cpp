#include <iostream>
using namespace std;

class MyString {
private:
    char* data;
    size_t length;

    size_t strLength(const char* str) const {
        size_t len = 0;
        while (str && str[len] != '\0') len++;
        return len;
    }

    void strCopy(char* dest, const char* src) {
        size_t i = 0;
        if (src) {
            while (src[i] != '\0') {
                dest[i] = src[i];
                i++;
            }
        }
        dest[i] = '\0';
    }

    void strCat(char* dest, const char* src) {
        size_t i = 0;
        while (dest[i] != '\0') i++;
        size_t j = 0;
        while (src && src[j] != '\0') {
            dest[i++] = src[j++];
        }
        dest[i] = '\0';
    }

public:
    MyString() : data(nullptr), length(0) {}

    MyString(const char* str) {
        length = strLength(str);
        data = new char[length + 1];
        strCopy(data, str);
    }

    MyString(const MyString& other) {
        length = other.length;
        data = new char[length + 1];
        strCopy(data, other.data);
    }

    MyString& operator=(const MyString& other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new char[length + 1];
            strCopy(data, other.data);
        }
        return *this;
    }

    ~MyString() {
        delete[] data;
    }

    size_t size() const { return length; }
    bool isEmpty() const { return length == 0; }
    const char* cStr() const { return data ? data : ""; }

    char at(size_t index) const {
        if (index < length) return data[index];
        throw out_of_range("Index out of range");
    }

    void pushBack(char c) {
        char* newData = new char[length + 2];
        if (data) strCopy(newData, data);
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
        size_t addLen = strLength(str);
        char* newData = new char[length + addLen + 1];
        if (data) strCopy(newData, data);
        else newData[0] = '\0';
        strCat(newData, str);
        delete[] data;
        data = newData;
        length += addLen;
    }

    void assign(const char* str) {
        delete[] data;
        length = strLength(str);
        data = new char[length + 1];
        strCopy(data, str);
    }

    int findChar(char c) const {
        for (size_t i = 0; i < length; i++)
            if (data[i] == c) return (int)i;
        return -1;
    }

    MyString subStr(size_t pos, size_t count) const {
        if (pos >= length) return MyString();
        if (pos + count > length) count = length - pos;
        char* temp = new char[count + 1];
        for (size_t i = 0; i < count; i++)
            temp[i] = data[pos + i];
        temp[count] = '\0';
        MyString result(temp);
        delete[] temp;
        return result;
    }

    void resize(size_t newSize) {
        char* newData = new char[newSize + 1];
        size_t i = 0;
        for (; i < length && i < newSize; i++)
            newData[i] = data[i];
        for (; i < newSize; i++)
            newData[i] = '\0';
        newData[newSize] = '\0';
        delete[] data;
        data = newData;
        length = newSize;
    }
};

int main() {
    MyString s("Hello");
    MyString t = s;         
    t.pushBack('!');
    cout << s.cStr() << endl;
    cout << t.cStr() << endl;

    MyString u;
    u = t;                 
    u.append(" World");
    cout << u.cStr() << endl;

    return 0;
}
