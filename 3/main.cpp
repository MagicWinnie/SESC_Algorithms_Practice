// Bellman-Ford
// input:
// list of edges
// output:
// sum of weights of the shortest path
// Written by Dmitriy Okoneshnikov, 2021
#include <iostream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <queue>
#include <cmath>
#include <vector>
const int INF = 100000;

using namespace std;

struct edge
{
    edge(int i, int j, int w) : src(i), dest(j), weight(w) {}
    int src;
    int dest;
    int weight;
};

int BellmanFord(vector<edge> arr, int n, int m, int start, int finish)
{
    vector<int> dist(n, INF);

    dist[start] = 0;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int u = arr[j].src;
            int v = arr[j].dest;
            int weight = arr[j].weight;

            if (dist[u] != INF && dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
            }
        }
    }

    for (int j = 0; j < m; j++)
    {
        int u = arr[j].src;
        int v = arr[j].dest;
        int weight = arr[j].weight;

        if (dist[u] + weight < dist[v])
        {
            return -1;
        }
    }

    return dist[finish];
}

int main(int argc, char **argv)
{
    string input_filename = "input.txt";
    string output_filename = "output.txt";
    if (argc == 2)
    {
        input_filename = argv[1];
    }
    else if (argc >= 3)
    {
        input_filename = argv[1];
        output_filename = argv[2];
    }

    ifstream inp(input_filename);

    int n, m, t, s, f;

    inp >> s >> f;
    s--;
    f--;
    inp >> n >> m >> t;

    vector<edge> arr;
    for (int l = 0; l < m; l++)
    {
        int i, j, k;
        inp >> i >> j;
        i--;
        j--;
        if (t == 2 || t == 4)
        {
            inp >> k;
        }
        if (t == 1)
        {
            arr.push_back(edge(i, j, 1));
        }
        else if (t == 2)
        {
            arr.push_back(edge(i, j, k));
        }
        else if (t == 3)
        {
            arr.push_back(edge(i, j, 1));
            arr.push_back(edge(j, i, 1));
        }
        else if (t == 4)
        {
            arr.push_back(edge(i, j, k));
            arr.push_back(edge(j, i, k));
        }
    }
    inp.close();

    int cost = BellmanFord(arr, n, m, s, f);

    ofstream out(output_filename, std::ios::out | std::ios::trunc);
    if (cost == INF)
        cost = 0;
    out << cost << endl;
    out.close();
}
