```cpp
#include <iostream>
#include <cstring>
using namespace std;

class String {
    char* data;
    size_t size;
public:
    String() : data(nullptr), size(0) {}
    String(const char* s) {
        size = strlen(s);
        data = new char[size + 1];
        strcpy(data, s);
    }
    String(const String& other) {
        size = other.size;
        data = new char[size + 1];
        strcpy(data, other.data);
    }
    String(String&& other) noexcept {
        data = other.data;
        size = other.size;
        other.data = nullptr;
        other.size = 0;
    }
    String& operator=(const String& other) {
        if (this == &other) return *this;
        delete[] data;
        size = other.size;
        data = new char[size + 1];
        strcpy(data, other.data);
        return *this;
    }
    String& operator=(String&& other) noexcept {
        if (this == &other) return *this;
        delete[] data;
        data = other.data;
        size = other.size;
        other.data = nullptr;
        other.size = 0;
        return *this;
    }
    String operator*(const String& other) const {
        String result;
        for (size_t i = 0; i < size; i++) {
            if (strchr(other.data, data[i])) {
                char tmp[2] = { data[i], '\0' };
                result += tmp;
            }
        }
        return result;
    }
    String operator/(const String& other) const {
        String result;
        for (size_t i = 0; i < size; i++) {
            if (!strchr(other.data, data[i])) {
                char tmp[2] = { data[i], '\0' };
                result += tmp;
            }
        }
        return result;
    }
    String& operator+=(const char* s) {
        size_t len = strlen(s);
        char* newData = new char[size + len + 1];
        if (data) strcpy(newData, data);
        else newData[0] = '\0';
        strcat(newData, s);
        delete[] data;
        data = newData;
        size += len;
        return *this;
    }
    void Show() const {
        if (data) cout << data << endl;
    }
    ~String() { delete[] data; }
};

int main() {
    String a = "Microsoft";
    String b = "Windows";
    String c;
    c = a * b;
    c.Show();
    c = a / b;
    c.Show();
}
```
