#include "../src/graph.hpp"
#include "gtest/gtest.h"
#include <fstream>
#include <random>

using namespace std;

TEST(Graph, path)
{
    vector<vector<bool>> mx = {{0, 1, 0, 1, 1, 1},
                               {1, 0, 1, 0, 0, 0},
                               {0, 1, 0, 1, 0, 1},
                               {1, 0, 1, 0, 1, 0},
                               {1, 0, 0, 1, 0, 1},
                               {1, 0, 1, 0, 1, 0}};

    vector<Vertex> verts = {Vertex(0, 2, 0), Vertex(2, 2, 0),
                            Vertex(3, 1, 0), Vertex(2, 0, 0),
                            Vertex(0, 0, 0), Vertex(1, 1, 1)};
    Graph graph(mx, verts);

    auto ans2 = graph.searchPath(0, 2);
    vector<int> true_path = {0, 1, 2};
    ASSERT_TRUE(ans2 == true_path);
}

TEST(Graph, search)
{
    vector<vector<bool>> mx = {{0, 1, 0, 1, 1, 1},
                               {1, 0, 1, 0, 0, 0},
                               {0, 1, 0, 1, 0, 1},
                               {1, 0, 1, 0, 1, 0},
                               {1, 0, 0, 1, 0, 1},
                               {1, 0, 1, 0, 1, 0}};

    vector<Vertex> verts = {Vertex(0, 2, 0), Vertex(2, 2, 0), Vertex(3, 1, 0), Vertex(2, 0, 0), Vertex(0, 0, 0),
                            Vertex(1, 1, 1)};
    Graph graph(mx, verts);

    vector<double> ans0 = {0.0, 2.0, 2 + sqrt(2), sqrt(8), 2.0, sqrt(3)};

    ASSERT_TRUE(graph.search(0) == ans0);

    vector<double> ans4 = {2.0, 4.0, 2.0 + sqrt(2), 2.0, 0.0, sqrt(3)};
    ASSERT_TRUE(graph.search(4) == ans4);
}

TEST(Graph, searchPath)
{
    vector<vector<bool>> mx = {{0, 1, 0, 1, 1, 1},
                               {1, 0, 1, 0, 0, 0},
                               {0, 1, 0, 1, 0, 1},
                               {1, 0, 1, 0, 1, 0},
                               {1, 0, 0, 1, 0, 1},
                               {1, 0, 1, 0, 1, 0}};

    vector<Vertex> verts = {Vertex(0, 2, 0), Vertex(2, 2, 0), Vertex(3, 1, 0), Vertex(2, 0, 0), Vertex(0, 0, 0),
                            Vertex(1, 1, 1)};
    Graph graph(mx, verts);

    vector<int> ans = {4, 3, 2};
    vector<int> ans2 = {5, 2, 1};

    ASSERT_TRUE(graph.searchPath(4, 2) == ans);
    ASSERT_TRUE(ans2 == graph.searchPath(5, 1));
}


TEST(Graph,bench_search)
{
    int n = 15000;
    ofstream file("../graphics/benchSearch.txt", ios_base::trunc);
    for (int i = n / 20; i <= n; i += n / 20)
    {
        Graph graph = generateGraph(i);
        auto begin = chrono::steady_clock::now();
        vector<double> ans1 = graph.search(0);
        vector<double> ans2 = graph.search(i / 4);
        vector<double> ans3 = graph.search(i / 2);
        vector<double> ans4 = graph.search(i - 1);
        auto end = chrono::steady_clock::now();
        auto time = chrono::duration_cast<chrono::microseconds>(end - begin);
        cout << i << "\n";
        file << i << " " << time.count() / 4.0 << "\n";
    }
    file.close();
}
//
//TEST(Graph, add)
//{
//    vector<vector<bool>> mx = {{0, 1, 0, 1, 1, 1},
//                               {1, 0, 1, 0, 0, 0},
//                               {0, 1, 0, 1, 0, 1},
//                               {1, 0, 1, 0, 1, 0},
//                               {1, 0, 0, 1, 0, 1},
//                               {1, 0, 1, 0, 1, 0}};
//
//    vector<Vertex> verts = {Vertex(0, 2, 0), Vertex(2, 2, 0), Vertex(3, 1, 0), Vertex(2, 0, 0), Vertex(0, 0, 0),
//                            Vertex(1, 1, 1)};
//    Graph graph(mx, verts);
//
//    graph.addVertex(Vertex{2, 1, 0});
//    graph.addEdge(6, 2);
//    graph.addEdge(6, 1);
//    graph.addEdge(6, 4);
//    graph.addEdge(6, 3);
//
//    vector<double> ans4 = {2.0, sqrt(5) + 1, sqrt(5) + 1, 2.0, 0.0, sqrt(3), sqrt(5)};
//
//    vector<int> ans = graph.searchPath(4, 2);
//    vector<Vertex> path(ans.size());
//    for (int i = 0; i < ans.size(); i++)
//        path[i] = graph.verts[ans[i]];
//}

//TEST(Graph, visualisation)
//{
//    vector<vector<bool>> mx = {{0, 1, 0, 1, 1},
//                               {1, 0, 1, 0, 0},
//                               {0, 1, 0, 1, 0},
//                               {1, 0, 1, 0, 1},
//                               {1, 0, 0, 1, 0}};
//
//    vector<Vertex> verts = {Vertex(0, 2, 0), Vertex(2, 2, 0), Vertex(3, 1, 0), Vertex(2, 0, 0), Vertex(0, 0, 0)};
//    Graph graph(mx, verts);
//}
