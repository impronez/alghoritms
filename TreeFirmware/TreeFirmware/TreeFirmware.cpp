/* 18. Задано бинарное  дерево.  Построить  прошитое   дерево,
соответствующее обходу сверху вниз. Составить программу удале-
ния поддерева с  корнем  в  заданной  вершине  без  повторного
построения дерева. Конечное дерево должно оставаться прошитым. 
Выдать информацию о нитях исходного и конечного деревьев (12).
Орзаев Святослав, ПС-21, Microsoft Visual Studio 2022.*/
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
    Tree* fath;                  // отец в исходном дереве
    vector<Tree*> sons;   // указатели на сыновей
};

int read_from_file(ifstream& F, Tree*& r);  // с вектором сыновей 
// чтение из файла, формирование дерева
void print_down(Tree* p, int lev);
// выдача сверху вниз с точками

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

int read_from_file(ifstream& F, Tree*& r)       // с вектором сыновей
{
    char buf[DL];
    int i, j, k, m, len;
    Tree* p, * q, * t;       // *root = NULL 
    m = -1;                 // уровень предыдущей вершины
    t = 0;                    // указатель на предыдущую вершину
    while (!F.eof())
    {
        F >> buf;
        len = strlen(buf);
        if (len == 0) continue;
        // если конец файла в следующей строке или пустая строка
        k = 0;
        while (buf[k] == '.') k++;     // k-уровень вершины
        p = new Tree;
        i = 0;
        j = k;
        while (p->name[i++] = buf[j++]);
        // копирование вместе с '\0’
        p->urov = k;
        if (k == 0)                    // корень
        {
            r = p;
            t = r;
            m = 0;
            continue;
        }
        if (k > m)       // переход на следующий уровень
        {
            t->sons.push_back(p);
            p->fath = t;
        }
        else if (k == m)            // тот же уровень
        {
            q = t->fath;
            q->sons.push_back(p);
            p->fath = q;
        }
        else        // подъем по дереву на m-k+1 уровней
        {
            q = t;
            for (i = 0; i <= m - k; i++) q = q->fath;
            // q - отец вводимой вершины p
            q->sons.push_back(p);
            p->fath = q;
        }
        m = k;      // текущий уровень
        t = p;      // текущая вершина
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

