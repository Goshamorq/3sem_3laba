#pragma once

#include "vertex.hpp"
#include <chrono>
#include <cmath>
#include <utility>
#include <vector>
#include <algorithm>
#include <cassert>
#include <iomanip>
#include <random>
#include <fstream>

using namespace std;

///ребро
struct Edge
{
    int a = 0; // индекс первой вершины
    int b = 0; // индекс второй вершины
    double cost = 0.0; // цена пути между ними

    Edge(int a, int b, double cost) : a(a), b(b), cost(cost)
    {};

    ~Edge() = default;
};

class Graph
{
public:
    vector<vector<bool>> mx; // матрица смежности, вершина смежна сама с собой
    vector<Vertex> verts; // вершины
    vector<vector<Edge>> edges;
    int n = 0; // количество вершин
    int m = 0; // количество рёбер

    Graph(const vector<vector<bool>> &matrix, const vector<Vertex> &verts) : mx(matrix), verts(verts), n(verts.size())
    {
        for (int i = 0; i < n; ++i) // смотрим на матрицу смежности, +1 если ребро есть
            for (int j = i + 1; j < n; ++j)
                if (mx[i][j] != 0.0)
                    m++;

        edges.resize(n); // увеличили капасити
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (mx[i][j])
                {
                    edges[i].emplace_back(i, j, dist(verts[i], verts[j]));
                    edges[j].emplace_back(j, i, dist(verts[i], verts[j]));
                }
    };

    void addVertex(const Vertex &p)
    {
        // проверка, есть ли такой уже среди вершин
        for (auto &v: verts)
            if (equal(v, p, 0.001))
                return;

        verts.emplace_back(p);
        for (int i = 0; i < n; ++i)
            mx[i].emplace_back(false);

        mx.emplace_back(vector<bool>(n + 1, false));
        edges.resize(n + 1);
        n++;
    }

    void addEdge(const int begin, const int end)
    {
        if (begin < 0 || begin >= n || end < 0 || end >= n)
        {
            cerr << "Error in func addEdge(" << begin << ", " << end << ")\n";
            throw out_of_range("Error in funk addEdge");
        }

        // чек на дубликат
        if (mx[begin][end])
            return;

        m++;
        edges[begin].emplace_back(Edge(begin, end, dist(verts[begin], verts[end])));
        edges[end].emplace_back(Edge(end, begin, dist(verts[begin], verts[end])));

        mx[begin][end] = true;
        mx[end][begin] = true;
    }


    /// поиск кратчайшего расстояния от начальной вершины до остальных вершин
    [[nodiscard]] vector<double> search(int begin) const
    {
        vector<double> d(n, 1e9); //вектор длин
        vector<int> p(n); // родители
        vector<bool> visited(n, false); // вектор пометок
        d[begin] = 0;

        for (int i = 0; i < n; ++i)
        {
            int v = -1; // первичное значение индекса
            for (int j = 0; j < n; ++j)
                if (!visited[j] && (v == -1 || d[j] < d[v]))
                    v = j;

            if (d[v] == 1e9)
                break;

            visited[v] = true;

            for (size_t j = 0; j < edges[v].size(); ++j)
            {
                int to = edges[v][j].b;
                double len = edges[v][j].cost;
                if (d[v] + len < d[to])
                {
                    d[to] = d[v] + len;
                    p[to] = v;
                }
            }
        }

        for (int i = 0; i < n; i++)
            if (d[i] == 1e9)
                d[i] = -1.0;

        return d;
    }

    /// поиск кратчайшего пути между двумя вершинами
    vector<int> searchPath(int begin, int end)
    {
        vector<double> d(n, 1e9); //вектор длин
        vector<int> p(n); // родители
        vector<bool> visited(n, false); // вектор пометок
        d[begin] = 0;

        for (int i = 0; i < n; ++i)
        {
            int v = -1; // первичное значение индекса
            for (int j = 0; j < n; ++j)
                if (!visited[j] && (v == -1 || d[j] < d[v]))
                    v = j;

            if (d[v] == 1e9)
                break;

            visited[v] = true;

            for (size_t j = 0; j < edges[v].size(); ++j)
            {
                int to = edges[v][j].b;
                double len = edges[v][j].cost;
                if (d[v] + len < d[to])
                {
                    d[to] = d[v] + len;
                    p[to] = v;
                }
            }
        }

        vector<int> path;
        path.reserve(n / 2);
        for (int cur = end; cur != begin; cur = p[cur])
            path.push_back(cur);
        path.push_back(begin);
        reverse(path.begin(), path.end());

        return path;
    }

    ~Graph() = default;
};

/// Генерация случайного графа заданного размера
Graph generateGraph(int n)
{
    // n - размер графа
    vector<vector<bool>> mx(n);
    random_device rd;
    mt19937 mersenne(rd());
    // Создаём пустую матрицу смежности
    for (int i = 0; i < n; i++)
    {
        mx[i].resize(n, false);
        for (int j = 0; j < n; j++)
            if (mersenne() % (n / 3) == 3)
                mx[i][j] = true;
        mx[i][i] = true;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
            if (mx[j][i])
                mx[i][j] = true;
    }

    vector<Vertex> verts(n);
    for (int i = 0; i < n; i++)
        verts[i] = Vertex(mersenne() % 3 * n, mersenne() % 3 * n, 0);

    Graph graph(mx, verts);
    return graph;
}
