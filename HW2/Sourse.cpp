#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

class Subscriber {
private:
    char* fullName;
    string homePhone;
    string workPhone;
    string mobilePhone;
    string extraInfo;

public:
    Subscriber()
        : fullName(nullptr), homePhone(""), workPhone(""),
          mobilePhone(""), extraInfo("") {}

    Subscriber(const char* name, const string& home,
               const string& work, const string& mobile,
               const string& extra)
        : homePhone(home), workPhone(work),
          mobilePhone(mobile), extraInfo(extra) {
        fullName = new char[strlen(name) + 1];
        strcpy(fullName, name);
    }

    Subscriber(const Subscriber& other)
        : homePhone(other.homePhone), workPhone(other.workPhone),
          mobilePhone(other.mobilePhone), extraInfo(other.extraInfo) {
        fullName = new char[strlen(other.fullName) + 1];
        strcpy(fullName, other.fullName);
    }

    Subscriber& operator=(const Subscriber& other) {
        if (this == &other) return *this;
        delete[] fullName;
        fullName = new char[strlen(other.fullName) + 1];
        strcpy(fullName, other.fullName);
        homePhone = other.homePhone;
        workPhone = other.workPhone;
        mobilePhone = other.mobilePhone;
        extraInfo = other.extraInfo;
        return *this;
    }

    ~Subscriber() {
        delete[] fullName;
    }

    inline const char* getFullName() const { return fullName; }
    inline const string& getHomePhone() const { return homePhone; }

    void print() const {
        cout << "ПІБ: " << (fullName ? fullName : "—") << "\n";
        cout << "Домашній: " << homePhone << "\n";
        cout << "Робочий: " << workPhone << "\n";
        cout << "Мобільний: " << mobilePhone << "\n";
        cout << "Додаткова інформація: " << extraInfo << "\n\n";
    }

    void save(ofstream& out) const {
        size_t len = strlen(fullName);
        out.write((char*)&len, sizeof(len));
        out.write(fullName, len);

        size_t l1 = homePhone.size();
        out.write((char*)&l1, sizeof(l1));
        out.write(homePhone.c_str(), l1);

        size_t l2 = workPhone.size();
        out.write((char*)&l2, sizeof(l2));
        out.write(workPhone.c_str(), l2);

        size_t l3 = mobilePhone.size();
        out.write((char*)&l3, sizeof(l3));
        out.write(mobilePhone.c_str(), l3);

        size_t l4 = extraInfo.size();
        out.write((char*)&l4, sizeof(l4));
        out.write(extraInfo.c_str(), l4);
    }

    void load(ifstream& in) {
        delete[] fullName;

        size_t len;
        in.read((char*)&len, sizeof(len));
        fullName = new char[len + 1];
        in.read(fullName, len);
        fullName[len] = '\0';

        size_t l1; in.read((char*)&l1, sizeof(l1));
        homePhone.resize(l1);
        in.read(&homePhone[0], l1);

        size_t l2; in.read((char*)&l2, sizeof(l2));
        workPhone.resize(l2);
        in.read(&workPhone[0], l2);

        size_t l3; in.read((char*)&l3, sizeof(l3));
        mobilePhone.resize(l3);
        in.read(&mobilePhone[0], l3);

        size_t l4; in.read((char*)&l4, sizeof(l4));
        extraInfo.resize(l4);
        in.read(&extraInfo[0], l4);
    }
};

int main() {
    vector<Subscriber> phoneBook;

    while (true) {
        cout << "1. Додати абонента\n"
             << "2. Видалити абонента\n"
             << "3. Знайти абонента\n"
             << "4. Показати всіх\n"
             << "5. Зберегти у файл\n"
             << "6. Завантажити з файлу\n"
             << "0. Вихід\n> ";

        int choice; cin >> choice;
        cin.ignore();
        if (choice == 0) break;

        if (choice == 1) {
            string home, work, mobile, extra;
            char name[256];
            cout << "Введіть ПІБ: "; cin.getline(name, 256);
            cout << "Домашній: "; getline(cin, home);
            cout << "Робочий: "; getline(cin, work);
            cout << "Мобільний: "; getline(cin, mobile);
            cout << "Додаткова інформація: "; getline(cin, extra);
            phoneBook.emplace_back(name, home, work, mobile, extra);

        } else if (choice == 2) {
            string name;
            cout << "Введіть ПІБ для видалення: ";
            getline(cin, name);
            for (auto it = phoneBook.begin(); it != phoneBook.end(); ++it) {
                if (strcmp(it->getFullName(), name.c_str()) == 0) {
                    phoneBook.erase(it);
                    cout << "Абонента видалено.\n";
                    break;
                }
            }

        } else if (choice == 3) {
            string name;
            cout << "Введіть ПІБ для пошуку: ";
            getline(cin, name);
            for (auto& s : phoneBook) {
                if (strcmp(s.getFullName(), name.c_str()) == 0) {
                    s.print();
                }
            }

        } else if (choice == 4) {
            for (auto& s : phoneBook) s.print();

        } else if (choice == 5) {
            ofstream out("phonebook.dat", ios::binary);
            size_t count = phoneBook.size();
            out.write((char*)&count, sizeof(count));
            for (auto& s : phoneBook) s.save(out);
            cout << "Збережено.\n";

        } else if (choice == 6) {
            ifstream in("phonebook.dat", ios::binary);
            size_t count;
            in.read((char*)&count, sizeof(count));
            phoneBook.clear();
            phoneBook.resize(count);
            for (size_t i = 0; i < count; ++i) {
                phoneBook[i].load(in);
            }
            cout << "Завантажено.\n";
        }
    }
    return 0;
}
