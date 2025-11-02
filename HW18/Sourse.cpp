#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
using namespace std;

map<string, string> dict;

void loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file) return;
    string line, key, value;
    while (getline(file, line)) {
        stringstream ss(line);
        if (getline(ss, key, '=') && getline(ss, value)) {
            dict[key] = value;
        }
    }
}

void saveToFile(const string& filename) {
    ofstream file(filename);
    for (const auto& pair : dict) {
        file << pair.first << "=" << pair.second << endl;
    }
}

void search(const string& key) {
    auto it = dict.find(key);
    if (it != dict.end()) {
        cout << "Знайдено: " << key << " -> " << it->second << endl;
    } else {
        cout << "Не знайдено: " << key << endl;
    }
}

void add(const string& key, const string& value) {
    dict[key] = value;
    cout << "Додано: " << key << " -> " << value << endl;
}

void remove(const string& key) {
    if (dict.erase(key) > 0) {
        cout << "Видалено: " << key << endl;
    } else {
        cout << "Не знайдено для видалення: " << key << endl;
    }
}

void edit(const string& key, const string& newValue) {
    if (dict.find(key) != dict.end()) {
        dict[key] = newValue;
        cout << "Відредаговано: " << key << " -> " << newValue << endl;
    } else {
        cout << "Не знайдено для редагування: " << key << endl;
    }
}

void printAll() {
    if (dict.empty()) {
        cout << "Словник порожній." << endl;
    } else {
        cout << "Словник:" << endl;
        for (const auto& pair : dict) {
            cout << pair.first << " -> " << pair.second << endl;
        }
    }
}

int main() {
    loadFromFile("dictionary.txt");
    int choice;
    string key, value;

    while (true) {
        cout << "\nМеню:\n";
        cout << "1. Пошук слова\n";
        cout << "2. Додавання\n";
        cout << "3. Видалення\n";
        cout << "4. Редагування\n";
        cout << "5. Вивести всі\n";
        cout << "6. Зберегти у файл\n";
        cout << "0. Вихід\n";
        cout << "Вибір: ";
        cin >> choice;
        cin.ignore();

        if (choice == 0) break;
        switch (choice) {
            case 1:
                cout << "Ключ: "; getline(cin, key);
                search(key);
                break;
            case 2:
                cout << "Ключ: "; getline(cin, key);
                cout << "Значення: "; getline(cin, value);
                add(key, value);
                break;
            case 3:
                cout << "Ключ: "; getline(cin, key);
                remove(key);
                break;
            case 4:
                cout << "Ключ: "; getline(cin, key);
                cout << "Нове значення: "; getline(cin, value);
                edit(key, value);
                break;
            case 5:
                printAll();
                break;
            case 6:
                saveToFile("dictionary.txt");
                cout << "Збережено!" << endl;
                break;
            default:
                cout << "Невірний вибір." << endl;
        }
    }

    saveToFile("dictionary.txt");
    return 0;
}
