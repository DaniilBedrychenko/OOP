#include <iostream>
#include <string>
#include <ctime>
#include "Queue.h"
#include "QueuePriority.h"
using namespace std;

struct PrintJob {
    string user;
    string document;
    int priority;
};

struct PrintStat {
    string user;
    string document;
    string timePrinted;
};

class Printer {
    QueuePriority jobQueue;
    Queue statQueue;
    PrintJob* jobs;
    PrintStat* stats;
    int jobCount;
    int statCount;
    int maxSize;

public:
    Printer(int size) : jobQueue(size), statQueue(size) {
        maxSize = size;
        jobs = new PrintJob[size];
        stats = new PrintStat[size];
        jobCount = 0;
        statCount = 0;
    }

    ~Printer() {
        delete[] jobs;
        delete[] stats;
    }

    void AddJob(const string& user, const string& doc, int priority) {
        if (jobCount >= maxSize) {
            cout << "Очередь переполнена!\n";
            return;
        }
        jobs[jobCount] = { user, doc, priority };
        jobQueue.Add(jobCount, priority);
        cout << "Добавлено задание: " << doc << " (" << user << "), приоритет " << priority << endl;
        jobCount++;
    }

    void PrintNext() {
        if (jobQueue.IsEmpty()) {
            cout << "Очередь пуста!\n";
            return;
        }
        int index = jobQueue.Extract();
        PrintJob job = jobs[index];
        time_t now = time(nullptr);
        string timeStr = ctime(&now);
        timeStr.pop_back();

        cout << "\n=== Печать документа ===\n";
        cout << "Пользователь: " << job.user << endl;
        cout << "Документ: " << job.document << endl;
        cout << "Приоритет: " << job.priority << endl;
        cout << "Время печати: " << timeStr << endl;

        stats[statCount] = { job.user, job.document, timeStr };
        statQueue.Enqueue(statCount);
        statCount++;
    }

    void ShowStats() {
        if (statQueue.IsEmpty()) {
            cout << "Статистика пуста.\n";
            return;
        }
        cout << "\n===== Статистика печати =====\n";
        for (int i = 0; i < statQueue.getSize(); i++) {
            int idx = i;
            PrintStat st = stats[idx];
            cout << i + 1 << ") Пользователь: " << st.user
                 << " | Документ: " << st.document
                 << " | Время: " << st.timePrinted << endl;
        }
    }
};

//---------------------------- MAIN --------------------------
int Menu() {
    cout << "\n=== Меню ===\n";
    cout << "1) Добавить задание\n";
    cout << "2) Печать следующего\n";
    cout << "3) Показать статистику\n";
    cout << "4) Выход\n";
    cout << "Выбор: ";
    int choice;
    cin >> choice;
    cin.ignore();
    return choice;
}

int main() {
    setlocale(LC_ALL, "Russian");
    Printer printer(10);
    while (true) {
        switch (Menu()) {
        case 1: {
            string user, doc;
            int pr;
            cout << "Имя пользователя: ";
            getline(cin, user);
            cout << "Название документа: ";
            getline(cin, doc);
            cout << "Приоритет (1-10): ";
            cin >> pr;
            cin.ignore();
            printer.AddJob(user, doc, pr);
            break;
        }
        case 2:
            printer.PrintNext();
            break;
        case 3:
            printer.ShowStats();
            break;
        case 4:
            cout << "Выход...\n";
            return 0;
        default:
            cout << "Ошибка выбора!\n";
        }
    }
}
