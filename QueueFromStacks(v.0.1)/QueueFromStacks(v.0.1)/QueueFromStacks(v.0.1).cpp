/* 20. Организовать  в основной  памяти  с помощью указателей
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
    ElemSt* prev;
};
struct Stack
{
    string name;
    ElemSt* key;
    Stack* next;
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
        t->prev = NULL;
        p->key = t;
    }
    else
    {
        t->prev = p->key;
        p->key = t;
    }
}

void PopSt(Stack*& p)             // удаление из стека
{
    ElemSt* t = p->key;
    p->key = t->prev;
    delete t;
}

void OutSt(Stack* p)
{
    ElemSt* t = p->key;
    while (t)
    {
        printf("%d ", t->keySt);
        t = t->prev;
    }
    printf("\n");
}

void ClearSt(Stack*& p)
{
    while (p->key)
    {
        ElemSt* t = p->key;
        p->key = t->prev;
        delete t;
    }
}

void StackFormation(Stack*& st)
{
    st->key = NULL;
    int answer = 0;
    while (answer != 5)
    {
        //cout << "1 - push, 2 - pop, 3 - out, 4 - clear, 5 - exit: " << endl;
        cout << "Меню стека: \n1 - включение в стек; \n2 - удаление из стека; \n3 - выдача стека; \n4 - удаление всего стека; \n5 - выход во внешнее меню. \nВведите число: ";
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
            break;
        default:
            cout << "Неверное значение! Введите корректное значение: ";
        }
    }
}

void AddQ(Queue* Q, string name)
{
    Stack* newStack = new Stack;
    newStack->name = name;
    newStack->next = NULL;
    newStack->key = NULL;

    if (Q->first == NULL)
    {
        Q->first = newStack;
        Q->last = Q->first;
    }
    else {
        Q->last->next = newStack;
        Q->last = newStack;
    }
    cout << endl;
    StackFormation(newStack);
    cout << endl;
}

void ShowQ(Queue* Q)
{
    cout << endl;
    int counter = 1;
    Stack* p = Q->first;
    cout << "Содержимое стеков: " << endl;
    while (p != NULL)
    {
        cout << counter << " - " << p->name << ": ";
        OutSt(p);
        p = p->next;
        counter += 1;
    }
    cout << endl;
}

void PromotionQ(Queue* Q)
{
    Stack* t = Q->first;
    if (Q->first == Q->last)
    {
        Q->first = Q->last = NULL;
    }
    else {
        Q->first = Q->first->next;
    }
    delete t;
}

void QueueFormation() {
    Queue Q = { NULL, NULL };
    Stack* p = NULL;
    int answer = 0;
    while (answer != 5)
    {
        cout << "Меню работы с очередью: \n1 - добавить стек в очередь; \n2 - продвижение очереди; \n3 - содержимое очереди; \n4 - очиcтка очереди; \n5 - arividerchi. \nВведите число: ";
        cin >> answer;
        string name = "";
        switch (answer)
        {
        case 1:
            cout << "Введите имя стека: ";
            cin >> name;
            AddQ(&Q, name);
            break;
        case 2:
            if (Q.first)
            {
                PromotionQ(&Q);
            }
            else
            {
                cout << "Очередь пуста!\n";
            }
            break;
        case 3:
            if (Q.first != NULL)
            {
                ShowQ(&Q);
            }
            else
            {
                cout << "Очередь пуста!\n";
            }
            break;
        case 4:
            if (Q.first != NULL)
            {
                while (Q.first != NULL)
                {
                    PromotionQ(&Q);
                }
            }
            else
            {
                cout << "Очередь пуста!\n";
            }
            break;
        case 5:
            if (Q.first)
            {
                while (Q.first)
                {
                    p = Q.first;
                    ClearSt(p);
                    Q.first = p->next;
                    delete p;
                }
                Q.first = Q.last = NULL;
            }
            break;
        default:
            cout << "Введите корректное значение: ";
        }
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    QueueFormation();
}
