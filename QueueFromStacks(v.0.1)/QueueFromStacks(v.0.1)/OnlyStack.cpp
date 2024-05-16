/*Организовать  в основной  памяти  с помощью указателей
очередь  из  стеков. Обеспечить  операции  ведения  стека  из
начала  очереди, дополнения  и  продвижения  очереди,  выдачи
содержимого очереди (9).*/
// Орзаев Святослав, ПС-11, Microsoft Visual Studio 2022

#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

struct ElemSt
{
    int keySt;
    ElemSt* last;
};
struct Stack
{
    string name;
    ElemSt* key;
};
struct Queue
{
    Stack* first;
    Stack* last;
};

void PushSt(Stack*& p, int elem)  // включение в стек
{
    ElemSt* t = new ElemSt;
    t->keySt = elem;
    if (p->key == NULL)
    {
        t->last = NULL;
        p->key = t;
    }
    else
    {
        t->last = p->key;
        p->key = t;
    }
}

void PopSt(Stack*& p)             // удаление из стека
{
    ElemSt* t = p->key;
    p->key = t->last;
    delete t;
}

void OutSt(Stack* p)
{
    ElemSt* t = p->key;
    while (t)
    {
        printf("%d ", t->keySt);
        t = t->last;
    }
    printf("\n");
}

void ClearSt(Stack*& p)
{
    while (p->key)
    {
        ElemSt* t = p->key;
        p->key = t->last;
        delete t;
    }
}



void StackFormation()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Stack* st = new Stack;
    st->key = NULL;
    int answer = 0;
    while (answer != 5)
    {
        cout << "1 - push, 2 - pop, 3 - out, 4 - clear, 5 - exit: ";
        cin >> answer;
        switch (answer)
        {
        case 1:
            int k;
            cout << "in num: ";
            cin >> k;
            PushSt(st, k);
            break;
        case 2:
            if (st->key)
            {
                PopSt(st);
            }
            else printf("Стек пуст!\n");
            break;
        case 3: 
            if (st->key)
            {
                OutSt(st);
            }
            else printf("Стек пуст!\n");
            break;
        case 4:
            if (st->key)
            {
                ClearSt(st);
            }
            else printf("Стек пуст!\n");
            break;
        case 5: 
            delete st;
            break;
        }
    }
    return;
}



int main()
{

}
