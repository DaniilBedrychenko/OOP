#include <iostream>
#include <string>
using namespace std;

struct Person {
    string name;
    int id;
    int booksCount;
};

struct Book {
    string title;
    string author;
    string genre;
    bool onHands;
    int holderId;
};

class Library {
    Book books[100];
    Person people[50];
    int bookCount;
    int peopleCount;
public:
    Library() : bookCount(0), peopleCount(0) {}

    void addBook(string t, string a, string g) {
        books[bookCount++] = {t, a, g, false, -1};
    }

    void addPerson(string n, int id) {
        people[peopleCount++] = {n, id, 0};
    }

    void searchByTitle(string title) {
        for (int i = 0; i < bookCount; i++)
            if (books[i].title == title)
                cout << books[i].title << " | " << books[i].author << " | " 
                     << books[i].genre << " | " 
                     << (books[i].onHands ? "на руках" : "в наличии") << endl;
    }

    void searchByAuthor(string author) {
        for (int i = 0; i < bookCount; i++)
            if (books[i].author == author)
                cout << books[i].title << " | " << books[i].author << " | " << books[i].genre << endl;
    }

    void searchByGenre(string genre) {
        for (int i = 0; i < bookCount; i++)
            if (books[i].genre == genre)
                cout << books[i].title << " | " << books[i].author << " | " << books[i].genre << endl;
    }

    int findPerson(int id) {
        for (int i = 0; i < peopleCount; i++)
            if (people[i].id == id) return i;
        return -1;
    }

    void giveBook(string title, int id) {
        int pid = findPerson(id);
        if (pid == -1) { cout << "Посетитель не найден.\n"; return; }
        if (people[pid].booksCount >= 3) { cout << "У посетителя уже 3 книги.\n"; return; }

        for (int i = 0; i < bookCount; i++)
            if (books[i].title == title && !books[i].onHands) {
                books[i].onHands = true;
                books[i].holderId = id;
                people[pid].booksCount++;
                cout << "Книга выдана.\n";
                return;
            }
        cout << "Книга не найдена или уже на руках.\n";
    }

    void returnBook(string title, int id) {
        int pid = findPerson(id);
        if (pid == -1) { cout << "Посетитель не найден.\n"; return; }

        for (int i = 0; i < bookCount; i++)
            if (books[i].title == title && books[i].holderId == id) {
                books[i].onHands = false;
                books[i].holderId = -1;
                people[pid].booksCount--;
                cout << "Книга возвращена.\n";
                return;
            }
        cout << "Ошибка возврата.\n";
    }

    void mostFrequentVisitor() {
        int maxBooks = -1, idx = -1;
        for (int i = 0; i < peopleCount; i++)
            if (people[i].booksCount > maxBooks) {
                maxBooks = people[i].booksCount;
                idx = i;
            }
        if (idx != -1)
            cout << "Самый частый посетитель: " << people[idx].name << " (" << people[idx].id << ")\n";
    }

    void showAllBooks() {
        for (int i = 0; i < bookCount; i++)
            cout << books[i].title << " | " << books[i].author << " | " << books[i].genre << " | " 
                 << (books[i].onHands ? "на руках" : "в наличии") << endl;
    }
};

int main() {
    Library lib;
    lib.addPerson("Иванов", 1);
    lib.addPerson("Петров", 2);
    lib.addBook("Война и мир", "Толстой", "Роман");
    lib.addBook("1984", "Оруэлл", "Антиутопия");
    lib.addBook("Три мушкетера", "Дюма", "Приключения");

    lib.searchByAuthor("Толстой");
    lib.giveBook("1984", 1);
    lib.showAllBooks();
    lib.returnBook("1984", 1);
    lib.mostFrequentVisitor();
}
