#include <iostream>
#include <fstream>
#include <map>
using namespace std;

string normalize(const string& w) {
    string r;
    for (char c : w)
        if (islower(c) || isupper(c)) r += tolower(c);
    return r;
}

int main() {
    ifstream in("input.txt");
    if (!in) { cerr << "error in"; return 1; }
    string text((istreambuf_iterator<char>(in)), {});
    in.close();

    cout << "Слова у тексті:" << endl;
    map<string, int> m;
    stringstream ss(text);
    string w;
    while (ss >> w) {
        string c = normalize(w);
        if (!c.empty()) {
            cout << c << endl;
            m[c]++;
        }
    }
    cout << endl;

    string top; int cnt = 0;
    for (auto& p : m)
        if (p.second > cnt) { cnt = p.second; top = p.first; }

    cout << "Найбільш уживане слово: \"" << top
         << "\" (зустрічається " << cnt << " разів)" << endl << endl;

    ofstream out("output.txt");
    if (!out) { cerr << "error out"; return 1; }
    out << "Найбільш уживане слово: \"" << top
        << "\" (зустрічається " << cnt << " разів)" << endl;

    cout << "Результати збережено у файлі output.txt" << endl;
    return 0;
}
