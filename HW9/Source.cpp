```cpp
#include <iostream>
#include <string>
using namespace std;

string compressText(const string& s) {
    string res;
    bool space = false;
    for (char c : s) {
        if (c != ' ') {
            if (space && !res.empty()) res += ' ';
            res += c;
            space = false;
        } else space = true;
    }
    return res;
}

string removeComments(const string& text) {
    string res;
    bool line = false, block = false;
    for (size_t i = 0; i < text.size(); i++) {
        if (!line && !block && i + 1 < text.size() && text[i] == '/' && text[i + 1] == '/')
            line = true, i++;
        else if (!line && !block && i + 1 < text.size() && text[i] == '/' && text[i + 1] == '*')
            block = true, i++;
        else if (line && text[i] == '\n')
            line = false, res += text[i];
        else if (block && i + 1 < text.size() && text[i] == '*' && text[i + 1] == '/')
            block = false, i++;
        else if (!line && !block)
            res += text[i];
    }
    return res;
}

string highlight(const string& text, const string& sub) {
    if (sub.empty()) return text;
    string res;
    size_t i = 0;
    while (i < text.size()) {
        if (text.substr(i, sub.size()) == sub) {
            res += '(' + sub + ')';
            i += sub.size();
        } else res += text[i++];
    }
    return res;
}

void fileInfo(const string& path) {
    size_t pos1 = path.find_last_of("\\/");
    size_t pos2 = path.find_last_of('.');
    string dir = (pos1 == string::npos) ? "" : path.substr(0, pos1);
    string folder = "";
    if (pos1 != string::npos) {
        size_t prev = path.substr(0, pos1).find_last_of("\\/");
        folder = (prev == string::npos) ? path.substr(0, pos1) : path.substr(prev + 1, pos1 - prev - 1);
    }
    string file = (pos1 == string::npos) ? path : path.substr(pos1 + 1);
    string ext = (pos2 == string::npos || pos2 < pos1) ? "" : path.substr(pos2);
    string fileNoExt = (pos2 == string::npos || pos2 < pos1) ? file : path.substr(pos1 + 1, pos2 - pos1 - 1);

    cout << "a) " << dir << endl;
    cout << "b) " << folder << endl;
    cout << "c) " << file << endl;
    cout << "d) " << ext << endl;
    cout << "e) " << fileNoExt << endl;
}

int main() {
    int choice;
    string text, sub, path;

    while (true) {
        cout << "\n===== Меню =====\n";
        cout << "1. Сжатие текста\n";
        cout << "2. Удаление комментариев\n";
        cout << "3. Поиск и выделение\n";
        cout << "6. Путь к файлу\n";
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;
        cin.ignore();

        if (choice == 0) break;

        switch (choice) {
            case 1:
                cout << "Введите строку: ";
                getline(cin, text);
                cout << "Результат: " << compressText(text) << endl;
                break;
            case 2:
                cout << "Введите текст: ";
                getline(cin, text);
                cout << "Результат:\n" << removeComments(text) << endl;
                break;
            case 3:
                cout << "Введите текст: ";
                getline(cin, text);
                cout << "Введите подстроку: ";
                getline(cin, sub);
                cout << "Результат: " << highlight(text, sub) << endl;
                break;
            case 6:
                cout << "Введите путь к файлу: ";
                getline(cin, path);
                fileInfo(path);
                break;
            default:
                cout << "Неверный выбор.\n";
        }
    }

    cout << "Программа завершена.\n";
    return 0;
}
```
