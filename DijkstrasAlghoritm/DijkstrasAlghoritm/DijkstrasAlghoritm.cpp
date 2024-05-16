/* 22. Имеется сеть автомобильных дорог. По  некоторым дорогам
можно  проехать  только  в одном  направлении. Известна  длина 
каждой дороги, причем она может быть разной в  зависимости  от 
направления. С помощью алгоритма Дейкстры найти цикл минимальной
длины из заданного города (10).
Орзаев Святослав, ПС-21, Microsoft Visual Studio 2022*/

#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

const int SL = 255;

struct Town
{
    int number;
    string name;
    vector<pair<int, int>> communication;
};

int CharToInt(char a[])
{
    string s = string(a);
    int i = atoi(s.c_str());
    return i;
}

vector<Town*> ReadTowns(ifstream& F)
{
    vector<Town*> towns;
    char buf[SL];

    while (!F.eof())
    {
        F >> buf;                   //считывание номера
        int num = CharToInt(buf);
              
        string name;                //считывание названия
        getline(F, name);
        if (name[0] = ' ')
        {
            name.erase(0, 1);
        }

        Town* town = new Town;
        town->number = num - 1;
        town->name = name;
        towns.push_back(town);
    }
    return towns;
}

Town* GetTown(vector<Town*> towns, int num)
{
    Town* town;
    for (int i = 0; i < towns.size(); i++)
    {
        if (towns.at(i)->number == num)
        {
            town = towns.at(i);
            return town;
        }
    }
}

vector<Town*> SetCommunications(ifstream& F, vector<Town*> towns)
{
    Town* fromTown, * toTown;
    char buf[SL];

    pair<int, int> com;
    for (int i = 0; i < towns.size(); i++)
    {
        towns[i]->communication.resize(towns.size());
        for (int j = 0; j < towns.size(); j++)
        {
            com.first = j, com.second = INT_MAX;
            towns[i]->communication[j] = com;
        }
    }

    while (!F.eof())
    {
        F >> buf;
        int firstNum = CharToInt(buf) - 1;

        F >> buf;
        int secondNum = CharToInt(buf) - 1;

        F >> buf;
        int distance = CharToInt(buf);

        fromTown = GetTown(towns, firstNum);
        toTown = GetTown(towns, secondNum);

        pair<int, int> com;
        com.first = toTown->number, com.second = distance;
        fromTown->communication.at(secondNum) = com;
    }

    return towns;
}

Town* SearchTown(vector<Town*> towns, string name)
{
    if (!towns.empty())
    {
        for (int i = 0; i < towns.size(); i++)
        {
            if (name == towns[i]->name)
            {
                return towns[i];
            }
        }
    }
    return NULL;
}

void OutTowns(vector<Town*> towns, vector<int> cicle, int &k, int s)
{
    if (k != s)
    {
        OutTowns(towns, cicle, cicle.at(k), s);
        cout << towns[k]->name << " -> ";
    }
}

void AlghoritmDijkstras(vector<Town*> towns, Town* sourceTown)
{
    int v = towns.size(), s = sourceTown->number;
    vector<int> dist(v, INT_MAX);
    dist[s] = 0;
    vector<boolean> visited(v, false);
    int index = -1;
    vector<int> cicle(v, -1);
    for (int i = 0; i < v + 1; i++)
    {
        if (i == v) // для нахождения цикла
        {
            visited[s] = false;
            dist[s] = INT_MAX;
        }
        int min = INT_MAX;
        for (int j = 0; j < v; j++) // поиск минимального пути из возможных
        {
            if (dist[j] != INT_MAX)
            {
                for (int k = 0; k < towns[j]->communication.size(); k++)
                {
                    int id = towns[j]->communication[k].first;
                    int distance = towns[j]->communication[k].second;
                    if (!visited[id] && distance < min)
                    {
                        min = distance;
                        index = id;
                    }
                }
            }
        }
        int distance = INT_MAX;
        for (int j = 0; j < v; j++) // подсчёт расстояний
        {
            for (int k = 0; k < towns[j]->communication.size(); k++)
            {
                if (towns[j]->communication[k].first == index)
                {
                    distance = towns[j]->communication[k].second;
                }
            }
            if (!visited[index] && distance != INT_MAX && dist[j] != INT_MAX && (dist[j] + distance < dist[index]))
            {
                cicle.at(index) = j;
                dist[index] = dist[j] + distance;
            }
        }
        visited[index] = true;
    }  

    cout << "Кратчайший цикл = " << dist[s] << endl;
    int k;
    cout << towns[s]->name << " -> ";
    k = cicle.at(s);
    OutTowns(towns, cicle, k, s);
    cout << towns[s]->name << endl;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    vector<Town*> towns;
    string name;
    Town* town;

    ifstream fTowns("towns1.txt"), communications("communications1.txt");
    if (fTowns && communications)
    {
        towns = ReadTowns(fTowns);
        towns = SetCommunications(communications, towns);
        int k = 0;
        while (k != 2)
        {
            cout << "Меню: 1 - поиск минимального цикла, 2 - выход.\nВведите число: ";
            cin >> k;
            switch (k) {
            case 1:
                cout << "Введите название города: ";
                getline(cin>>ws, name);
                cout << endl;
                town = SearchTown(towns, name);
                if (!town)
                {
                    cout << "Город не найден!\n";
                    break;
                }
                AlghoritmDijkstras(towns, town);
                break;
            case 2:
                break;
            default:
                break;
            }
        }
    }
    else { cout << "bad..."; }

    for (int i = 0; i < towns.size(); i++)
    {
        town = towns[i];
        delete town;
    }
        
    fTowns.close();
    communications.close();
}