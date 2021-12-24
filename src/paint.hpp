#pragma once

#include "graph.hpp"
#include <fstream>


void visualisation(const Graph &graph, const string &filename)
{
    ofstream file("../graphs/" + filename, std::ios_base::trunc);
    file << "graph " << filename.substr(0, filename.size() - 4) << "{\n";
    file << "\trankdir =LR;\n";
    file << "\tranksep = 0.8;\n";
    file << "\tnodesep = 0.8;\n";

    int size = graph.n;
    bool vec[size][size];
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            vec[i][j] = false;
        }
    }

    for (auto &edge: graph.edges)
    {
        for (auto &one_edge: edge)
        {
            if (vec[one_edge.a][one_edge.b] == vec[one_edge.b][one_edge.a])
            {
                vec[one_edge.a][one_edge.b] = true;
                file << "\t" << 1 + one_edge.a << "--" << 1 + one_edge.b << fixed
                     << setprecision(2) << " [label=\"" << one_edge.cost << "\"];\n";
            }
        }
    }
    file << "}";
    file.close();
}

void visualisationPath(const Graph &graph, const vector<int> &a, const string &filename)
{
    ofstream file("../graphs/" + filename, std::ios_base::trunc);
    file << "graph " << filename.substr(0, filename.size() - 4) << "{\n";
    file << "\trankdir =LR;\n";
    file << "\tranksep = 0.8;\n";
    file << "\tnodesep = 0.8;\n";

    int size = graph.n;
    bool vec[size][size];
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            vec[i][j] = false;
        }
    }

    for (auto &edge: graph.edges)
    {
        for (auto &one_edge: edge)
        {
            if (vec[one_edge.a][one_edge.b] == vec[one_edge.b][one_edge.a])
            {
                vec[one_edge.a][one_edge.b] = true;
                file << "\t" << 1 + one_edge.a << "--" << 1 + one_edge.b << fixed
                     << setprecision(2) << " [label=\"" << one_edge.cost << "\"];\n";
            }
        }
    }

    for (int i = 0; i < a.size(); i++)
    {
        file << "\t" << 1 + a[i] << " [color=\"blue\",style=filled];\n";
    }

    file << "}";
    file.close();
}
