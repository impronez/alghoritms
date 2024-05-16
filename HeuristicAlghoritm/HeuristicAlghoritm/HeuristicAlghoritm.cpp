/* 16. Реализовать  эвристический   алгоритм   решения  задачи
коммивояжера на неориентированном полном  графе  на  основании 
метода Краскала нахождения остовного дерева. Проиллюстрировать
по шагам этапы поиска (11).
Орзаев Святослав, ПС-21, Microsoft Visual Studio */

#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include <Windows.h>

using namespace std;

vector<vector<int>> ReadData(fstream& F)
{
    int size = 0;
    F >> size;
    vector<vector<int>> matrix;
    matrix.resize(size, vector<int>(size));

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (i == j)
            {
                matrix[i][j] = 0;
            }
            else
            {
                int from, to, len;
                F >> from >> to >> len;
                matrix[from - 1][to - 1] = matrix[to - 1][from - 1] = len;
            }
        }
    } 
    return matrix;
}

vector<pair<int, int>> SortEdges(vector<vector<int>>& matrix)
{
    vector<pair<int, int>> sortedEdges;
    int size = matrix.size();
    int count = (size * size - size) / 2;
    vector<vector<boolean>> visited;
    visited.resize(matrix.size(), vector<boolean>(matrix.size()));

    for (int k = 0; k < count; k++)
    {
        int min = INT_MAX;
        pair<int, int> index;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (i < j && matrix[i][j] < min && !visited[i][j])
                {
                    min = matrix[i][j];
                    index.first = i, index.second = j;
                }
            }
        }
        visited[index.first][index.second] = true;
        sortedEdges.push_back(index);
    }
    return sortedEdges;
}

vector<pair<int, int>> SortOutEdges(vector<pair<int, int>>& edges, vector<vector<int>>& matrix)
{
    vector<pair<int, int>> sortedEdges;
    int k = 0;
    pair<int, int> tmp;
    boolean isTrue = false;
    int size = edges.size();
    for (int i = 0; i < size; i++)
    {
        int j = 0;
        while (!isTrue)
        {
            if (edges[j].first == k)
            {
                isTrue = true;
                tmp = edges[j];
                k = edges[j].second;
                sortedEdges.push_back(tmp);
                edges.erase(edges.begin() + j);
            }
            else if (edges[j].second == k)
            {
                isTrue = true;
                tmp.first = edges[j].second, tmp.second = edges[j].first;
                k = edges[j].first;
                sortedEdges.push_back(tmp);
                edges.erase(edges.begin() + j);
            }
            j++;
        }
        isTrue = false;
    }
    return sortedEdges;
}

void KruskalsAlghoritm(vector<vector<int>>& matrix)
{
    vector<pair<int, int>> result, edges = SortEdges(matrix);
    cout << "Отсортированные ребра:\n";
    for (int i = 0; i < edges.size(); i++) // отображение
    {
        cout << "(" << edges[i].first + 1 << ";" << edges[i].second + 1 << ") ";
    }
    cout << endl << endl;

    vector<int> comp(matrix.size()); // компонента связности
    for (int i = 0; i < matrix.size(); i++)
    {
        comp[i] = i;
    }

    vector<int> degrees(matrix.size(), 0); // степени вершин
    vector<boolean> visited(matrix.size(), false);
    int sum = 0;
    for (int i = 0; i < edges.size(); i++)
    {
        //cout << "  1  2  3  4  5  6\n  " << comp[0] + 1 << "  " << comp[1] + 1 << "  " << comp[2] + 1 << "  " << comp[3] + 1 << "  " << comp[4] + 1 << "  " << comp[5] + 1 << endl << endl;
        pair<int, int> index = edges[i];
        int len = matrix[index.first][index.second];
        if (comp[index.first] != comp[index.second] && (degrees[index.first] < 2) && (degrees[index.second] < 2))
        {
            degrees[index.first]++;
            degrees[index.second]++;
            sum += len;
            int a = comp[index.first];
            int b = comp[index.second];
            for (int j = 0; j < matrix.size(); j++)
            {
                if (comp[j] == b)
                {
                    comp[j] = a;
                }
            }
            result.push_back(index);
            visited[index.first] = true;
            cout << index.first + 1 << " -> " << index.second + 1 << " = " << len << endl << endl;
        }
    }
    //cout << "  1  2  3  4  5  6\n  " << degrees[0] + 1 << "  " << degrees[1] + 1 << "  " << degrees[2] + 1 << "  " << degrees[3] + 1 << "  " << degrees[4] + 1 << "  " << degrees[5] + 1 << endl << endl;
    pair<int, int> tmp;
    for (int i = 0; i < matrix.size(); i++)
    {
        if (visited[i] == false && degrees[i] != 2)
        {
            tmp.first = i;
        }
    }

    for (int i = 0; i < degrees.size(); i++)
    {
        if (degrees[i] == 1 && i != tmp.first)
        {
            tmp.second = i;
        }
    }
    cout << tmp.first + 1 << " -> " << tmp.second + 1 << " = " << matrix[tmp.first][tmp.second] << endl;
    sum += matrix[tmp.first][tmp.second];
    result.push_back(tmp);
    result = SortOutEdges(result, matrix);
    tmp = result.front();
    cout << endl << tmp.first + 1;
    while (!result.empty())
    {
        tmp = result.front();
        cout << " -> " << tmp.second + 1;
        result.erase(result.begin());
    }
    cout << endl << "Sum = " << sum << endl;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    vector<vector<int>> matrix;
    fstream file("matrix.txt");
    if (file.is_open())
    {
        matrix = ReadData(file);
        KruskalsAlghoritm(matrix);
    }
}
