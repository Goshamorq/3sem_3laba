#include <fstream>
#include "graph.hpp"
#include "paint.hpp"
#include <ctime>

void benchSearch(int n)
{
    ofstream file("../graphics/benchSearch.txt", ios_base::trunc);
    for (int i = n / 50; i <= n; i += n / 50)
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
// C:\Users\Tom\CLionProjects\last_laba\graphs
// dot -Tpng graph_test.gv -oexample1.png
// dot -Tpng graph_vis.gv -oexamplevis.png
int main()
{
    srand ( time(NULL) );
//    benchSearch(10000);
    int n = 7;
    vector<vector<bool>> mx = {{1, 1, 1, 0, 0, 0, 1},
                               {1, 1, 1, 1, 0, 0, 0},
                               {1, 1, 1, 1, 0, 1, 1},
                               {0, 1, 1, 1, 1, 0, 1},
                               {0, 0, 0, 1, 1, 1, 0},
                               {0, 0, 1, 0, 1, 1, 0},
                               {1, 0, 1, 1, 0, 0, 1}};


    vector<Vertex> verts(n);
    for (int i = 0; i < n; i++)
    {
        verts[i] = Vertex(rand() % 10, rand() % 10, 0);
    }
    Graph graph(mx, verts);

    visualisation(graph, "graph_test.gv");
    vector<int> path = graph.searchPath(0, 3);
    visualisationPath(graph, path, "graph_vis.gv");
    return 0;
}
