/* 18. ������ ��������  ������.  ���������  ��������   ������,
��������������� ������ ������ ����. ��������� ��������� �����-
��� ��������� �  ������  �  ��������  �������  ���  ����������
���������� ������. �������� ������ ������ ���������� ��������. 
������ ���������� � ����� ��������� � ��������� �������� (12).
������ ���������, ��-21, Microsoft Visual Studio 2022.*/
#include <string>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int DL = 20;

struct Tree
{
    char name[DL];
    int urov;
    Tree* fath;                  // ���� � �������� ������
    vector<Tree*> sons;   // ��������� �� �������
};

int read_from_file(ifstream& F, Tree*& r);  // � �������� ������� 
// ������ �� �����, ������������ ������
void print_down(Tree* p, int lev);
// ������ ������ ���� � �������

using namespace std;

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "\nNumber parameters is wrong";
        return 1;
    }
    ifstream Fin(argv[1]);
    if (!Fin)
    {
        cout << "\nCan not open file %s" << argv[1];
        return 1;
    }
    Tree* root = NULL;
    read_from_file(Fin, root);
    getchar();
    print_down(root, 0);
}

int read_from_file(ifstream& F, Tree*& r)       // � �������� �������
{
    char buf[DL];
    int i, j, k, m, len;
    Tree* p, * q, * t;       // *root = NULL 
    m = -1;                 // ������� ���������� �������
    t = 0;                    // ��������� �� ���������� �������
    while (!F.eof())
    {
        F >> buf;
        len = strlen(buf);
        if (len == 0) continue;
        // ���� ����� ����� � ��������� ������ ��� ������ ������
        k = 0;
        while (buf[k] == '.') k++;     // k-������� �������
        p = new Tree;
        i = 0;
        j = k;
        while (p->name[i++] = buf[j++]);
        // ����������� ������ � '\0�
        p->urov = k;
        if (k == 0)                    // ������
        {
            r = p;
            t = r;
            m = 0;
            continue;
        }
        if (k > m)       // ������� �� ��������� �������
        {
            t->sons.push_back(p);
            p->fath = t;
        }
        else if (k == m)            // ��� �� �������
        {
            q = t->fath;
            q->sons.push_back(p);
            p->fath = q;
        }
        else        // ������ �� ������ �� m-k+1 �������
        {
            q = t;
            for (i = 0; i <= m - k; i++) q = q->fath;
            // q - ���� �������� ������� p
            q->sons.push_back(p);
            p->fath = q;
        }
        m = k;      // ������� �������
        t = p;      // ������� �������
    }
    return 0;
}

void print_down(Tree* p, int level)
{
    for (int i = 0; i < level; i++) cout << '.';
    cout << p->name << endl;
    if (p->sons.size())
    {
        for (int i = 0; i < p->sons.size(); i++)
            print_down(p->sons[i], level + 1);
    }
}

