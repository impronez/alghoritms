/*Организовать  в основной  памяти  с помощью указателей
очередь  из  стеков. Обеспечить  операции  ведения  стека  из
начала  очереди, дополнения  и  продвижения  очереди,  выдачи
содержимого очереди (9).*/
// Орзаев Святослав, ПС-11, Microsoft Visual Studio 2022

#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

struct Stack
{
    string name;
    int keySt;
    Stack *next;
};
struct Queue
{
    int size;
    Stack *first;
    Stack *last;
};

void PushSt(Stack*& p, int elem)  // включение в стек
{
    Stack* t = new Stack;
    t->keySt = elem;
    t->next = p;
    p = t;
}

void PopSt(Stack*& p)             // удаление из стека
{
    Stack* t = p;
    p = p->next;
    delete t;
}

void OutputSt(Stack* p)            // вывод содержимого стека на экран
{
    Stack* t = p;
    while (t)
    {
        printf("%d ", t->keySt);
        t = t->next;
    }
    printf("\n");
}

void ClearSt(Stack* p)            // очистка стека
{
    while (p)
    {
        Stack* t = p;
        p = p->next;
        delete t;
    }
}

void StackFormation() {
    Stack* top = 0;
    int answer = 0;
    while (answer != 5)
    {
        cout << "Меню для работы со стеком:\n" << "1 - Включение в стек;\n" << "2 - Удаление из стека;\n" << "3 - Выдача стека;\n" << "4 - Удаление всего стека;\n" << "5 - Выход во внешнее меню.\n" << "Введите число: ";
        cin >> answer;
        switch (answer)
        {
        case 1:
            int k;
            printf("Введите целое число: ");
            cin >> k;
            PushSt(top, k);
            break;
        case 2:
            if (top)
            {
                PopSt(top);
            }
            else printf("Стек пуст!\n");
            break;
        case 3:
            if (top)
            {
                cout << endl << "Стек: ";
                OutputSt(top);
            }
            else printf("Стек пуст!\n");
            break;
        case 4:
            if (top)
            {
                ClearSt(top);
            }
            else {
                cout << endl;
                printf("Стек пуст!\n");
            }
            top = 0;   // функция clear не возвращает top!
            break;
        case 5:
            break;
        default:
            cout << "Неверное значение! Введите корректное значение: ";
        }
        cout << endl;
    }
}

void AddQ(Queue* Q, string name)
{
    Stack *newStack = new Stack;

    if (Q->first == NULL)
    {
        cout << "NULL!!" << endl;
        Q->first = newStack;
        Q->first->next = NULL;
        Q->first->name = name;
        Q->last = Q->first;
    }
    else {
        cout << "NOT NULL!!" << endl;
        newStack->name = name;
        newStack->next = NULL;
        Q->last->next = newStack;
        Q->last = newStack;
    }
    StackFormation();
}

void ShowQ(Queue* Q)
{
    int counter = 1;
    Stack* p = Q->first;
    cout << "Содержимое стеков: " << endl;
    while (p != NULL)
    {
        cout << counter << " - " << p->name << ":" << endl;
        OutputSt(p);
        p = p->next;
        counter += 1;
    }
}

void PromotionQ(Queue* Q)
{
    Stack *t = Q->first;
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
        cout << "Меню работы с очередью:\n" << "1 - Добавить стек в очередь;\n" << "2 - Продвижение очереди;\n" << "3 - Содержимое очереди;\n" << "4 - Очиcтка очереди;\n" << "5 - Arividerchi.\n" << "Введите число: ";
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
            if (Q.first != NULL)
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
            p = Q.first;
            ClearSt(p);
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