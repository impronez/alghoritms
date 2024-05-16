#include <iostream>
#include <set>
#include <iterator>

using namespace std;

int main() {
    setlocale(0, "");
    cout << "������� ��������� ���������� ������: ";
    int n; cin >> n;

    multiset <int> files;

    for (int i = 0; i < n; i++) {
        cout << i + 1 << ") ������� ������ ����� ��� ����������: ";
        int a; cin >> a;
        files.insert(a);
    }

    cout << endl << "������� ���������� ��������: ";
    q; cin >> q;

    for (int i = 0; i < q; i++) {
        cout << i + 1 << ") ";
        string operation; cin >> operation;

        if (operation == "add" || operation == "+") {
            cout << "������� ������ ����� �����: ";
            int value; cin >> value;

            files.insert(value);

            cout << "����� �������� ��������: ";
            copy(files.begin(), files.end(), ostream_iterator(cout, " "));

            cout << endl;
        }

        if (operation == "erase" || operation == "-") {
            cout << "������� ����� ������ ��� �������� ��� ��������: ";
            string temp; cin >> temp;

            if (temp == "one" || temp == "1") {
                cout << "������� ��������: ";
                int value; cin >> value;

                multiset <int> ::iterator it = files.find(value);
                if (it == files.end()) {
                    cout << "������ ������� �� ����������!" << endl;
                    continue;
                }

                files.erase(it);
            }

            if (temp == "all" || temp == "*") {
                cout << "������� ��������: ";
                int value; cin >> value;

                multiset <int> ::iterator it = files.find(value);

                if (!files.count(value)) {
                    cout << "����� �������� �� ����������!" << endl;
                    continue;
                }

                files.erase(value);
            }
            cout << "����� �������� ��������: ";
            copy(files.begin(), files.end(), ostream_iterator(cout, " "));
            cout << endl;
        }

        if (operation == "lower_bound" || operation == ">=") {
            cout << "������� �������� ��� ������: ";
            int value; cin >> value;

            multiset <int> ::iterator it;
            it = files.lower_bound(value);

            if (it == files.end()) {
                cout << "�������� >= " << value << " �� ����������!" << endl;
                continue;
            }
            cout << *it << endl;
        }

        if (operation == "upper_bound" || operation == ">") {
            cout << "������� �������� ��� ������: ";
            int value; cin >> value;

            multiset <int> ::iterator it;
            it = files.upper_bound(value);

            if (it == files.end()) {
                cout << "�������� > " << value << " �� ����������!" << endl;
                continue;
            }

            cout << *it << endl;
        }
    }

    system("pause");
    return 0;
}