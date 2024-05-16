#include <iostream>
#include <set>
#include <iterator>

using namespace std;

int main() {
    setlocale(0, "");
    cout << "Введите начальное количество файлов: ";
    int n; cin >> n;

    multiset <int> files;

    for (int i = 0; i < n; i++) {
        cout << i + 1 << ") Введите индекс папки для добавления: ";
        int a; cin >> a;
        files.insert(a);
    }

    cout << endl << "Укажите количество операций: ";
    q; cin >> q;

    for (int i = 0; i < q; i++) {
        cout << i + 1 << ") ";
        string operation; cin >> operation;

        if (operation == "add" || operation == "+") {
            cout << "Введите индекс новой папки: ";
            int value; cin >> value;

            files.insert(value);

            cout << "Новые значения индексов: ";
            copy(files.begin(), files.end(), ostream_iterator(cout, " "));

            cout << endl;
        }

        if (operation == "erase" || operation == "-") {
            cout << "Укажите какой именно тип операции вам подходит: ";
            string temp; cin >> temp;

            if (temp == "one" || temp == "1") {
                cout << "Введите значение: ";
                int value; cin >> value;

                multiset <int> ::iterator it = files.find(value);
                if (it == files.end()) {
                    cout << "Такого индекса не существует!" << endl;
                    continue;
                }

                files.erase(it);
            }

            if (temp == "all" || temp == "*") {
                cout << "Введите значение: ";
                int value; cin >> value;

                multiset <int> ::iterator it = files.find(value);

                if (!files.count(value)) {
                    cout << "Таких индексов не существует!" << endl;
                    continue;
                }

                files.erase(value);
            }
            cout << "Новые значения индексов: ";
            copy(files.begin(), files.end(), ostream_iterator(cout, " "));
            cout << endl;
        }

        if (operation == "lower_bound" || operation == ">=") {
            cout << "Введите значение для поиска: ";
            int value; cin >> value;

            multiset <int> ::iterator it;
            it = files.lower_bound(value);

            if (it == files.end()) {
                cout << "Элемента >= " << value << " не существует!" << endl;
                continue;
            }
            cout << *it << endl;
        }

        if (operation == "upper_bound" || operation == ">") {
            cout << "Введите значение для поиска: ";
            int value; cin >> value;

            multiset <int> ::iterator it;
            it = files.upper_bound(value);

            if (it == files.end()) {
                cout << "Элемента > " << value << " не существует!" << endl;
                continue;
            }

            cout << *it << endl;
        }
    }

    system("pause");
    return 0;
}