#include <iostream>
#include <string>
#include <ctime>
#include "QueuePriority.h"
#include "Queue.h"
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
    PrintJob* jobList;       
    PrintStat* statList;    
    int jobCount;
    int statCount;

public:
    Printer(int size) : jobQueue(size), statQueue(size) {
        jobList = new PrintJob[size];
        statList = new PrintStat[size];
        jobCount = 0;
        statCount = 0;
    }

    ~Printer() {
        delete[] jobList;
        delete[] statList;
    }

    void AddJob(const string& user, const string& doc, int priority) {
        jobList[jobCount] = { user, doc, priority };
        jobQueue.Add(jobCount, priority);
        jobCount++;
        cout << "Задание добавлено: " << doc << " от " << user
             << " (приоритет " << priority << ")\n";
    }

    void PrintNext() {
        if (jobQueue.IsEmpty()) {
            cout << "Очередь пуста!\n";
            return;
        }

        int index = jobQueue.Extract();
        PrintJob job = jobList[index];

        cout << "\n=== Печать документа ===\n";
        cout << "Пользователь: " << job.user << endl;
        cout << "Документ: " << job.document << endl;
        cout << "Приоритет: " << job.priority << endl;

        time_t now = time(nullptr);
        string timeStr = ctime(&now);
        timeStr.pop_back();

        statList[statCount] = { job.user, job.document, timeStr };
        statQueue.Enqueue(statCount);
        statCount++;

        cout << "Печать завершена в: " << timeStr << endl;
    }

    void ShowStats() {
        if (statQueue.IsEmpty()) {
            cout << "Нет статистики.\n";
            return;
        }

        cout << "\n===== Статистика печати =====\n";
        for (int i = 0; i < statQueue.getSize(); i++) {
            int idx = i;
            PrintStat st = statList[idx];
            cout << i + 1 << ") Пользователь: " << st.user
                 << " | Документ: " << st.document
                 << " | Время: " << st.timePrinted << endl;
        }
    }
};

//------------------------ main -----------------------------

int menu() {
    cout << "\n=== Меню ===\n";
    cout << "1) Добавить задание\n";
    cout << "2) Печать следующего\n";
    cout << "3) Показать статистику\n";
    cout << "4) Выход\n";
    cout << "Выберите пункт: ";
    int c;
    cin >> c;
    cin.ignore();
    return c;
}

int main() {
    setlocale(LC_ALL, "Russian");
    Printer printer(10);

    while (true) {
        switch (menu()) {
        case 1: {
            string user, doc;
            int pr;
            cout << "Введите имя пользователя: ";
            getline(cin, user);
            cout << "Введите имя документа: ";
            getline(cin, doc);
            cout << "Введите приоритет (1-10): ";
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
            cout << "Неверный пункт меню!\n";
        }
    }
}
