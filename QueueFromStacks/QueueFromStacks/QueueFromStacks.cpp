/*������������  � ��������  ������  � ������� ����������
�������  ��  ������. ����������  ��������  �������  �����  ��
������  �������, ����������  �  �����������  �������,  ������
����������� ������� (9).*/
// ������ ���������, ��-11, Microsoft Visual Studio 2022

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

void PushSt(Stack*& p, int elem)  // ��������� � ����
{
    Stack* t = new Stack;
    t->keySt = elem;
    t->next = p;
    p = t;
}

void PopSt(Stack*& p)             // �������� �� �����
{
    Stack* t = p;
    p = p->next;
    delete t;
}

void OutputSt(Stack* p)            // ����� ����������� ����� �� �����
{
    Stack* t = p;
    while (t)
    {
        printf("%d ", t->keySt);
        t = t->next;
    }
    printf("\n");
}

void ClearSt(Stack* p)            // ������� �����
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
        cout << "���� ��� ������ �� ������:\n" << "1 - ��������� � ����;\n" << "2 - �������� �� �����;\n" << "3 - ������ �����;\n" << "4 - �������� ����� �����;\n" << "5 - ����� �� ������� ����.\n" << "������� �����: ";
        cin >> answer;
        switch (answer)
        {
        case 1:
            int k;
            printf("������� ����� �����: ");
            cin >> k;
            PushSt(top, k);
            break;
        case 2:
            if (top)
            {
                PopSt(top);
            }
            else printf("���� ����!\n");
            break;
        case 3:
            if (top)
            {
                cout << endl << "����: ";
                OutputSt(top);
            }
            else printf("���� ����!\n");
            break;
        case 4:
            if (top)
            {
                ClearSt(top);
            }
            else {
                cout << endl;
                printf("���� ����!\n");
            }
            top = 0;   // ������� clear �� ���������� top!
            break;
        case 5:
            break;
        default:
            cout << "�������� ��������! ������� ���������� ��������: ";
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
    cout << "���������� ������: " << endl;
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
        cout << "���� ������ � ��������:\n" << "1 - �������� ���� � �������;\n" << "2 - ����������� �������;\n" << "3 - ���������� �������;\n" << "4 - ���c��� �������;\n" << "5 - Arividerchi.\n" << "������� �����: ";
        cin >> answer;
        string name = "";
        switch (answer)
        {
        case 1:
            cout << "������� ��� �����: ";
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
                cout << "������� �����!\n";
            }
            break;
        case 3:
            if (Q.first != NULL)
            {
                ShowQ(&Q);
            }
            else 
            {
                cout << "������� �����!\n";
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
                cout << "������� �����!\n";
            }
            break;

        case 5: 
            p = Q.first;
            ClearSt(p);
            break;

        default:
            cout << "������� ���������� ��������: ";
        }
    }
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    QueueFormation();    
}