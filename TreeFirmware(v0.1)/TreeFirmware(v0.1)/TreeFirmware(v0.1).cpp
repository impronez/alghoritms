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

using namespace std;

const int DL = 20;

struct Tree
{
    char name[DL];
    Tree* fath, * right, * left;
};

struct FirmwareTree
{
    string name;
    FirmwareTree* left, * right, * fath;
    boolean rightIsThread;
};

void ReadTreeFromFile(ifstream& F, Tree*& r)
{
    char buf[DL];
    int i, j, k, m, len = 0;
    m = -1;

    Tree* p, *l = NULL;

    while (!F.eof())
    {
        F >> buf; 
        len = strlen(buf);
        if (len == 0) continue;
        i = k = 0;
        while (buf[k] == '.') k++;
        p = new Tree;
        p->fath = p->left = p->right = NULL;
        j = k;
        while (p->name[i++] = buf[j++]);

        if (k == 0)
        {
            r = p;
            l = p;
            m++;
            continue;
        }

        if (k > m)
        {
            p->fath = l;
            l->left = p;
            l = p;
            m = k;
            continue;
        }

        if (k == m)
        {
            l = l->fath;
            l->right = p;
            p->fath = l;
            l = p;
            continue;
        }

        if (k < m)
        {
            while (m != (k - 1))
            {
                m--;
                l = l->fath;
            }
            m++;
            l->right = p;
            p->fath = l;
            l = p;
            continue;
        } 
    }

}

void PrintTree(Tree* p, int level)
{
    if (p)
    {
        PrintTree(p->right, level + 1);
        for (int i = 0; i < level; i++) cout << "  ";
        cout << p->name << endl;
        PrintTree(p->left, level + 1);
    }
}

FirmwareTree* CopyToFTree(Tree* tree)
{
    if (tree == nullptr)
    {
        return NULL;
    }

    FirmwareTree* fTree = new FirmwareTree;
    fTree->rightIsThread = false;
    fTree->fath = fTree->left = fTree->right = NULL;
    fTree->name = string(tree->name);

    fTree->left = CopyToFTree(tree->left);
    if (fTree->left)
    {
        fTree->left->fath = fTree;
    }

    fTree->right = CopyToFTree(tree->right);
    if (fTree->right)
    {
        fTree->right->fath = fTree;
    }

    return fTree;
}

void PrintFTree(FirmwareTree* fTree, int level)
{
    if (fTree)
    {
        if (!fTree->rightIsThread)
        {
            PrintFTree(fTree->right, level + 1);
        }
        for (int i = 0; i < level; i++) cout << "  ";
        cout << fTree->name << endl;
        PrintFTree(fTree->left, level + 1);
    }
}

void AddThreads(FirmwareTree*& fTree, FirmwareTree*& tmp)
{
    if (fTree)
    {
        if (tmp)
        {
            tmp->right = fTree;
            tmp = NULL;
        }
        AddThreads(fTree->left, tmp);
        if (!fTree->left)
        {
            fTree->rightIsThread = true;
            fTree->right = tmp;
            tmp = fTree;
        }
        AddThreads(fTree->right, tmp);
    }
}

void PrintThreads(FirmwareTree*& fTree)
{
    if (fTree)
    {
        boolean isEnd = false, switcher = false;
        while (!isEnd)
        {
            while (fTree->left)
            {
                fTree = fTree->left;
            }
            if (fTree->rightIsThread)
            {
                cout << fTree->name;
                switcher = true;
            }
            if (fTree->right)
            {
                fTree = fTree->right;
            }
            if (switcher)
            {
                cout << fTree->name << " ";
            }
            if (!fTree->left && !fTree->right)
            {
                isEnd = true;
            }
            switcher = false;
        }
        while (fTree->fath)
        {
            fTree = fTree->fath;
        }
        cout << endl;
    }
}

FirmwareTree* SearchTop(FirmwareTree* fTree, string name)
{
    if (fTree)
    {
        while (name != fTree->name)
        {
            if (!fTree->left && !fTree->right)
            {
                return NULL;
            }
            if (fTree->left)
            {
                fTree = fTree->left;
            }
            else if (fTree->right)
            {
                fTree = fTree->right;
            }
        }
        return fTree;
    }
}

void FindPtrOnDeletingPtr(FirmwareTree*& fTree, FirmwareTree*& deletingPtr, FirmwareTree*& ptr, boolean &found)
{
    if (fTree && !found)
    {
        FindPtrOnDeletingPtr(fTree->left, deletingPtr, ptr, found);
        if (!fTree->rightIsThread && !found)
        {
            FindPtrOnDeletingPtr(fTree->right, deletingPtr, ptr, found);
        }
        if (fTree->right == deletingPtr && fTree->rightIsThread)
        {
            found = true;
            ptr = fTree;
        }
    }
}

void FindLastThreadOfDeletingPtr(FirmwareTree* deletingPtr, FirmwareTree*& tmp, boolean &found)
{
    if (deletingPtr)
    {
        if (!deletingPtr->rightIsThread)
        {
            FindLastThreadOfDeletingPtr(deletingPtr->right, tmp, found);
        }
        else
        {
            found = true;
            tmp = deletingPtr->right;
        }
        if (!found)
        {
            FindLastThreadOfDeletingPtr(deletingPtr->left, tmp, found);
        }        
    }
}

void DeleteSubtree(FirmwareTree* deletingPtr)
{
    if (deletingPtr)
    {
        DeleteSubtree(deletingPtr->left);
        if (!deletingPtr->rightIsThread)
        {
            DeleteSubtree(deletingPtr->right);
        }
        if (deletingPtr == deletingPtr->fath->left)
        {
            deletingPtr->fath->left = NULL;
        }
        else if (deletingPtr == deletingPtr->fath->right)
        {
            deletingPtr->fath->right = NULL;
        }
        delete deletingPtr;
    }
}

void FindSonOfTree(FirmwareTree*& fTree, FirmwareTree*& deletingPtr, boolean &found)
{
    if (deletingPtr && !found)
    {
        FindSonOfTree(fTree, deletingPtr->left, found);
        if (!deletingPtr->rightIsThread)
        {
            FindSonOfTree(fTree, deletingPtr->right, found);
        }
        if (deletingPtr->name == fTree->name)
        {
            found = true;
        }
    }
}

void ChangeThreads(FirmwareTree*& fTree, FirmwareTree*& deletingPtr)
{
    FirmwareTree* tmp = NULL, * ptr = NULL;
    boolean found = false;
    FindPtrOnDeletingPtr(fTree, deletingPtr, ptr, found);
    found = false;
    FindLastThreadOfDeletingPtr(deletingPtr, tmp, found);
    if (tmp && !ptr && deletingPtr->fath != tmp->fath)
    {
        ptr = deletingPtr->fath;
    }
    found = false;
    if (tmp) 
    {
        FindSonOfTree(tmp, deletingPtr, found);
        if (found)
        {
            tmp = NULL;
        }
    }
    DeleteSubtree(deletingPtr);
    if (ptr && tmp)
    {
        ptr->right = tmp;
        ptr->rightIsThread = true;
    }
    else if (ptr && !tmp)
    {
        ptr->rightIsThread = false;
        ptr->right = NULL;
    }

}

void ChangeTheTree(FirmwareTree*& fTree, FirmwareTree*& deletingPtr)
{
    int level = 0;
    FirmwareTree* tmp = NULL, *ptr = NULL;
    cout << "Нити исходного дерева: ";
    PrintThreads(fTree);
    ChangeThreads(fTree, deletingPtr);
    cout << "Нити конечного дерева: ";
    PrintThreads(fTree);
    PrintFTree(fTree, level);
}

int main()
{
    SetConsoleCP(1251);                
    SetConsoleOutputCP(1251);

    ifstream file("tree.txt");
    if (file)
    {
        int switcher = 0, level = 0;
        string name;
        Tree* root = NULL;
        FirmwareTree* tmp = NULL;
        ReadTreeFromFile(file, root);
        FirmwareTree* fRoot = CopyToFTree(root);
        AddThreads(fRoot, tmp);
        while (switcher != 4)
        {
            cout << "Меню:\n1 - Вывод обычного дерева,\n2 - показать нити прошитого дерева,\n3 - удалить поддерево,\n4 - выход.\nВведите число: ";
            cin >> switcher;

            switch (switcher)
            {
            case 1:
                level = 0;
                PrintTree(root, level);
                cout << endl;
                break;
            case 2:
                cout << "Нити дерева: ";
                PrintThreads(fRoot);
                cout << endl;
                break;
            case 3:
                cout << "Введите имя вершины: ";
                cin >> name;
                tmp = SearchTop(fRoot, name);
                if (!tmp)
                {
                    cout << "Вершина не найдена!\n";
                    break;
                }
                else {
                    if (tmp == fRoot)
                    {
                        cout << "Попытка удаления корня дерева!\n";
                        break;
                    }
                    else
                    {
                        ChangeTheTree(fRoot, tmp);
                    }
                }
                break;
            case 4:
                break;
            case 5:
                if (fRoot->left->rightIsThread)
                {
                    cout << "yeee\n";
                }
                break;
            default:
                cout << "Неверное значение! Введите корректное значение!\n";
                cout << endl;
            }
        }
        delete root;
        delete fRoot;
    }
    else
    {
        cout << "Error of reading file!" << endl;
    }
    file.close();
}
